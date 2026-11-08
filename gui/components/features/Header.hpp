#ifndef TAP_HEADER_HPP
#define TAP_HEADER_HPP

#include "../Component.hpp"
#include <string>
#include <vector>

class Group;
class ProgressBar;
class Server;
class Text;

class Header : public Component
{
    private:
        Server *server;
        Group *content;
        Text *username;
        ProgressBar *health_bar;
        Text *health_value;
        Text *group_value;

        int width;
        int stat_gap;
        int stats_y;
        int right_padding;

        std::vector<Group *> stats;
        std::vector<int> stats_widths;

        void layout_stats();

    public:
        Header(App *app, int width, float scale, Server *server);
        void update_username(const std::string &username);
        void render(int origin_x = 0, int origin_y = 0) override;
        void update_hp();
        ~Header();
};

#endif
