#include "Game.hpp"
#include "TextManager.hpp"

TextManager::TextManager(int fontSize) {
    textFont = TTF_OpenFont("Assets/Font/SairaExtraCondensed-SemiBold.ttf", fontSize);
    textTexture = nullptr;
    textSurface = nullptr;
}
void TextManager::Render(const char* text, int x, int y, int type)
{
    if (type == 0) textColor = {255,255,255};
    else textColor = {0,255,0};
    textSurface = TTF_RenderText_Solid(textFont, text, textColor);
    textTexture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface);
    SDL_Rect dest = {x, y, textSurface->w, textSurface->h};
    dest.x = x - textSurface->w / 2;
    dest.y = y - textSurface->h / 2;
    SDL_RenderCopy(Game::gRenderer, textTexture, nullptr, &dest);
}
TextManager::~TextManager()
{
    TTF_CloseFont(textFont);
    textFont = nullptr;
    SDL_DestroyTexture(textTexture);
    textTexture = nullptr;
    SDL_FreeSurface(textSurface);
    textSurface = nullptr;
}
