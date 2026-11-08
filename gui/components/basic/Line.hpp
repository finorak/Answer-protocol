#ifndef LINE_HPP
#define LINE_HPP

#include "../Component.hpp"

class Line : public Component
{
    public:
        int end_x;
        int end_y;
        SDL_Color color;
        int thickness;

        Line(App *app, int x, int y, int end_x, int end_y,
            SDL_Color color, int thickness = 1);
        void render(int origin_x = 0, int origin_y = 0) override;
};

#endif