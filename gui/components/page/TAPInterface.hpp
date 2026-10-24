#ifndef TAPINTERFACE_HPP
#define TAPINTERFACE_HPP

#include "../Component.hpp"
#include <string>

class Environment;
class Group;
class Header;
class Inventory;
class Protocol;
class Server;


class TAPInterface : public Component
{
    public:
        int width;
        int height;
        Server *server;
        Group *screen;
        std::string chat_message;
        std::string protocol_command;
        bool chat_focused;
        bool command_focused;
        Header *header;
        Environment *environment;
        Inventory *inventory;
        Protocol *protocol;

        TAPInterface(App *app, int width, int height, Server *server);
        void update_data();
        void render(int origin_x = 0, int origin_y = 0) override;
        ~TAPInterface();
};


#endif