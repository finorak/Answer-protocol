#ifndef GROUP_HPP
#define GROUP_HPP

#include "../Component.hpp"
#include <initializer_list>
#include <vector>

class Group : public Component
{
    public:
        std::vector<Component *> children;

        Group(App *app, int x, int y, std::initializer_list<Component *> children);
        Group(const Group &) = delete;
        Group &operator=(const Group &) = delete;
        Group(Group &&) = delete;
        Group &operator=(Group &&) = delete;
        void render(int origin_x = 0, int origin_y = 0) override;
        ~Group();
};

#endif