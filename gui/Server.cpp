#include "Server.hpp"
#include "common.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "components/page/TAPInterface.hpp"
#include "components/features/Environment.hpp"
#include "components/features/Inventory.hpp"
#include "components/features/Protocol.hpp"

using namespace std;


void *Server::wait_for_server(void *arg)
{
	char	buffer[BUFFER_SIZE];
	Server *server = static_cast<Server *>(arg);
    string received;

	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes = recv(server->sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0)
        {
            printf("DISCONNECTED SERVER!\n");
            server->connected = false;
            server->response_ready.notify_all();
            return NULL;
        }
		if (!server->connected)
			break;
        received.append(buffer, bytes);
        size_t pos;
        while ((pos = received.find('\n')) != string::npos)
        {
            string line = received.substr(0, pos);
            received.erase(0, pos + 1);

            if (!line.empty() && line.back() == '\r')
                line.pop_back();

            if (strncmp(line.c_str(), "EVT", 3) == 0)
            {
                lock_guard<mutex> lock(server->message_mutex);
                server->pending_events.push_back(line);
            }
            else
                server->on_response(line);
        }
	}
	return (NULL);
}

string Server::get_timestamp()
{
    time_t now = time(nullptr);
    tm local_time = *localtime(&now);

    ostringstream oss;
    oss << put_time(&local_time, "%H:%M:%S");

    return oss.str();
}

void Server::on_event(string event)
{
	cout << "SERVER EVENT: " << event << endl;

    if (!tap_interface)
        return;

    istringstream stream(event);

    string evt;
    string category;
    string type;

    stream >> evt >> category >> type;

    if (category == "GLOBAL" && type == "CHAT")
    {
        string username;
        string message;

        stream >> username;
        getline(stream >> ws, message);

        tap_interface->inventory->add_message(get_timestamp(), username, message, category);
    }
    else if (category == "ROOM")
    {
        if (type == "CHAT")
        {
            string username;
            string message;

            stream >> username;
            getline(stream >> ws, message);

            tap_interface->inventory->add_message(get_timestamp(), username, message, category);
        }
        else if (type == "PRESENCE")
        {
            tap_interface->environment->look();
        }
        else

            tap_interface->update_data();
    }
    else if (category == "GROUP")
    {
        if (type == "CHAT")
        {
            string username;
            string message;

            stream >> username;
            getline(stream >> ws, message);

            tap_interface->inventory->add_message(get_timestamp(), username, message, category);
        }
        else if (type == "INVITE")
        {
            string leader;
            stream >> leader;
            string message = "Group invitation from " + leader;

            tap_interface->protocol->log_protocol(message);
        }
        else if (type == "JOIN" || type == "LEAVE")
        {
            string username;
            stream >> username;


            string message = username +
                            (type == "JOIN"
                                ? " joined the group."
                                : " left the group.");
            tap_interface->protocol->log_protocol(message);
        }
    }
    else
    {
        tap_interface->update_data();
    }
}

string Server::request(string request_msg)
{
    if (!connected)
        return "";
    request_msg = request_msg + "\n";
    if (send(sock, request_msg.c_str(), request_msg.size(), MSG_NOSIGNAL)
        != static_cast<ssize_t>(request_msg.size()))
        return "";

    unique_lock<mutex> lock(message_mutex);
    response_ready.wait(lock, [this]() {
        return !pending_responses.empty() || !connected;
    });
    if (pending_responses.empty())
        return "";

    string response = move(pending_responses.front());
    pending_responses.pop_front();
    cout << "SERVER RESPONSE: " << response << endl;
    return response;
}

void Server::on_response(string response)
{
    {
        lock_guard<mutex> lock(message_mutex);
        pending_responses.push_back(move(response));
    }
    response_ready.notify_one();
}

void Server::dispatch_events()
{
    deque<string> events;
    {
        lock_guard<mutex> lock(message_mutex);
        events.swap(pending_events);
    }
    for (const string &event : events)
        on_event(event);
}

Server::Server(char *ip): sock(-1), ip(ip), connected(false), tap_interface(nullptr),
    client_thread_started(false)
{
    if (!connect_to_server())
		return ;
    connected = true;

    char buffer[BUFFER_SIZE];
    string received;
    size_t pos = string::npos;

    while (pos == string::npos)
    {
        memset(buffer, 0, BUFFER_SIZE);

        ssize_t bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0)
        {
            connected = false;
            close(sock);
            sock = -1;
            return;
        }

        received.append(buffer, bytes);
        pos = received.find('\n');
    }

	cout << "FIRST SERVER LINE: " << received;
    if (pthread_create(&client_mods, NULL, wait_for_server, this) != 0)
    {
        connected = false;
        close(sock);
        sock = -1;
        return;
    }
    client_thread_started = true;
}


int Server::connect_to_server()
{
	struct sockaddr_in	addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(ip);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(this->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf("NO SERVER TO CONNECT WITH!\n");
        close(sock);
        sock = -1;
		return 0;
	}
	printf("OK hello proto=2\n");
	return 1;
}

Server::~Server()
{
    connected = false;
    if (sock >= 0)
        shutdown(sock, SHUT_RDWR);
    response_ready.notify_all();
    if (client_thread_started)
        pthread_join(client_mods, NULL);
    if (sock >= 0)
        close(sock);
}
