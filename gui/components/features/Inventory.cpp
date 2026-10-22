#include "Inventory.hpp"
#include "TAPInterfaceHelpers.hpp"
#include "../basic/Group.hpp"
#include "../basic/Input.hpp"
#include "../basic/Line.hpp"
#include "../basic/Rect.hpp"
#include "../basic/Button.hpp"
#include "../../Server.hpp"
#include <algorithm>
#include <cmath>
#include "../../json.hpp"

using json = nlohmann::json;
using namespace TAPUI;
using namespace std;

Inventory::Inventory(App *app, int x, int width, int panel_height, float scale,
    string &chat_message, bool &chat_focused, Server *server)
        : Component(app, x, 0), actualize(false), width(width), panel(nullptr),
            chat_message(chat_message), chat_focused(chat_focused), server(server),
            chat_mode(0)
{
    px = [scale](float value) { return static_cast<int>(lround(value * scale)); };
    Group *inventory = create_panel(app, width, panel_height, "02 / INVENTORY");
    inventory_components = new Group(app, 0, 0, {});
    inventory->children.push_back(inventory_components);

    chat_messages = {};
    chat_components = new Group(app, 0, 0, {});
    inventory->children.push_back(chat_components);

    show_chat();

    const int chatbox_y = px(684);
    const int input_height = px(36);
    chat_mode_button = new Button(
        app,
        px(16), chatbox_y, px(74), input_height,
        "GLOBAL",
        [this]() {
            chat_mode = (chat_mode + 1) % 3;

            const char *modes[] = {"GLOBAL", "ROOM", "GROUP"};
            chat_mode_button->content = modes[chat_mode];
        },
        panel_dark, blue_light, 1,
        {37, 70, 107, 255},
        {16, 39, 68, 255},
        {65, 72, 82, 255},
        9, 0, true
    );
    inventory->children.push_back(chat_mode_button);

    Input *chat_input = new Input(app, px(96), chatbox_y, width - px(194), input_height,
        &chat_message, &chat_focused, panel_dark, text_color, 0, {37, 70, 107, 255},
        "Enter message...", "", 0, px(12), {97, 120, 149, 255});
    inventory->children.push_back(chat_input);
    inventory->children.push_back(new Button(
        app,
        width - px(88), chatbox_y,
        px(72), input_height,
        "SEND",
        [this]() {
            if (this->chat_message.empty())
                return;

            const char *modes[] = {"GLOBAL", "ROOM", "GROUP"};

            string request_msg =
                "CHAT " + string(modes[chat_mode]) + " " + this->chat_message;

            this->server->request(request_msg);
        },
        {11, 26, 46, 255},
        blue_light, 0,
        {37, 70, 107, 255},
        {16, 39, 68, 255},
        {65, 72, 82, 255},
        10, 1, true
    ));
    panel = inventory;
}

void Inventory::show_chat()
{
    for (Component *component : chat_components->children)
        delete component;

    chat_components->children.clear();

    const int inventory_end = width - px(16);

    const std::string channels[] = {
        "GLOBAL", "ROOM", "GROUP"
    };

    const std::string titles[] = {
        "GLOBAL COMMUNICATION",
        "ROOM COMMUNICATION",
        "GROUP COMMUNICATION"
    };

    int y = px(218);

    for (int channel_index = 0; channel_index < 3; ++channel_index)
    {
        const std::string &channel = channels[channel_index];

        add_text(
            chat_components, app,
            px(16), y,
            titles[channel_index],
            px(10), blue_light, px(2)
        );

        y += px(22);

        add_row_rule(
            chat_components, app,
            px(16), y, inventory_end
        );

        y += px(10);

        // Compter les messages de ce canal.
        int count = 0;

        for (const ChatMessage &msg : chat_messages)
        {
            if (msg.channel == channel)
                ++count;
        }

        // Nombre de messages anciens à ignorer.
        const int skip = std::max(0, count - 4);
        int current = 0;

        for (const ChatMessage &msg : chat_messages)
        {
            if (msg.channel != channel)
                continue;

            if (current++ < skip)
                continue;

            add_chat_line(
                chat_components, app,
                px(16), y, inventory_end,
                msg.time,
                msg.author,
                msg.message
            );

            y += px(22);
        }

        y += px(9);
    }
}

void Inventory::render(int origin_x, int origin_y)
{
    panel->render(origin_x + x, origin_y + y);
}

void Inventory::show_inventory()
{
    for (Component *component : inventory_components->children)
        delete component;

    inventory_components->children.clear();

    const int inventory_end = width - px(16);
    int index = 0;

    for (const string &item : inventory_item)
    {
        int y = px(52 + index * 31);

        add_text(
            inventory_components, app,
            px(16), y,
            item, px(11), text_color
        );

        inventory_components->children.push_back(new Button(
            app,
            width - px(78),
            y - px(5),
            px(62),
            px(24),
            "DROP",
            [this, item]() {
                string response = this->server->request("DROP " + item);

                this->actualize = true;
            },
            {11, 26, 46, 255},
            blue_light,
            0,
            {37, 70, 107, 255},
            {16, 39, 68, 255},
            {65, 72, 82, 255},
            10, 1, true
        ));

        add_row_rule(
            inventory_components, app,
            px(16), y + px(25),
            inventory_end
        );

        ++index;
    }
}

void Inventory::update_inventory()
{
    string response = this->server->request("INVENTORY");

    if (response.substr(0, 2) != "OK")
        return ;
    inventory_item = json::parse(response.substr(2)).get<vector<string>>();
    show_inventory();
}

void Inventory::add_message(
    string time,
    string author,
    string message,
    string channel
)
{
    chat_messages.push_back({
        time, author, message, channel
    });

    int channel_count = 0;
    for (const ChatMessage &chat : chat_messages)
    {
        if (chat.channel == channel)
            ++channel_count;
    }
    while (channel_count > 4)
    {
        auto oldest = std::find_if(chat_messages.begin(), chat_messages.end(),
            [&channel](const ChatMessage &chat) {
                return chat.channel == channel;
            });
        if (oldest == chat_messages.end())
            break;
        chat_messages.erase(oldest);
        --channel_count;
    }

    show_chat();
}

Inventory::~Inventory()
{
    delete panel;
}
