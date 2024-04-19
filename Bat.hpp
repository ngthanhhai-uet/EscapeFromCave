#ifndef Bat_hpp
#define Bat_hpp
#include <iostream>
#include "Map.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Bat {
private:
public:
    Bat(int x, int y, int type);
    void Update(Map *map);
    void Render(int x, int y);
    int xBat, yBat;
    int vBat = 1;
    int frame = 0;
    int typeBat;
    SDL_Rect hitbox;
    SDL_Texture* batTexture;
};
#endif
