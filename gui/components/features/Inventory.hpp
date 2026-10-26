#ifndef TAP_INVENTORY_HPP
#define TAP_INVENTORY_HPP

#include "../Component.hpp"
#include <functional>
#include <string>
#include <vector>

class Button;
class Group;
class ScrollableGroup;
class Server;

struct ChatMessage
{
    std::string time;
    std::string author;
    std::string message;
    std::string channel;
};

class Inventory : public Component
{
    
    public:
        bool actualize;
        int width;
        Group *panel;
        std::string &chat_message;
        bool &chat_focused;
        Server *server;
        std::vector<std::string> inventory_item;
        ScrollableGroup *inventory_components;
        std::function<int(float)> px;
        int chat_mode;
        Button *chat_mode_button;
        std::vector<ChatMessage> chat_messages;
        Group *chat_components;

        Inventory(App *app, int x, int width, int panel_height, float scale,
            std::string &chat_message, bool &chat_focused, Server *server);
        void update_inventory();
        void show_inventory();
        void render(int origin_x = 0, int origin_y = 0) override;
        void show_chat();
        void add_message(std::string time, std::string author,
            std::string message, std::string channel);
        ~Inventory();
};

#endif
