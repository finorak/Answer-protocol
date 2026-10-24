#ifndef TAPINTERFACEHELPERS_HPP
#define TAPINTERFACEHELPERS_HPP

#include <SDL2/SDL.h>
#include <string>

class App;
class Group;
class Text;

namespace TAPUI
{
    extern const SDL_Color background;
    extern const SDL_Color panel_color;
    extern const SDL_Color panel_dark;
    extern const SDL_Color blue;
    extern const SDL_Color blue_light;
    extern const SDL_Color text_color;
    extern const SDL_Color muted;
    extern const SDL_Color border;
    extern const SDL_Color row_border;
    extern const SDL_Color warning;
    extern const SDL_Color error;

    Text *add_text(Group *group, App *app, int x, int y, std::string text,
        int size, SDL_Color color, int tracking = 0);
    void add_button(Group *group, App *app, int x, int y, int width,
        std::string label, int height = 26);
    Group *create_panel(App *app, int width, int height, const std::string &title);
    void add_row_rule(Group *group, App *app, int x, int y, int end_x);
    void add_chat_line(Group *group, App *app, int x, int y, int end_x,
        const std::string &time, const std::string &user,
        const std::string &message, SDL_Color user_color = blue_light);
}

#endif
