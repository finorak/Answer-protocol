#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "../Component.hpp"

class Circle : public Component
{
    public:
        int radius;
        SDL_Color color;
        bool filled;
        int thickness;

        Circle(App *app, int center_x, int center_y, int radius,
            SDL_Color color, bool filled = false, int thickness = 1);
        void render(int origin_x = 0, int origin_y = 0) override;
};

#endif