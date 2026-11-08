#ifndef TAP_PROTOCOL_HPP
#define TAP_PROTOCOL_HPP

#include "../Component.hpp"
#include <string>
#include <vector>
#include <functional>

class Group;
class Server;
class Text;
class Line;

class Protocol : public Component
{
    public:
        Group *panel;
        std::string &protocol_command;
        bool &command_focused;
        Server *server;
        std::vector<std::string> response_lines;
        std::vector<std::size_t> response_ends;
        std::vector<Text *> log_entries;
        std::vector<Line *> response_separators;
        int width;
        std::function<int(float)> px;
        Protocol(App *app, int x, int width, int panel_height, float scale,
            std::string &protocol_command, bool &command_focused, Server *server);
        void render(int origin_x = 0, int origin_y = 0) override;
        void submit_command();
        void log_protocol(std::string log);
        ~Protocol();
};

#endif
