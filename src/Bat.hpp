#ifndef Bat_hpp
#define Bat_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Map.hpp"
class Bat {
private:
public:
    Bat(int x, int y, int type);
    ~Bat();
    void Update(Map *map);
    void Render(int x, int y);
    int xBat, yBat;
    int vBat = 1;
    int frame = 0;
    int typeBat;
    SDL_Rect hitbox;
    SDL_Rect animation;
    SDL_Texture* batTexture;
};
#endif
