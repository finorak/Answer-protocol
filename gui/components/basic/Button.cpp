#include "Button.hpp"
#include "../utils.hpp"

using namespace std;


Button::Button(App *app, int x, int y, int width, int height,
            string content, function<void()> onclick, SDL_Color color,
            SDL_Color text_color, int border_radius, SDL_Color border_color,
            SDL_Color hover_color, SDL_Color disabled_color, int font_size,
            int letter_spacing, bool centered)
    : Component(app, x, y)
{
    this->color = color;
    this->border_color = border_color;
    this->width = width;
    this->height = height;
    this->border_radius = border_radius;
    this->content = content;
    this->text_color = text_color;
    this->onclick = onclick;
    this->hover_color = hover_color;
    this->disabled_color = disabled_color;
    this->font_size = font_size;
    this->letter_spacing = letter_spacing;
    this->centered = centered;
    this->enabled = true;
    this->font = TTF_OpenFont("./assets/font/arial.ttf", font_size);
}

void Button::handleEvent(int x, int y, int width, int height)
{
    for (SDL_Event event: this->app->events)
    {
        if (enabled && event.type == SDL_MOUSEBUTTONDOWN
            && event.button.button == SDL_BUTTON_LEFT)
        {
            if (event.button.x >= x &&
                event.button.x <= x + width &&
                event.button.y >= y &&
                event.button.y <= y + height)
            {
                this->onclick();
            }
        }
    }
}


void Button::render(int origin_x, int origin_y)
{
    SDL_Rect rect = {
        origin_x + x,
        origin_y + y,
        width,
        height
    };

    if (enabled)
        handleEvent(origin_x + x, origin_y + y, width, height);

    SDL_Point mouse = {0, 0};
    SDL_GetMouseState(&mouse.x, &mouse.y);
    bool hovered = enabled && SDL_PointInRect(&mouse, &rect);
    SDL_Color current_color = !enabled ? disabled_color
        : hovered ? hover_color : color;
    SDL_BlendMode previous_blend;
    SDL_GetRenderDrawBlendMode(app->renderer, &previous_blend);
    SDL_SetRenderDrawBlendMode(app->renderer,
        current_color.a < 255 ? SDL_BLENDMODE_BLEND : previous_blend);

    drawFilledRoundedRect(
        app->renderer,
        rect,
        this->border_radius,
        current_color
    );

    SDL_SetRenderDrawBlendMode(app->renderer,
        border_color.a < 255 ? SDL_BLENDMODE_BLEND : previous_blend);
    drawRoundedBorder(
        app->renderer,
        rect,
        this->border_radius,
        border_color
    );
    SDL_SetRenderDrawBlendMode(app->renderer, previous_blend);

    if (!font || content.empty())
        return;

    int label_width = measureTextWidth(font, content, letter_spacing);
    int text_x = centered ? rect.x + (width - label_width) / 2
        : rect.x + height / 6;
    int text_y = rect.y + (height - TTF_FontHeight(font)) / 2;

    renderText(app->renderer, font, content, text_x, text_y,
        text_color, letter_spacing);
}

Button::~Button()
{
    if (font)
        TTF_CloseFont(font);
}
