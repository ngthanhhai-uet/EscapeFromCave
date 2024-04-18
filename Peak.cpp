#include "Peak.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
Peak::Peak(int x, int y)
{
    peakon = TextureManager::LoadTexture("Assets/Object/peak1.png");
    peakoff = TextureManager::LoadTexture("Assets/Object/peak2.png");
    xPeak = x; yPeak = y;
    hitbox.x = x - 32;
    hitbox.y = y - 32;
    hitbox.w = 96;
    hitbox.h = 96;
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
    if(isExpand)
    {
        onTime += deltaTime();
        if(onTime >= 2000) { isExpand = false; onTime = 0; }
    }
    else
    {
        offTime += deltaTime();
        if(offTime >= 3000) { isExpand = true; offTime = 0; }
    }
}
void Peak::Render(int x, int y)
{
    SDL_Rect temp = {xPeak - x + 448, yPeak - y + 288, 96, 96};
    if(isExpand) SDL_RenderCopy(Game::gRenderer, peakon, nullptr, &temp);
    else SDL_RenderCopy(Game::gRenderer, peakoff, nullptr, &temp);
}
