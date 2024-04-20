#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "../manager/TextureManager.hpp"
Bomb::Bomb(int x, int y, int type)
{
    x *= 32;
    y *= 32;
    bombTexture = TextureManager::LoadTexture("Assets/Object/bomb.png");
    xBomb = x; yBomb = y; typeBomb = type; xStart = x; yStart = y;
    hitbox.x = x; hitbox.y = y; hitbox.w = 16; hitbox.h = 16;
}
Bomb::~Bomb()
{
    if(bombTexture)
    {
        SDL_DestroyTexture(bombTexture);
        bombTexture = nullptr;
    }
}
void Bomb::Update(Map* map)
{
    if(typeBomb == 1) // right //
    {
        if(wait)
        {
            if (SDL_GetTicks() - lastTime > 2000)
            {
                xBomb = xStart;
                yBomb = yStart;
                wait = false;
            }
        }
        else
        {
            if(map->curr_map[yBomb/32][(xBomb+1)/32] <= 46)
            {
                wait = true;
                lastTime = SDL_GetTicks();
            }
            xBomb += 4;
            hitbox.x = xBomb;
        }
    }
    if(typeBomb == 2) // left //
    {
        if(wait)
        {
            if (SDL_GetTicks() - lastTime > 2000)
            {
                xBomb = xStart;
                yBomb = yStart;
                wait = false;
            }
        }
        else
        {
            if(map->curr_map[yBomb/32][(xBomb-1)/32] <= 46)
            {
                wait = true;
                lastTime = SDL_GetTicks();
            }
            xBomb -= 4;
            hitbox.x = xBomb;
        }
    }
    if(typeBomb == 3) // down //
    {
        if(wait)
        {
            if (SDL_GetTicks() - lastTime > 2000)
            {
                xBomb = xStart;
                yBomb = yStart;
                wait = false;
            }
        }
        else
        {
            if(map->curr_map[(yBomb+1)/32][xBomb/32] <= 46)
            {
                wait = true;
                lastTime = SDL_GetTicks();
            }
            yBomb += 4;
            hitbox.y = yBomb;
        }
    }
    if(typeBomb == 4) // up //
    {
        if(wait)
        {
            if (SDL_GetTicks() - lastTime > 2000)
            {
                xBomb = xStart;
                yBomb = yStart;
                wait = false;
            }
        }
        else
        {
            if(map->curr_map[(yBomb-1)/32][xBomb/32] <= 46)
            {
                wait = true;
                lastTime = SDL_GetTicks();
            }
            yBomb -= 4;
            hitbox.y = yBomb;
        }
    }
}
void Bomb::Render(int x, int y)
{
    SDL_Rect temp = {xBomb - x  + 490, yBomb - y + 330, 12, 12};
    if(!wait) SDL_RenderCopy(Game::gRenderer, bombTexture, nullptr, &temp);
}
