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
    // Method //
    Bat(int x, int y, int type);
    void Update(Map *map);
    void Render(int x, int y);
    // Atribute //
    int xBat, yBat;
    int vBat = 1;
    int typeBat;
    // Render //
    SDL_Texture* batTexture;
    SDL_Rect batRect;
};
#endif
