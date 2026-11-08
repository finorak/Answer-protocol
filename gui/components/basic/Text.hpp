#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Component.hpp"

class Text : public Component
{
    public:
        std::string text;
        int size;
        SDL_Color color;
        TTF_Font* font;
        int letter_spacing;

        Text(
            App *app,
            int x,
            int y,
            std::string text,
            int size,
            SDL_Color color,
            int letter_spacing = 0
        );

        void render(int origin_x = 0, int origin_y = 0) override;
        int measureWidth() const;
        ~Text();
};

#endif
