#ifndef TAP_ENVIRONMENT_HPP
#define TAP_ENVIRONMENT_HPP

#include "../Component.hpp"
#include <functional>
#include <string>
#include <vector>

class Button;
class Group;
class Input;
class ScrollableGroup;
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
        ScrollableGroup *room_description;
        Button *north_button;
        Button *south_button;
        Button *west_button;
        Button *east_button;
        ScrollableGroup *item_components;
        ScrollableGroup *player_components;
        ScrollableGroup *npc_components;
        std::vector<std::string> players;
        std::vector<std::string> items;
        std::vector<std::string> npcs;
        std::function<int(float)> px;
        std::function<void(std::string)> log_protocol;
        std::function<void()> update_hp;
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
        std::string member_group;
        Group *quest_popup;
        ScrollableGroup *quest_components;
        Text *quest_feedback;
        bool quest_popup_open;
        bool quest_loading;
        bool quest_refresh_pending;

        struct Quest
        {
            std::string id;
            std::string status;
            std::string progress;
        };
        std::vector<Quest> quests;

        Environment(App *app, int x, int width, int panel_height, float scale,
            Server *server, std::function<void(std::string)> log_protocol, std::function<void()> update_hp);
        void render(int origin_x = 0, int origin_y = 0) override;
        void submit_group_action(std::string &value, const std::string &action);
        void load_quests();
        void show_quests();
        void complete_quest(const std::string &quest_id);
        void look();
        void show_items();
        void show_players();
        void show_npcs();
        ~Environment();
};

#endif
