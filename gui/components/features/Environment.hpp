#ifndef TAP_ENVIRONMENT_HPP
#define TAP_ENVIRONMENT_HPP

#include "../Component.hpp"
#include <functional>
#include <string>
#include <vector>

class Button;
class Group;
class Input;
class Server;
class Text;

class Environment : public Component
{
    public:
        bool actualize;
        Group *panel;
        Server *server;
        Text *room_name;
        Text *room_id;
        Text *room_description;
        Button *north_button;
        Button *south_button;
        Button *west_button;
        Button *east_button;
        Group *item_components;
        Group *player_components;
        Group *npc_components;
        std::vector<std::string> players;
        std::vector<std::string> items;
        std::vector<std::string> npcs;
        std::function<int(float)> px;
        std::function<void(std::string)> log_protocol;
        int width;
        Group *group_popup;
        bool group_popup_open;
        std::string create_group_name;
        std::string join_group_name;
        std::string invite_player_name;
        bool create_group_focused;
        bool join_group_focused;
        bool invite_player_focused;
        Text *group_feedback;

        Environment(App *app, int x, int width, int panel_height, float scale,
            Server *server, std::function<void(std::string)> log_protocol);
        void render(int origin_x = 0, int origin_y = 0) override;
        void submit_group_action(std::string &value, const std::string &action);
        void look();
        void show_items();
        void show_players();
        void show_npcs();
        ~Environment();
};

#endif
