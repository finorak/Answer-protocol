#include "Line.hpp"
#include <cmath>

Line::Line(App *app, int x, int y, int end_x, int end_y,
    SDL_Color color, int thickness)
    : Component(app, x, y), end_x(end_x), end_y(end_y),
      color(color), thickness(thickness)
{
}

void Line::render(int origin_x, int origin_y)
{
    SDL_BlendMode previous_blend;
    SDL_GetRenderDrawBlendMode(app->renderer, &previous_blend);
    SDL_SetRenderDrawBlendMode(app->renderer,
        color.a < 255 ? SDL_BLENDMODE_BLEND : previous_blend);
    SDL_SetRenderDrawColor(app->renderer, color.r, color.g, color.b, color.a);
    const float delta_x = static_cast<float>(end_x - x);
    const float delta_y = static_cast<float>(end_y - y);
    const float length = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    const float normal_x = length == 0 ? 0 : -delta_y / length;
    const float normal_y = length == 0 ? 0 : delta_x / length;
    const int first_offset = -(thickness - 1) / 2;
    const int last_offset = thickness / 2;

    for (int offset = first_offset; offset <= last_offset; ++offset)
    {
        SDL_RenderDrawLine(app->renderer,
            origin_x + x + static_cast<int>(std::lround(normal_x * offset)),
            origin_y + y + static_cast<int>(std::lround(normal_y * offset)),
            origin_x + end_x + static_cast<int>(std::lround(normal_x * offset)),
            origin_y + end_y + static_cast<int>(std::lround(normal_y * offset)));
    }
    SDL_SetRenderDrawBlendMode(app->renderer, previous_blend);
}