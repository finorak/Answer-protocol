#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../Component.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>

class Button : public Component
{
    public:
        SDL_Color color;
        SDL_Color text_color;
        SDL_Color border_color;
        int width;
        int height;
        int border_radius;
        std::string content;
        std::function<void()> onclick;
        SDL_Color hover_color;
        SDL_Color disabled_color;
        int font_size;
        int letter_spacing;
        bool centered;
        bool enabled;
        TTF_Font *font;

        Button(App *app, int x, int y, int width, int height, std::string content,
            std::function<void()> onclick, SDL_Color color, SDL_Color text_color,
            int border_radius, SDL_Color border_color, SDL_Color hover_color,
            SDL_Color disabled_color, int font_size, int letter_spacing,
            bool centered);
        void render(int origin_x = 0, int origin_y = 0) override;
        void handleEvent(int x, int y, int width, int height);
        ~Button();
};


#endif