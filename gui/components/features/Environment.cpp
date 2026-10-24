#include "Environment.hpp"
#include "TAPInterfaceHelpers.hpp"
#include "../basic/Button.hpp"
#include "../basic/Group.hpp"
#include "../basic/Input.hpp"
#include "../basic/Line.hpp"
#include "../basic/Rect.hpp"
#include "../basic/Text.hpp"
#include "../../Server.hpp"
#include <string>
#include <cmath>
#include <algorithm>
#include <regex>

using namespace std;
using namespace TAPUI;

Environment::Environment(App *app, int x, int width, int panel_height, float scale, Server *server, function<void(string)> log_protocol)
        : Component(app, x, 0), actualize(false), panel(nullptr), server(server),
            log_protocol(log_protocol), width(width), group_popup(nullptr),
            group_popup_open(false), create_group_focused(false),
            join_group_focused(false), invite_player_focused(false),
            group_feedback(nullptr)
{
    px = [scale](float value) { return static_cast<int>(lround(value * scale)); };
    Group *room = create_panel(app, width, panel_height, "01 / ENVIRONMENT");
    const int room_end = width - px(16);

    room_name = add_text(room, app, px(16), px(52), "The Forgotten Archive", px(17), text_color);
    room_id = add_text(room, app, px(16), px(78), "LOCATION // ARC-003", px(10), blue_light, px(1));
    room_description = add_text(room, app, px(16), px(105),
        "", px(12), muted);
    add_text(room, app, px(16), px(197), "EXITS", px(10), blue_light, px(1));
    north_button = new Button(
        app, px(82), px(190), px(62), 26, "NORTH", [this]() {
            this->server->request("MOVE north");
            this->look();
        },
        {11, 26, 46, 255}, blue_light, 0,
        {37, 70, 107, 255}, {16, 39, 68, 255}, {65, 72, 82, 255},
        10, 1, true
    );
    room->children.push_back(north_button);

    south_button = new Button(
        app, px(150), px(190), px(62), 26, "SOUTH", [this]() {
            this->server->request("MOVE south");
            this->look();
        },
        {11, 26, 46, 255}, blue_light, 0,
        {37, 70, 107, 255}, {16, 39, 68, 255}, {65, 72, 82, 255},
        10, 1, true
    );
    room->children.push_back(south_button);

    west_button = new Button(
        app, px(218), px(190), px(62), 26, "WEST", [this]() {
            this->server->request("MOVE west");
            this->look();
        },
        {11, 26, 46, 255}, blue_light, 0,
        {37, 70, 107, 255}, {16, 39, 68, 255}, {65, 72, 82, 255},
        10, 1, true
    );
    room->children.push_back(west_button);

    east_button = new Button(
        app, px(286), px(190), px(62), 26, "EAST", [this]() {
            this->server->request("MOVE east");
            this->look();
        },
        {11, 26, 46, 255}, blue_light, 0,
        {37, 70, 107, 255}, {16, 39, 68, 255}, {65, 72, 82, 255},
        10, 1, true
    );
    room->children.push_back(east_button);

    add_text(room, app, px(16), px(236), "ITEMS IN THIS ROOM", px(10), blue_light, px(2));
    room->children.push_back(new Line(app, px(16), px(258), room_end, px(258), border));

    item_components = new Group(app, 0, 0, {});
    room->children.push_back(item_components);
    show_items();

    add_text(room, app, px(16), px(382),
        "NPCS", px(10), blue_light, px(2));

    room->children.push_back(
        new Line(app, px(16), px(404), room_end, px(404), border)
    );

    npc_components = new Group(app, 0, px(416), {});
    room->children.push_back(npc_components);
    show_npcs();

    add_text(room, app, px(16), px(503), "PLAYERS PRESENT", px(10), blue_light, px(2));
    player_components = new Group(app, 0, 0, {});
    room->children.push_back(player_components);
    show_players();
    room->children.push_back(new Line(app, px(16), px(562), room_end, px(562), border));

    int action_y = px(574);

    room->children.push_back(new Button(
        app, px(16), action_y, px(68), px(24), "QUESTS",
        [this]() {
            this->log_protocol(this->server->request("QUESTS"));
        },
        {11, 26, 46, 255}, blue_light, 0,
        {37, 70, 107, 255}, {16, 39, 68, 255},
        {11, 26, 46, 255}, 10, 1, true
    ));

    room->children.push_back(new Button(
        app, px(90), action_y, px(100), px(24), "GROUP",
        [this]() { this->group_popup_open = !this->group_popup_open; },
        {11, 26, 46, 255}, blue_light, 0,
        {37, 70, 107, 255}, {16, 39, 68, 255},
        {11, 26, 46, 255}, 10, 1, true
    ));

    const int popup_width = width - px(32);
    const int input_x = px(16);
    const int submit_width = px(72);
    const int field_gap = px(8);
    const int field_width = popup_width - input_x * 2 - submit_width - field_gap;
    group_popup = new Group(app, px(16), px(112), {});
    group_popup->children.push_back(new Rect(app, 0, 0, popup_width, px(390),
        panel_dark, border, px(1)));
    add_text(group_popup, app, input_x, px(14), "GROUP MANAGEMENT", px(11), blue_light, px(1));
    group_popup->children.push_back(new Button(app, popup_width - px(40), px(8),
        px(28), px(24), "X", [this]() { this->group_popup_open = false; },
        panel_dark, muted, 0, border, {16, 39, 68, 255}, panel_dark,
        px(10), 0, true));
    group_popup->children.push_back(new Line(app, input_x, px(40),
        popup_width - input_x, px(40), border));

    const int section_label_size = px(10);
    const int field_height = px(32);
    auto add_group_field = [&](const string &label, int y, string &value,
        bool &focused, const string &placeholder, const string &action)
    {
        string *input_value = &value;
        add_text(group_popup, app, input_x, y, label, section_label_size, text_color);
        Input *input = new Input(app, input_x, y + px(18), field_width,
            field_height, &value, &focused, panel_dark, text_color, 0,
            border, placeholder, ">_", 31, px(11), muted,
            [this, input_value, action]() {
                this->submit_group_action(*input_value, action);
            },
            blue, blue_light);
        group_popup->children.push_back(input);
        group_popup->children.push_back(new Button(app,
            input_x + field_width + field_gap, y + px(18), submit_width,
            field_height, "SUBMIT", [this, input_value, action]() {
                this->submit_group_action(*input_value, action);
            }, {11, 26, 46, 255}, blue_light, 0,
            border, {16, 39, 68, 255}, {11, 26, 46, 255}, px(9), 0, true));
    };

    add_group_field("CREATE A GROUP", px(52), create_group_name,
        create_group_focused, "Group name", "CREATE");
    add_group_field("JOIN A GROUP", px(122), join_group_name,
        join_group_focused, "Group name", "JOIN");
    add_group_field("INVITE A PERSON", px(192), invite_player_name,
        invite_player_focused, "Player name", "INVITE");
    add_text(group_popup, app, input_x, px(262), "LEAVE THE GROUP",
        section_label_size, text_color);
    group_popup->children.push_back(new Button(app, input_x, px(280),
        popup_width - input_x * 2, field_height, "LEAVE GROUP", [this]() {
            this->submit_group_action(this->join_group_name, "LEAVE");
        }, {11, 26, 46, 255}, {255, 151, 151, 255}, 0,
        {104, 49, 57, 255}, {57, 27, 34, 255}, {11, 26, 46, 255},
        px(10), 0, true));
    group_feedback = add_text(group_popup, app, input_x, px(330), "",
        px(10), muted);

    panel = room;
}

