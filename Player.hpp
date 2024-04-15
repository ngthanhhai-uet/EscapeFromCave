
#ifndef Player_hpp
#define Player_hpp
#include "Game.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Player
{
public:
    // Method //
    Player(const char* pngfile, int x, int y);
    ~Player();
    void Handle(SDL_Event e, Game* game, Map *map);
    void Update(SDL_Rect &camera, int &x, int &y);
    void Render();
    bool Collision(SDL_Rect rect);
    // Attribute //
    int xpos;
    int ypos;
    int velocity;
    double degrees;
    SDL_RendererFlip flip;
    // Render //
    SDL_Texture* playerTexture;
    SDL_Rect src;
    SDL_Rect dest = {480,320,32,32};
};
#endif
