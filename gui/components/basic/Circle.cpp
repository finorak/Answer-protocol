#include "Circle.hpp"
#include <cmath>

Circle::Circle(App *app, int center_x, int center_y, int radius,
    SDL_Color color, bool filled, int thickness)
    : Component(app, center_x, center_y), radius(radius), color(color),
      filled(filled), thickness(thickness)
{
}

void Circle::render(int origin_x, int origin_y)
{
    SDL_BlendMode previous_blend;
    SDL_GetRenderDrawBlendMode(app->renderer, &previous_blend);
    SDL_SetRenderDrawBlendMode(app->renderer,
        color.a < 255 ? SDL_BLENDMODE_BLEND : previous_blend);
    SDL_SetRenderDrawColor(app->renderer, color.r, color.g, color.b, color.a);
    const int center_x = origin_x + x;
    const int center_y = origin_y + y;
    const int inner_radius = filled ? 0 : std::max(0, radius - thickness + 1);
    const int outer_radius = radius;

    for (int y_offset = -outer_radius; y_offset <= outer_radius; ++y_offset)
    {
        const int outer_x = static_cast<int>(std::sqrt(
            outer_radius * outer_radius - y_offset * y_offset));
        if (filled)
        {
            SDL_RenderDrawLine(app->renderer, center_x - outer_x, center_y + y_offset,
                center_x + outer_x, center_y + y_offset);
            continue;
        }

        if (std::abs(y_offset) > inner_radius)
        {
            SDL_RenderDrawPoint(app->renderer, center_x - outer_x, center_y + y_offset);
            SDL_RenderDrawPoint(app->renderer, center_x + outer_x, center_y + y_offset);
        }
        else
        {
            const int inner_x = static_cast<int>(std::sqrt(
                inner_radius * inner_radius - y_offset * y_offset));
            SDL_RenderDrawLine(app->renderer, center_x - outer_x, center_y + y_offset,
                center_x - inner_x, center_y + y_offset);
            SDL_RenderDrawLine(app->renderer, center_x + inner_x, center_y + y_offset,
                center_x + outer_x, center_y + y_offset);
        }
    }
    SDL_SetRenderDrawBlendMode(app->renderer, previous_blend);
}