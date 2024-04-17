#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

Bomb::Bomb(int x, int y, int type)
{
    bombTexture = TextureManager::LoadTexture("Assets/Object/bomb.png");
    xBomb = x; yBomb = y; typeBomb = type; xStart = x; yStart = y;
    hitbox.x = x; hitbox.y = y; hitbox.w = 16; hitbox.h = 16;
}
void Bomb::Update(Map* map)
{
    if(typeBomb == 1) // right //
    {
        if(map->curr_map[yBomb/32][xBomb/32+2] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        xBomb += 2;
    }
    if(typeBomb == 2) // left //
    {
        if(map->curr_map[yBomb/32][(xBomb-2)/32] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        xBomb -= 2;
    }
    if(typeBomb == 3) // down //
    {
        if(map->curr_map[yBomb/32+2][xBomb/32] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        yBomb += 2;
    }
    if(typeBomb == 4) // up //
    {
        if(map->curr_map[yBomb/32][xBomb/32+2] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        yBomb -= 2;
    }
}
void Bomb::Render(int x, int y)
{
    SDL_Rect temp = {xBomb - x  + 488, yBomb - y + 328, 16, 16};
    SDL_RenderCopy(Game::gRenderer, bombTexture, nullptr, &temp);
}
