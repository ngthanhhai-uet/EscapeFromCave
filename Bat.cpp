#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"

Bat::Bat(int x, int y, int type)
{
    batTexture = TextureManager::LoadTexture("Assets/Object/bat.png");
    xpos = x; ypos = y;
    xBat = x; yBat = y;
    batRect.x = x; batRect.y = y;
    batRect.w = 32; batRect.h = 32;
    typeBat = type;
}
void Bat::Update(Map* map)
{
    if(!typeBat)
    {
        if(map->curr_map[ypos/32][xpos/32+1] <= 46) vBat = -1;
        if(map->curr_map[ypos/32][(xpos-1)/32] <= 46) vBat = 1;
        xpos += vBat;
    }
    else
    {
        if(map->curr_map[ypos/32+1][xpos/32] <= 46) vBat = -1;
        if(map->curr_map[(ypos-1)/32][xpos/32] <= 46) vBat = 1;
        ypos += vBat;
    }
}
void Bat::Render(int x, int y)
{
    batRect.x = xpos - x + 480;
    batRect.y = ypos - y + 320;
    SDL_RenderCopy(Game::gRenderer, batTexture, nullptr, &batRect);
}
