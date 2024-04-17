
#ifndef TextManager_hpp
#define TextManager_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
class TextManager
{
public:
    TTF_Font* textFont;
    SDL_Texture* textTexture;
    SDL_Surface* textSurface;
    SDL_Color textColor;
    TextManager(int fontSize);
    ~TextManager();
    void Render(const char* text, int x, int y, int type);
};
#endif
