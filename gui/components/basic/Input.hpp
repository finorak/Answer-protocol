#ifndef INPUT_HPP
#define INPUT_HPP

#include "../Component.hpp"
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <string>

class Input : public Component
{
    public:
        SDL_Color color;
        SDL_Color text_color;
        SDL_Color border_color;
        SDL_Color focus_border_color;
        SDL_Color prefix_color;
        int width;
        int height;
        int border_radius;
        std::string *content;
        bool *focused;
        std::string placeholder;
        std::string prefix;
        SDL_Color placeholder_color;
        int max_length;
        int font_size;
        int padding_x;
        int prefix_gap;
        bool read_only;
        std::function<void()> on_submit;
        TTF_Font *font;

        Input(App *app, int x, int y, int width, int height,
            std::string *content, bool *focused, SDL_Color color, SDL_Color text_color,
            int border_radius, SDL_Color border_color, std::string placeholder,
            std::string prefix, int max_length, int font_size,
            SDL_Color placeholder_color, std::function<void()> on_submit = nullptr,
            SDL_Color focus_border_color = {22, 140, 255, 255},
            SDL_Color prefix_color = {22, 140, 255, 255});
        void render(int origin_x = 0, int origin_y = 0) override;
        void handleEvent(int x, int y, int width, int height);
        ~Input();
};


#endif