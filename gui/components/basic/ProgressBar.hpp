#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "../Component.hpp"

class ProgressBar : public Component
{
    public:
        SDL_Color color;
        SDL_Color progression_color;
        SDL_Color border_color;
        int width;
        int height;
        int border_radius;
        int progression;

        ProgressBar(App *app, int x, int y,
            int width, int height, SDL_Color color, int progression, SDL_Color progression_color, int border_radius, SDL_Color border_color);
        void render(int origin_x = 0, int origin_y = 0) override;
};


#endif