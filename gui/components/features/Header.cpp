#include "Header.hpp"
#include "TAPInterfaceHelpers.hpp"
#include "../basic/Group.hpp"
#include "../basic/Circle.hpp"
#include "../basic/Line.hpp"
#include "../basic/ProgressBar.hpp"
#include "../basic/Text.hpp"
#include "../../Server.hpp"
#include "../../json.hpp"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using json = nlohmann::json;
using namespace TAPUI;

Header::Header(App *app, int width, float scale, Server *server)
        : Component(app, 0, 0), server(server), content(new Group(app, 0, 0, {})),
            username(nullptr), width(width), stat_gap(0), stats_y(0), right_padding(0)
{
    auto px = [scale](float value) { return static_cast<int>(lround(value * scale)); };
    content->children.push_back(new Line(app, 0, px(39), width, px(39), border));
    Text *brand = add_text(content, app, px(22), px(8), "TAP", px(20), blue_light, px(5));
    add_text(content, app, px(22) + brand->measureWidth() + px(14), px(15),
        "THE ANSWER PROTOCOL", px(10), muted, px(2));

    stats_y = px(15);
    right_padding = px(22);
    Group *online = new Group(app, 0, 0, {});
    online->children.push_back(new Circle(app, 3, px(4), px(3), blue_light, true));
    Text *online_label = add_text(online, app, px(13), 0, "ONLINE", px(10), muted, px(1));
    stats_widths.push_back(px(13) + online_label->measureWidth());
    stats.push_back(online);

    Group *player = new Group(app, 0, 0, {});
    Text *player_label = add_text(player, app, 0, 0, "PLAYER", px(10), muted, px(1));
    username = add_text(player, app, player_label->measureWidth() + px(5),
        0, "", px(10), text_color);
    stats_widths.push_back(username->x + username->measureWidth());
    stats.push_back(player);

    Group *health = new Group(app, 0, 0, {});
    Text *health_label = add_text(
        health, app, 0, 0, "HP", px(10), muted, px(1)
    );

    const int health_bar_x = health_label->measureWidth() + px(5);

    health_bar = new ProgressBar(
        app,
        health_bar_x,
        px(2),
        px(75),
        px(6),
        {21, 36, 58, 255},
        84,
        blue,
        0,
        {37, 68, 102, 255}
    );

    health->children.push_back(health_bar);

    health_value = add_text(
        health,
        app,
        health_bar_x + px(80),
        0,
        "84/100",
        px(10),
        text_color
    );

    stats_widths.push_back(
        health_value->x + health_value->measureWidth()
    );

    stats.push_back(health);

    Group *server_count = new Group(app, 0, 0, {});
    Text *server_label = add_text(server_count, app, 0, 0,
        "ON SERVER", px(10), muted, px(1));
    Text *server_value = add_text(server_count, app,
        server_label->measureWidth() + px(5), 0, server->ip, px(10), text_color);
    stats_widths.push_back(server_value->x + server_value->measureWidth());
    stats.push_back(server_count);

    Group *group_stat = new Group(app, 0, 0, {});
    Text *group_label = add_text(group_stat, app, 0, 0,
        "STATUS", px(10), muted, px(1));
    group_value = add_text(group_stat, app,
        group_label->measureWidth() + px(5), 0, "NullSector", px(10), text_color);
    stats_widths.push_back(group_value->x + group_value->measureWidth());
    stats.push_back(group_stat);

    stat_gap = px(20);
    for (Group *stat : stats)
        content->children.push_back(stat);
    layout_stats();
}

void Header::layout_stats()
{
    int stats_width = stat_gap * (stats.size() - 1);
    for (int stat_width : stats_widths)
        stats_width += stat_width;
    int stat_x = width - right_padding - stats_width;
    for (size_t index = 0; index < stats.size(); ++index)
    {
        stats[index]->x = stat_x;
        stats[index]->y = stats_y;
        stat_x += stats_widths[index] + stat_gap;
    }
}

void Header::update_username(const std::string &new_username)
{
    username->text = new_username;
    stats_widths[1] = username->x + username->measureWidth();
    layout_stats();
}

void Header::render(int origin_x, int origin_y)
{
    content->render(origin_x + x, origin_y + y);
}

void Header::update_hp()
{
    string response = this->server->request("STATUS");
    if (response.substr(0, 2) != "OK")
        return ;
    json json_response = json::parse(response.substr(2));

    int hp = json_response.at("hp").get<int>();
    int max_hp = json_response.at("max_hp").get<int>();
    string status = json_response.at("status").get<string>();
    if (!status.empty())
        status[0] = static_cast<char>(toupper(static_cast<unsigned char>(status[0])));

    health_value->text = to_string(hp) + "/" + to_string(max_hp);
    health_bar->progression = hp * 100 / max_hp;
    group_value->text = status;

    stats_widths[2] = health_value->x + health_value->measureWidth();

    layout_stats();
}

Header::~Header()
{
    delete content;
}
