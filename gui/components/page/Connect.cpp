#include "Connect.hpp"
#include "../basic/Button.hpp"
#include "../basic/Circle.hpp"
#include "../basic/Group.hpp"
#include "../basic/Input.hpp"
#include "../basic/Line.hpp"
#include "../basic/Rect.hpp"
#include "../basic/Text.hpp"
#include "../../Server.hpp"
#include "../../common.h"
#include <regex>
#include <iostream>

using namespace std;

namespace
{
    const SDL_Color background = {5, 9, 20, 255};
    const SDL_Color panel = {9, 20, 38, 255};
    const SDL_Color visual_panel = {7, 19, 38, 255};
    const SDL_Color blue = {22, 140, 255, 255};
    const SDL_Color blue_light = {101, 197, 255, 255};
    const SDL_Color text_color = {220, 236, 255, 255};
    const SDL_Color muted = {113, 137, 168, 255};
    const SDL_Color border = {25, 57, 88, 255};
}

Connect::Connect(App *app, int width, int height, Server *server,
    function<void(string u)> on_connect_success)
    : Component(app, 0, 0), width(width), height(height), server(server),
      input_content(""), input_focused(true), message(""), confirmed(false),
      on_connect_success(on_connect_success), screen(nullptr), heading(nullptr),
      description_line_one(nullptr), description_line_two(nullptr),
      description_line_three(nullptr), status_message(nullptr),
      username_input(nullptr), submit_button(nullptr)
{
    const float scale = max(0.1f, min(1.0f, min((width - 48.0f) / 1000.0f,
        (height - 48.0f) / 627.0f)));
    auto px = [scale](float value) { return static_cast<int>(lround(value * scale)); };
    const int page_x = (width - px(1000)) / 2;
    const int page_y = (height - px(627)) / 2;
    Group *page = new Group(app, page_x, page_y, {});

    page->children.push_back(new Rect(app, 0, px(36), px(1000), px(560), panel));
    page->children.push_back(new Rect(app, 0, px(36), px(1000), px(560),
        {0, 0, 0, 0}, border, px(1)));
    page->children.push_back(new Rect(app, 0, px(36), px(500), px(560), visual_panel));

    const SDL_Color grid = {22, 140, 255, 18};
    for (int offset = 0; offset <= 480; offset += 30)
        page->children.push_back(new Line(app, px(offset), px(36),
            px(offset), px(596), grid));
    for (int offset = 0; offset <= 540; offset += 30)
        page->children.push_back(new Line(app, 0, px(36 + offset),
            px(500), px(36 + offset), grid));
    page->children.push_back(new Line(app, px(500), px(36), px(500), px(596), border));

    page->children.push_back(new Circle(app, px(250), px(316), px(140),
        {22, 140, 255, 89}));
    page->children.push_back(new Line(app, px(180), px(316), px(320), px(316), blue));
    page->children.push_back(new Line(app, px(250), px(246), px(250), px(386), blue));
    page->children.push_back(new Rect(app, px(196), px(262), px(108), px(108), background));
    page->children.push_back(new Rect(app, px(196), px(262), px(108), px(108),
        {0, 0, 0, 0}, blue, px(1)));

    Text *status = new Text(app, px(0), px(0), "SYSTEM ONLINE", px(10), muted, px(2));
    status->x = px(1000 - 16) - status->measureWidth();
    page->children.push_back(new Text(app, 0, 0, "TAP // IDENTIFICATION", px(10), muted, px(2)));
    page->children.push_back(new Circle(app, status->x - px(12.5f), px(5),
        px(3), blue_light, true));
    page->children.push_back(status);
    page->children.push_back(new Text(app, px(38), px(74), "T A P", px(13), blue_light, px(5)));
    page->children.push_back(new Text(app, px(38), px(96),
        "THE ANSWER PROTOCOL", px(10), muted, px(2)));
    page->children.push_back(new Text(app, px(250) - px(8), px(296),
        "?", px(30), blue_light, px(4)));
    page->children.push_back(new Text(app, px(38), px(498), "NETWORK", px(10), muted, px(1)));
    page->children.push_back(new Text(app, px(112), px(498), "CONNECTED", px(10), blue_light, px(1)));
    page->children.push_back(new Text(app, px(38), px(518), "PROTOCOL", px(10), muted, px(1)));
    page->children.push_back(new Text(app, px(111), px(518), "01.000", px(10), blue_light, px(1)));
    page->children.push_back(new Text(app, px(38), px(538),
        "AWAITING USER IDENTIFICATION", px(10), muted, px(1)));

    page->children.push_back(new Text(app, px(548), px(84),
        "IDENTIFICATION PROTOCOL", px(10), blue_light, px(3)));
    heading = new Text(app, px(548), px(121), "Enter the protocol.", px(36), text_color, px(1));
    description_line_one = new Text(app, px(548), px(179),
        "Every player has a story.", px(13), muted);
    description_line_two = new Text(app, px(548), px(202),
        "Not everyone is ready to compete.", px(13), muted);
    description_line_three = new Text(app, px(548), px(225),
        "Enter your identity to continue.", px(13), muted);
    page->children.push_back(heading);
    page->children.push_back(description_line_one);
    page->children.push_back(description_line_two);
    page->children.push_back(description_line_three);
    page->children.push_back(new Text(app, px(548), px(287),
        "USERNAME", px(10), {169, 197, 228, 255}, px(2)));

    username_input = new Input(app, px(548), px(311), px(404), px(50),
        &input_content, &input_focused, {5, 11, 23, 255}, text_color, 0,
        border, "Enter your username", ">_", 24, px(14),
        {79, 101, 128, 255}, [this]() { submit(); });
    username_input->padding_x = px(15);
    username_input->prefix_gap = px(16);
    page->children.push_back(username_input);
    submit_button = new Button(app, px(548), px(381), px(404), px(47),
        "INITIALIZE SESSION  \xe2\x86\x92", [this]() { submit(); }, blue,
        {255, 255, 255, 255}, 0, blue, {8, 116, 219, 255},
        {22, 140, 255, 166}, px(11), px(2), true);
    page->children.push_back(submit_button);
    status_message = new Text(app, px(548), px(445), "", px(11), blue_light);
    page->children.push_back(status_message);
    page->children.push_back(new Line(app, px(548), px(507), px(952), px(507), border));
    page->children.push_back(new Text(app, px(548), px(528),
        "ACCESS LEVEL: USER", px(9), muted, px(1)));
    Text *security_note = new Text(app, 0, px(528),
        "NO PASSWORD REQUIRED", px(9), muted, px(1));
    security_note->x = px(952) - security_note->measureWidth();
    page->children.push_back(security_note);
    page->children.push_back(new Text(app, 0, px(616),
        "THE ANSWER PROTOCOL", px(9), {83, 106, 133, 255}, px(1.5f)));
    Text *footer_right = new Text(app, 0, px(616),
        "ENTER THE GAME.", px(9), {83, 106, 133, 255}, px(1.5f));
    footer_right->x = px(1000) - footer_right->measureWidth();
    page->children.push_back(footer_right);

    screen = new Group(app, 0, 0, {
        new Rect(app, 0, 0, width, height, background),
        page
    });
}

