#include "Peak.hpp"
#include "Game.hpp"
#include "../manager/TextureManager.hpp"
Peak::Peak(int x, int y)
{
    x *= 32;
    y *= 32;
    peakon = TextureManager::LoadTexture("Assets/Object/peakon.png");
    peakoff = TextureManager::LoadTexture("Assets/Object/peakoff.png");
    xPeak = x; yPeak = y;
    hitbox.x = x - 32;
    hitbox.y = y - 32;
    hitbox.w = 96;
    hitbox.h = 96;
}
Peak::~Peak()
{
    if(peakon)
    {
        SDL_DestroyTexture(peakon);
        peakon = nullptr;
    }
    if(peakoff)
    {
        SDL_DestroyTexture(peakoff);
        peakoff = nullptr;
    }
}
int Peak::deltaTime()
{
    int currentTime = SDL_GetTicks();
    int deltaTime = SDL_GetTicks() - lastTime;
    lastTime = currentTime;
    return deltaTime;
}
void Peak::Update()
{
    if(activated)
    {
        onTime += deltaTime();
        if(onTime >= 1500) { activated = false; onTime = 0; }
    }
    else
    {
        offTime += deltaTime();
        if(offTime >= 1000) { activated = true; offTime = 0; }
    }
}
void Peak::Render(int x, int y)
{
    SDL_Rect temp = {xPeak - x + 448, yPeak - y + 288, 96, 96};
    if(activated) SDL_RenderCopy(Game::gRenderer, peakon, nullptr, &temp);
    else SDL_RenderCopy(Game::gRenderer, peakoff, nullptr, &temp);
}
