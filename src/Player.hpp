#ifndef Player_hpp
#define Player_hpp
#include "Game.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Player
{
public:
    // Method //
    Player(const char* pngfile, int x, int y);
    ~Player();
    void Handle(SDL_Event e, Game* game, Map *map);
    void Update(SDL_Rect &camera, int x, int y);
    void Render();
    bool Collision(SDL_Rect hitbox);
    // Attribute //
    int xpos, ypos;
    double degrees;
    SDL_RendererFlip flip;
    // Render //
    SDL_Rect animation;
    SDL_Texture* playerTexture;
};
#endif
