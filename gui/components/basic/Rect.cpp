// Copyright 2026 mrazakam

#include "gui/components/basic/Rect.hpp"

Rect::Rect(App* app, int x, int y, int width, int height, SDL_Color fill_color,
           SDL_Color border_color, int border_width)
    : Component(app, x, y),
      width(width),
      height(height),
      fill_color(fill_color),
      border_color(border_color),
      border_width(border_width) {}

void Rect::render(int origin_x, int origin_y) {
  SDL_Rect rect = {origin_x + x, origin_y + y, width, height};
  SDL_BlendMode previous_blend;
  SDL_GetRenderDrawBlendMode(app->renderer, &previous_blend);
  if (fill_color.a > 0) {
    SDL_SetRenderDrawBlendMode(app->renderer, fill_color.a < 255
                                                  ? SDL_BLENDMODE_BLEND
                                                  : previous_blend);
    SDL_SetRenderDrawColor(app->renderer, fill_color.r, fill_color.g,
                           fill_color.b, fill_color.a);
    SDL_RenderFillRect(app->renderer, &rect);
  }

  if (border_width <= 0) {
    SDL_SetRenderDrawBlendMode(app->renderer, previous_blend);
    return;
  }

  SDL_SetRenderDrawBlendMode(app->renderer, border_color.a < 255
                                                ? SDL_BLENDMODE_BLEND
                                                : previous_blend);
  SDL_SetRenderDrawColor(app->renderer, border_color.r, border_color.g,
                         border_color.b, border_color.a);
  for (int inset = 0; inset < border_width; ++inset) {
    SDL_Rect border = {rect.x + inset, rect.y + inset, rect.w - inset * 2,
                       rect.h - inset * 2};
    if (border.w > 0 && border.h > 0)
      SDL_RenderDrawRect(app->renderer, &border);
  }
  SDL_SetRenderDrawBlendMode(app->renderer, previous_blend);
}
