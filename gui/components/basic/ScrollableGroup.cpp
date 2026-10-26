#include "ScrollableGroup.hpp"
#include <algorithm>

ScrollableGroup::ScrollableGroup(App *app, int x, int y, int width, int height,
    std::initializer_list<Component *> children)
    : Group(app, x, y, children), width(width), height(height),
      content_height(0), scroll_offset(0)
{
}

void ScrollableGroup::setContentHeight(int height)
{
    content_height = std::max(0, height);
    scroll_offset = std::min(scroll_offset,
        std::max(0, content_height - this->height));
}

void ScrollableGroup::render(int origin_x, int origin_y)
{
    const int viewport_x = origin_x + x;
    const int viewport_y = origin_y + y;
    const SDL_Rect viewport = {viewport_x, viewport_y, width, height};
    int mouse_x = 0;
    int mouse_y = 0;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    const bool mouse_inside = mouse_x >= viewport.x
        && mouse_x < viewport.x + viewport.w
        && mouse_y >= viewport.y
        && mouse_y < viewport.y + viewport.h;

    if (mouse_inside)
    {
        for (const SDL_Event &event : app->events)
        {
            if (event.type == SDL_MOUSEWHEEL)
            {
                scroll_offset = std::max(0, std::min(
                    std::max(0, content_height - height),
                    scroll_offset - event.wheel.y * 36));
            }
        }
    }

    SDL_Rect previous_clip;
    SDL_RenderGetClipRect(app->renderer, &previous_clip);
    const SDL_bool had_clip = SDL_RenderIsClipEnabled(app->renderer);
    SDL_Rect effective_clip = viewport;
    if (had_clip)
        SDL_IntersectRect(&viewport, &previous_clip, &effective_clip);
    SDL_RenderSetClipRect(app->renderer, &effective_clip);

    std::vector<SDL_Event> visible_events;
    visible_events.reserve(app->events.size());
    for (const SDL_Event &event : app->events)
    {
        if (event.type != SDL_MOUSEBUTTONDOWN
            || (event.button.x >= viewport.x
                && event.button.x < viewport.x + viewport.w
                && event.button.y >= viewport.y
                && event.button.y < viewport.y + viewport.h))
            visible_events.push_back(event);
    }

    app->events.swap(visible_events);
    for (Component *child : children)
        child->render(viewport_x, viewport_y - scroll_offset);
    app->events.swap(visible_events);

    SDL_RenderSetClipRect(app->renderer, had_clip ? &previous_clip : nullptr);
}