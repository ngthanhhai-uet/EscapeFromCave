#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"

Bat::Bat(int x, int y, int type)
{
    batTexture = TextureManager::LoadTexture("Assets/Object/bat.png");
    xBat = x; yBat = y;
    batRect.x = x; batRect.y = y;
    batRect.w = 32; batRect.h = 32;
    typeBat = type;
}
void Bat::Update(Map* map)
{
    if(!typeBat)
    {
        if(map->curr_map[yBat/32][xBat/32+1] <= 46) vBat = -1;
        if(map->curr_map[yBat/32][(xBat-1)/32] <= 46) vBat = 1;
        xBat += vBat;
    }
    else
    {
        if(map->curr_map[yBat/32+1][xBat/32] <= 46) vBat = -1;
        if(map->curr_map[(yBat-1)/32][xBat/32] <= 46) vBat = 1;
        yBat += vBat;
    }
}
void Bat::Render(int x, int y)
{
    batRect.x = xBat - x + 480;
    batRect.y = yBat - y + 320;
    SDL_RenderCopy(Game::gRenderer, batTexture, nullptr, &batRect);
}
