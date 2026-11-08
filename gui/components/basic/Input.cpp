// Copyright 2026 mrazakam

#include "gui/components/basic/Input.hpp"

#include <string>

#include "gui/components/utils.hpp"

using std::function;
using std::string;

Input::Input(App* app, int x, int y, int width, int height, string* content,
             bool* focused, SDL_Color color, SDL_Color text_color,
             int border_radius, SDL_Color border_color, string placeholder,
             string prefix, int max_length, int font_size,
             SDL_Color placeholder_color, function<void()> on_submit,
             SDL_Color focus_border_color, SDL_Color prefix_color)
    : Component(app, x, y) {
  this->color = color;
  this->border_color = border_color;
  this->width = width;
  this->height = height;
  this->border_radius = border_radius;
  this->content = content;
  this->text_color = text_color;
  this->focused = focused;
  this->focus_border_color = focus_border_color;
  this->prefix_color = prefix_color;
  this->placeholder = placeholder;
  this->prefix = prefix;
  this->max_length = max_length;
  this->font_size = font_size;
  this->placeholder_color = placeholder_color;
  this->padding_x = 13;
  this->prefix_gap = 15;
  this->read_only = false;
  this->on_submit = on_submit;
  this->font = TTF_OpenFont("./assets/font/arial.ttf", font_size);
}

void Input::handleEvent(int x, int y, int width, int height) {
  for (SDL_Event event : this->app->events) {
    if (*focused) {
      if (!read_only && event.type == SDL_TEXTINPUT) {
        string next = *content + event.text.text;
        if (max_length <= 0 || countUtf8Characters(next) <= max_length)
          *content = next;
      }
      if (!read_only && event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE && !content->empty()) {
          size_t position = content->size() - 1;
          while (position > 0 &&
                 (static_cast<unsigned char>((*content)[position]) & 0xc0) ==
                     0x80)
            --position;
          content->erase(position);
        } else if ((event.key.keysym.sym == SDLK_RETURN ||
              event.key.keysym.sym == SDLK_KP_ENTER) &&
             on_submit) {
          on_submit();
        }
      }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (!read_only && event.button.x >= x && event.button.x <= x + width &&
          event.button.y >= y && event.button.y <= y + height) {
        *(this->focused) = true;
      } else {
        *(this->focused) = false;
      }
    }
  }
}

void Input::render(int origin_x, int origin_y) {
  SDL_Rect rect = {origin_x + x, origin_y + y, width, height};

  handleEvent(origin_x + x, origin_y + y, width, height);

  SDL_BlendMode previous_blend;
  SDL_GetRenderDrawBlendMode(app->renderer, &previous_blend);
  SDL_SetRenderDrawBlendMode(
      app->renderer, color.a < 255 ? SDL_BLENDMODE_BLEND : previous_blend);
  drawFilledRoundedRect(app->renderer, rect, border_radius, color);
  SDL_SetRenderDrawBlendMode(
      app->renderer,
      (*focused && !read_only ? focus_border_color.a : border_color.a) < 255
          ? SDL_BLENDMODE_BLEND
          : previous_blend);
  drawRoundedBorder(app->renderer, rect, border_radius,
                    *focused && !read_only ? focus_border_color : border_color);
  SDL_SetRenderDrawBlendMode(app->renderer, previous_blend);
  if (!font) return;

  int prefix_x = rect.x + padding_x;
  int text_x =
      prefix_x +
      (prefix.empty() ? 0 : measureTextWidth(font, prefix) + prefix_gap);
  int text_y = rect.y + (height - TTF_FontHeight(font)) / 2;
  if (!prefix.empty())
    renderText(app->renderer, font, prefix, prefix_x, text_y, prefix_color);

  SDL_Rect previous_clip;
  SDL_RenderGetClipRect(app->renderer, &previous_clip);
  SDL_bool had_clip = SDL_RenderIsClipEnabled(app->renderer);
  SDL_Rect text_clip = {text_x, rect.y + 1,
                        rect.w - (text_x - rect.x) - padding_x, rect.h - 2};
  SDL_RenderSetClipRect(app->renderer, &text_clip);
  const string& visible_text = content->empty() ? placeholder : *content;
  renderText(app->renderer, font, visible_text, text_x, text_y,
             content->empty() ? placeholder_color : text_color);
  if (*focused && !read_only && SDL_GetTicks() % 1000 < 500) {
    int caret_x = text_x + measureTextWidth(font, *content);
    SDL_SetRenderDrawColor(app->renderer, text_color.r, text_color.g,
                           text_color.b, text_color.a);
    SDL_RenderDrawLine(app->renderer, caret_x, text_y, caret_x,
                       text_y + TTF_FontHeight(font));
  }
  SDL_RenderSetClipRect(app->renderer, had_clip ? &previous_clip : nullptr);
}

Input::~Input() {
  if (font) TTF_CloseFont(font);
}
