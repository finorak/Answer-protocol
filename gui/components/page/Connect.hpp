#ifndef CONNECT_HPP
#define CONNECT_HPP

#include "../Component.hpp"
#include <string>
#include <functional>

class Button;
class Group;
class Input;
class Server;
class Text;


class Connect : public Component
{
    public:
        int width;
        int height;
        Server *server;
        std::string input_content;
        bool input_focused;
        std::string message;
        bool confirmed;
        std::function<void(std::string u)> on_connect_success;
        Group *screen;
        Text *heading;
        Text *description_line_one;
        Text *description_line_two;
        Text *description_line_three;
        Text *status_message;
        Input *username_input;
        Button *submit_button;

        Connect(App *app, int width, int height, Server *server,
            std::function<void(std::string u)> on_connect_success,
            std::function<void()> on_exit);
        void submit();
        void render(int origin_x = 0, int origin_y = 0) override;
        ~Connect();
};


#endif