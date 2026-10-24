#include "TAPInterfaceHelpers.hpp"
#include "../basic/Button.hpp"
#include "../basic/Group.hpp"
#include "../basic/Line.hpp"
#include "../basic/Rect.hpp"
#include "../basic/Text.hpp"

namespace TAPUI
{
    const SDL_Color background = {5, 9, 20, 255};
    const SDL_Color panel_color = {9, 20, 38, 255};
    const SDL_Color panel_dark = {5, 11, 23, 255};
    const SDL_Color blue = {22, 140, 255, 255};
    const SDL_Color blue_light = {101, 197, 255, 255};
    const SDL_Color text_color = {220, 236, 255, 255};
    const SDL_Color muted = {113, 137, 168, 255};
    const SDL_Color border = {25, 57, 88, 255};
    const SDL_Color row_border = {20, 38, 61, 255};
    const SDL_Color warning = {255, 207, 107, 255};
    const SDL_Color error = {255, 119, 119, 255};

    Text *add_text(Group *group, App *app, int x, int y, std::string text,
        int size, SDL_Color color, int tracking)
    {
        Text *component = new Text(app, x, y, text, size, color, tracking);
        group->children.push_back(component);
        return component;
    }

    void add_button(Group *group, App *app, int x, int y, int width,
        std::string label, int height)
    {
        group->children.push_back(new Button(app, x, y, width, height, label,
            []() {}, {11, 26, 46, 255}, blue_light, 0,
            {37, 70, 107, 255}, {16, 39, 68, 255}, {11, 26, 46, 255},
            10, 1, true));
    }

    Group *create_panel(App *app, int width, int height, const std::string &title)
    {
        Group *panel = new Group(app, 0, 54, {});
        panel->children.push_back(new Rect(app, 0, 0, width, height,
            panel_color, border, 1));
        add_text(panel, app, 16, 16, title, 10, blue_light, 2);
        panel->children.push_back(new Line(app, 16, 38, width - 16, 38, border));
        return panel;
    }

    void add_row_rule(Group *group, App *app, int x, int y, int end_x)
    {
        group->children.push_back(new Line(app, x, y, end_x, y, row_border));
    }

    void add_chat_line(Group *group, App *app, int x, int y, int end_x,
        const std::string &time, const std::string &user,
        const std::string &message, SDL_Color user_color)
    {
        add_text(group, app, x, y, time, 10, muted);
        add_text(group, app, x + 44, y, "[" + user + "]", 10, user_color);
        add_text(group, app, x + 132, y, message, 10, text_color);
        add_row_rule(group, app, x, y + 20, end_x);
    }
}
