#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SDL2/SDL.h>
#include "../App.hpp"

class Component
{
    public:
        App *app;
        int x;
        int y;

        Component(App *app, int x, int y);
        virtual void render(int origin_x = 0, int origin_y = 0) = 0;
        virtual ~Component() = default;

};


#endif