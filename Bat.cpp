#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"

Bat::Bat(int x, int y, int type)
{
    batTexture = TextureManager::LoadTexture("Assets/Object/bat.png");
    xBat = x; yBat = y;
    typeBat = type;
    hitbox.x = x; hitbox.y = y;
    hitbox.w = 32; hitbox.h = 32;
}
void Bat::Update(Map* map)
{
    if(!typeBat)
    {
        if(map->curr_map[yBat/32][xBat/32+1] <= 46) vBat = -1;
        if(map->curr_map[yBat/32][(xBat-1)/32] <= 46) vBat = 1;
        xBat += vBat; hitbox.x = xBat;
    }
    else
    {
        if(map->curr_map[yBat/32+1][xBat/32] <= 46) vBat = -1;
        if(map->curr_map[(yBat-1)/32][xBat/32] <= 46) vBat = 1;
        yBat += vBat; hitbox.y = yBat;
    }
}
void Bat::Render(int x, int y)
{
    SDL_Rect temp = {xBat - x  + 480, yBat - y + 320, 32, 32};
    SDL_RenderCopy(Game::gRenderer, batTexture, nullptr, &temp);
}
