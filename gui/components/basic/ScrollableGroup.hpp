#ifndef SCROLLABLE_GROUP_HPP
#define SCROLLABLE_GROUP_HPP

#include "Group.hpp"

class ScrollableGroup : public Group
{
    public:
        int width;
        int height;
        int content_height;
        int scroll_offset;

        ScrollableGroup(App *app, int x, int y, int width, int height,
            std::initializer_list<Component *> children);
        void setContentHeight(int height);
        void render(int origin_x = 0, int origin_y = 0) override;
};

#endif