void Environment::render(int origin_x, int origin_y)
{
    if (!group_popup_open)
    {
        panel->render(origin_x + x, origin_y + y);
        return;
    }

    vector<SDL_Event> events;
    events.swap(app->events);
    panel->render(origin_x + x, origin_y + y);
    events.swap(app->events);
    group_popup->render(origin_x + x, origin_y + y);
}

void Environment::submit_group_action(string &value, const string &action)
{
    size_t first = value.find_first_not_of(" \t\r\n");
    size_t last = value.find_last_not_of(" \t\r\n");
    string name = first == string::npos ? "" : value.substr(first, last - first + 1);
    if (action != "LEAVE" && name.empty())
    {
        group_feedback->text = "Enter a name before submitting.";
        group_feedback->color = error;
        return;
    }
    if (action != "LEAVE" && name.size() > 31)
    {
        group_feedback->text = "Names must be 31 characters or fewer.";
        group_feedback->color = error;
        return;
    }
    if ((action == "CREATE" || action == "JOIN")
        && name.find_first_of(" \t\r\n") != string::npos)
    {
        group_feedback->text = "Group names cannot contain spaces.";
        group_feedback->color = error;
        return;
    }
    if (action == "INVITE"
        && !regex_match(name, regex("^[A-Za-z0-9_-]{2,24}$")))
    {
        group_feedback->text = "Use 2-24 letters, numbers, _ or - for player names.";
        group_feedback->color = error;
        return;
    }

    string command = "GROUP " + action;
    if (action != "LEAVE")
        command += " " + name;
    string response = server->request(command);
    log_protocol(response);
    bool succeeded = response.compare(0, 2, "OK") == 0;
    group_feedback->text = succeeded
        ? "Success. Details are in the protocol log."
        : "Request failed. Details are in the protocol log.";
    group_feedback->color = succeeded ? blue_light : error;
    if (succeeded && action != "LEAVE")
        value.clear();
}

Environment::~Environment()
{
    delete panel;
    delete group_popup;
}
