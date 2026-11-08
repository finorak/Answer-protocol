#ifndef SERVER_HPP
#define SERVER_HPP

#include <pthread.h>
#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <string>

class TAPInterface;

class Server
{
    public:
        int sock;
        char *ip;
        std::atomic<bool> connected;
        pthread_t client_mods;
        TAPInterface *tap_interface;
        std::mutex message_mutex;
        std::condition_variable response_ready;
        std::deque<std::string> pending_responses;
        std::deque<std::string> pending_events;
        bool client_thread_started;

        Server(char *ip);
        int connect_to_server();
        void on_event(std::string event);
        std::string request(std::string request_msg);
        void on_response(std::string response);
        void dispatch_events();
        std::string get_timestamp();
        static void *wait_for_server(void *arg);
        ~Server();
};

#endif
