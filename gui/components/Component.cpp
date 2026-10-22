#include "Component.hpp"

Component::Component(App *app, int x, int y)
{
    this->app = app;
    this->x = x;
    this->y = y;
}
