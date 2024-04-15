#ifndef Bomb_hpp
#define Bomb_hpp
#include <iostream>
#include "Map.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Bomb
{
public:
    Bomb(int x, int y, int type);
    void Update(Map *map);
    void Render(int x, int y);
    int xBomb, yBomb;
    int xpos, ypos;
    int typeBomb;
    SDL_Texture* bombTexture;
    SDL_Rect bombRect;
};
#endif // Bomb_hpp