void Connect::render(int origin_x, int origin_y)
{
    screen->render(origin_x, origin_y);
}

void Connect::submit()
{
    size_t first = input_content.find_first_not_of(" \t\r\n");
    size_t last = input_content.find_last_not_of(" \t\r\n");
    string username = first == string::npos
        ? "" : input_content.substr(first, last - first + 1);
    static const regex valid_username("^[A-Za-z0-9_-]{2,24}$");
    if (!regex_match(username, valid_username))
    {
        message = "INVALID IDENTITY. CHECK YOUR USERNAME.";
        status_message->text = message;
        input_focused = true;
        return;
    }

    string request = "CONNECT " + username;
    string response = server->request(request);
    if (response.substr(0, 2) == "OK")
    {
        cout << "Connected: " << response;
        message = "IDENTITY ACCEPTED. WELCOME, " + username + ".";
        status_message->text = message;
        confirmed = true;
        input_focused = false;
        username_input->read_only = true;
        submit_button->content = "SESSION INITIALIZED";
        submit_button->enabled = false;
        heading->text = "Identity confirmed.";
        description_line_one->text = "Your identity has been registered for this session.";
        description_line_two->text = "The protocol is awaiting its next instruction.";
        description_line_three->text = "";
        this->on_connect_success(username);
    }
    else
    {
        if (response.substr(0, 19) == "ERR 201 NAME_IN_USE")
        {
            message = "NAME ALREADY IN USE. CHOOSE ANOTHER USERNAME";
            status_message->text = message;
            input_focused = true;
            return;
        }
    }
}

Connect::~Connect()
{
    delete screen;
}
