#ifndef Coin_hpp
#define Coin_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Coin
{
public:
    Coin(int x, int y);
    ~Coin();
    int xCoin;
    int yCoin;
    bool collected = false;
    int frame = 0;
    SDL_Texture *coinTexture;
    SDL_Rect animation;
    SDL_Rect hitbox;
    void Update();
    void Render(int x, int y);
};
#endif // Coin_hpp
