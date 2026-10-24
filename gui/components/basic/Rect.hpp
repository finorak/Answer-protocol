#ifndef RECT_HPP
#define RECT_HPP

#include "../Component.hpp"

class Rect : public Component
{
    public:
        int width;
        int height;
        SDL_Color fill_color;
        SDL_Color border_color;
        int border_width;

        Rect(App *app, int x, int y, int width, int height,
            SDL_Color fill_color, SDL_Color border_color = {0, 0, 0, 0},
            int border_width = 0);
        void render(int origin_x = 0, int origin_y = 0) override;
};

#endif