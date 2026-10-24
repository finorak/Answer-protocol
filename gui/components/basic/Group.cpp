#include "Group.hpp"

Group::Group(App *app, int x, int y, std::initializer_list<Component *> children)
    : Component(app, x, y), children(children)
{
}

void Group::render(int origin_x, int origin_y)
{
    for (Component *child : children)
        child->render(origin_x + x, origin_y + y);
}

Group::~Group()
{
    for (Component *child : children)
        delete child;
}