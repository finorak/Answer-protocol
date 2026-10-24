#include <cmath>
#include <algorithm>
#include "utils.hpp"

void drawFilledRoundedRect(
    SDL_Renderer* renderer,
    SDL_Rect& rect,
    int radius,
    SDL_Color color
)
{
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        color.a
    );

    // Évite que le radius dépasse la moitié du rectangle
    radius = std::min(radius, rect.w / 2);
    radius = std::min(radius, rect.h / 2);

    // Centre
    SDL_Rect center = {
        rect.x + radius,
        rect.y,
        rect.w - 2 * radius,
        rect.h
    };
    SDL_RenderFillRect(renderer, &center);

    SDL_Rect middle = {
        rect.x,
        rect.y + radius,
        rect.w,
        rect.h - 2 * radius
    };
    SDL_RenderFillRect(renderer, &middle);

    // Dessiner les 4 coins
    for (int dy = 0; dy < radius; ++dy)
    {
        int dx = static_cast<int>(
            std::sqrt(radius * radius - dy * dy)
        );

        // Coin supérieur gauche
        SDL_RenderDrawLine(
            renderer,
            rect.x + radius - dx,
            rect.y + radius - dy,
            rect.x + radius,
            rect.y + radius - dy
        );

        // Coin supérieur droit
        SDL_RenderDrawLine(
            renderer,
            rect.x + rect.w - radius,
            rect.y + radius - dy,
            rect.x + rect.w - radius + dx,
            rect.y + radius - dy
        );

        // Coin inférieur gauche
        SDL_RenderDrawLine(
            renderer,
            rect.x + radius - dx,
            rect.y + rect.h - radius + dy,
            rect.x + radius,
            rect.y + rect.h - radius + dy
        );

        // Coin inférieur droit
        SDL_RenderDrawLine(
            renderer,
            rect.x + rect.w - radius,
            rect.y + rect.h - radius + dy,
            rect.x + rect.w - radius + dx,
            rect.y + rect.h - radius + dy
        );
    }
}

void drawRoundedBorder(
    SDL_Renderer* renderer,
    SDL_Rect& rect,
    int radius,
    SDL_Color color
)
{
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        color.a
    );

    radius = std::min(radius, rect.w / 2);
    radius = std::min(radius, rect.h / 2);

    // Bords horizontaux
    SDL_RenderDrawLine(
        renderer,
        rect.x + radius,
        rect.y,
        rect.x + rect.w - radius,
        rect.y
    );

    SDL_RenderDrawLine(
        renderer,
        rect.x + radius,
        rect.y + rect.h - 1,
        rect.x + rect.w - radius,
        rect.y + rect.h - 1
    );

    // Bords verticaux
    SDL_RenderDrawLine(
        renderer,
        rect.x,
        rect.y + radius,
        rect.x,
        rect.y + rect.h - radius
    );

    SDL_RenderDrawLine(
        renderer,
        rect.x + rect.w - 1,
        rect.y + radius,
        rect.x + rect.w - 1,
        rect.y + rect.h - radius
    );

    // Coins
    for (int angle = 0; angle <= 90; ++angle)
    {
        double rad = angle * M_PI / 180.0;

        int dx = static_cast<int>(radius * std::cos(rad));
        int dy = static_cast<int>(radius * std::sin(rad));

        // Haut gauche
        SDL_RenderDrawPoint(
            renderer,
            rect.x + radius - dx,
            rect.y + radius - dy
        );

        // Haut droit
        SDL_RenderDrawPoint(
            renderer,
            rect.x + rect.w - radius + dx - 1,
            rect.y + radius - dy
        );

        // Bas gauche
        SDL_RenderDrawPoint(
            renderer,
            rect.x + radius - dx,
            rect.y + rect.h - radius + dy - 1
        );

        // Bas droit
        SDL_RenderDrawPoint(
            renderer,
            rect.x + rect.w - radius + dx - 1,
            rect.y + rect.h - radius + dy - 1
        );
    }
}

int countUtf8Characters(const std::string &text)
{
    int count = 0;
    for (unsigned char character : text)
    {
        if ((character & 0xc0) != 0x80)
            ++count;
    }
    return count;
}

int measureTextWidth(TTF_Font *font, const std::string &text,
    int letter_spacing)
{
    if (!font || text.empty())
        return 0;

    int width = 0;
    TTF_SizeUTF8(font, text.c_str(), &width, nullptr);
    return width + std::max(0, countUtf8Characters(text) - 1) * letter_spacing;
}

void renderText(SDL_Renderer *renderer, TTF_Font *font,
    const std::string &text, int x, int y, SDL_Color color,
    int letter_spacing)
{
    if (!font || text.empty())
        return;

    if (letter_spacing == 0)
    {
        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!surface)
            return;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture)
        {
            SDL_Rect rect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
        return;
    }

    for (size_t index = 0; index < text.size();)
    {
        const unsigned char first = static_cast<unsigned char>(text[index]);
        size_t length = 1;
        if ((first & 0xe0) == 0xc0)
            length = 2;
        else if ((first & 0xf0) == 0xe0)
            length = 3;
        else if ((first & 0xf8) == 0xf0)
            length = 4;

        const std::string glyph = text.substr(index, length);
        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, glyph.c_str(), color);
        if (surface)
        {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture)
            {
                SDL_Rect rect = {x, y, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);
                x += surface->w + letter_spacing;
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
        index += length;
    }
}
