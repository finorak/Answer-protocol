#include "Environment.hpp"
#include "TAPInterfaceHelpers.hpp"
#include "../basic/Button.hpp"
#include "../basic/Group.hpp"
#include "../basic/ScrollableGroup.hpp"
#include "../basic/Text.hpp"
#include "../../Server.hpp"
#include "../../json.hpp"
#include <algorithm>
#include <cctype>

using namespace std;
using namespace TAPUI;
using json = nlohmann::json;

void Environment::show_npcs()
{
    for (Component *component : npc_components->children)
        delete component;

    npc_components->children.clear();

    int index = 0;
    for (const string &npc : npcs)
    {
        const int y = px(5 + index * 38);
        add_text(npc_components, app, px(16), y, "NPC", px(10), blue_light, px(1));
        add_text(npc_components, app, px(64), y, npc, px(11), text_color);

        npc_components->children.push_back(new Button(
            app, width - px(196), y - px(5), px(52), px(24), "TALK",
            [this, npc]() {
                log_protocol(server->request("TALK " + npc));
            },
            {11, 26, 46, 255}, blue_light, 0,
            {37, 70, 107, 255}, {16, 39, 68, 255},
            {11, 26, 46, 255}, 10, 1, true
        ));

        npc_components->children.push_back(new Button(
            app, width - px(137), y - px(5), px(66), px(24), "ATTACK",
            [this, npc]() {
                log_protocol(server->request("ATTACK " + npc));
                this->update_hp();
            },
            {11, 26, 46, 255}, blue_light, 0,
            {37, 70, 107, 255}, {16, 39, 68, 255},
            {11, 26, 46, 255}, 10, 1, true
        ));

        npc_components->children.push_back(new Button(
            app, width - px(64), y - px(5), px(52), px(24), "QUEST",
            [this, npc]() {
                log_protocol(server->request("QUEST " + npc));
            },
            {11, 26, 46, 255}, blue_light, 0,
            {37, 70, 107, 255}, {16, 39, 68, 255},
            {11, 26, 46, 255}, 10, 1, true
        ));

        add_row_rule(npc_components, app, px(16), y + px(27), width - px(16));
        ++index;
    }
    npc_components->setContentHeight(px(5 + index * 38));
}

void Environment::show_players()
{
    for (Component *component : player_components->children)
        delete component;

    player_components->children.clear();

    int index = 0;
    int x = px(16);
    int y = px(529);
    for (const string &player : players)
    {
        add_text(player_components, app, x, y,
            player + (index < static_cast<int>(players.size()) - 1 ? "," : ""),
            px(11), blue_light);

        x += px(static_cast<int>(player.length()) * 5 + 12);
        if (x > width - px(80))
        {
            x = px(16);
            y += px(20);
        }
        ++index;
    }
}

void Environment::show_items()
{
    for (Component *component : item_components->children)
        delete component;

    item_components->children.clear();
    int index = 0;
    for (const string &item : items)
    {
        const int y = px(5 + index * 34);
        add_text(item_components, app, px(16), y, "ITEM", px(10), blue_light, px(1));
        add_text(item_components, app, px(70), y, item, px(11), text_color);

        item_components->children.push_back(new Button(
            app, width - px(63), y - px(5), px(47), px(24), "TAKE",
            [this, item]() {
                server->request("TAKE " + item);
                actualize = true;
            },
            {11, 26, 46, 255}, blue_light, 0,
            {37, 70, 107, 255}, {16, 39, 68, 255}, {11, 26, 46, 255},
            10, 1, true
        ));
        add_row_rule(item_components, app, px(16), y + px(26), width - px(16));
        ++index;
    }
    item_components->setContentHeight(px(5 + index * 34));
}

void Environment::look()
{
    const string response = server->request("LOOK");
    if (response.compare(0, 2, "OK") != 0)
        return;

    const json response_data = json::parse(response.substr(2));
    const json room = response_data.at("room");
    room_id->text = "LOCATION // " + room.at("id").get<string>();
    transform(room_id->text.begin(), room_id->text.end(), room_id->text.begin(),
        [](unsigned char character) {
            return static_cast<char>(toupper(character));
        });
    room_name->text = room.at("name").get<string>();
    room_description->text = room.at("description").get<string>();

    const json exits = room.at("exits");
    north_button->enabled = exits.contains("north");
    south_button->enabled = exits.contains("south");
    west_button->enabled = exits.contains("west");
    east_button->enabled = exits.contains("east");

    items = response_data.at("items").get<vector<string>>();
    players = response_data.at("players").get<vector<string>>();
    npcs = response_data.at("npcs").get<vector<string>>();

    show_items();
    show_players();
    show_npcs();
}