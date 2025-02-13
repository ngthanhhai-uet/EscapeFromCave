#ifndef Bomb_hpp
#define Bomb_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Map.hpp"
class Bomb {
private:
public:
    Bomb(int x, int y, int type);
    ~Bomb();
    void Update(Map *map);
    void Render(int x, int y);
    int xStart, yStart;
    int xBomb, yBomb;
    int typeBomb;
    int lastTime;
    bool wait;
    SDL_Rect hitbox;
    SDL_Texture* bombTexture;
};
#endif
