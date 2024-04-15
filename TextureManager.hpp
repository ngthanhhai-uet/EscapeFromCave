
#ifndef TextureManager_hpp
#define TextureManager_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class TextureManager
{
public:
    static SDL_Texture* LoadTexture (const char* pngfile);
    static void Draw (SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
};
#endif
