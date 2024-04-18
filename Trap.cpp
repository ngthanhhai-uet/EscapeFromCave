#include "Game.hpp"
#include "Trap.hpp"
#include "TextureManager.hpp"

Trap::Trap(int x, int y, int type)
{
    trapon = TextureManager::LoadTexture("Assets/Object/trapon.png");
    trapoff = TextureManager::LoadTexture("Assets/Object/trapoff.png");
    xTrap = x; yTrap = y;
    typeTrap = type;
    hitbox.x = x; hitbox.y = y;
    hitbox.w = 32; hitbox.h = 32;
}
void Trap::Update()
{
    if(activated && SDL_GetTicks() - activatedTime > 1500) activated = false;
}
void Trap::Render(int x, int y)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect temp = {xTrap - x + 480, yTrap - y + 320, 32, 32};
    if(activated)
    {
        if(typeTrap == 1) SDL_RenderCopyEx(Game::gRenderer, trapon, nullptr, &temp, 90 ,nullptr, flip);
        if(typeTrap == 2) SDL_RenderCopyEx(Game::gRenderer, trapon, nullptr, &temp, 270 ,nullptr, flip);
        if(typeTrap == 3) SDL_RenderCopyEx(Game::gRenderer, trapon, nullptr, &temp, 180 ,nullptr, flip);
        if(typeTrap == 4) SDL_RenderCopyEx(Game::gRenderer, trapon, nullptr, &temp, 0 ,nullptr, flip);
    }
    else
    {
        if(typeTrap == 1) SDL_RenderCopyEx(Game::gRenderer, trapoff, nullptr, &temp, 90 ,nullptr, flip);
        if(typeTrap == 2) SDL_RenderCopyEx(Game::gRenderer, trapoff, nullptr, &temp, 270 ,nullptr, flip);
        if(typeTrap == 3) SDL_RenderCopyEx(Game::gRenderer, trapoff, nullptr, &temp, 180 ,nullptr, flip);
        if(typeTrap == 4) SDL_RenderCopyEx(Game::gRenderer, trapoff, nullptr, &temp, 0 ,nullptr, flip);
    }
}
