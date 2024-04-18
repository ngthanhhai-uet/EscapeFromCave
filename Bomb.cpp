#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

Bomb::Bomb(int x, int y, int type)
{
    x *= 32;
    y *= 32;
    bombTexture = TextureManager::LoadTexture("Assets/Object/bomb.png");
    xBomb = x; yBomb = y; typeBomb = type; xStart = x; yStart = y;
    hitbox.x = x; hitbox.y = y; hitbox.w = 16; hitbox.h = 16;
}
void Bomb::Update(Map* map)
{
    if(typeBomb == 1) // right //
    {
        xBomb += 4;
        if(map->curr_map[yBomb/32][(xBomb+4)/32] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        hitbox.x = xBomb;
    }
    if(typeBomb == 2) // left //
    {
        if(map->curr_map[yBomb/32][(xBomb-4)/32] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        xBomb -= 4;
        hitbox.x = xBomb;
    }
    if(typeBomb == 3) // down //
    {
        if(map->curr_map[(yBomb+4)/32][xBomb/32] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        yBomb += 4;
        hitbox.y = yBomb;
    }
    if(typeBomb == 4) // up //
    {
        if(map->curr_map[(yBomb-4)/32][xBomb/32] <= 46)
        {
            xBomb = xStart;
            yBomb = yStart;
        }
        yBomb -= 4;
        hitbox.y = yBomb;
    }
}
void Bomb::Render(int x, int y)
{
    SDL_Rect temp = {xBomb - x  + 490, yBomb - y + 330, 12, 12};
    SDL_RenderCopy(Game::gRenderer, bombTexture, nullptr, &temp);
}
