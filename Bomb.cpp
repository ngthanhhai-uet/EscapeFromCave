#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

Bomb::Bomb(int x, int y, int type)
{
    bombTexture = TextureManager::LoadTexture("Assets/Object/bomb.png"); // ok
    xBomb = x, yBomb = y;
    xpos = x, ypos = y;
    typeBomb = type; // ok
    bombRect.x = x + 10,bombRect.y = y + 10; // ok
    bombRect.w = 12, bombRect.y = 12;
}
void Bomb::Update(Map* map)
{
    if(typeBomb == 1)
    {
        if(map->curr_map[ypos/32][xpos/32+1] <= 46) {xpos = xBomb; ypos = yBomb;}
        xpos++;
        bombRect.x = xpos + 10;
    }
    if(typeBomb == 2)
    {
        if(map->curr_map[ypos/32][(xpos-1)/32] <= 46) {xpos = xBomb; ypos = yBomb;}
        xpos--;
        bombRect.x = xpos + 10;
    }
    if (typeBomb == 3)
    {
        if(map->curr_map[ypos/32+1][xpos/32] <= 46) {xpos = xBomb; ypos = yBomb;}
        ypos++;
        bombRect.y = ypos + 10;
    }
    if (typeBomb == 4)
    {
        if(map->curr_map[(ypos-1)/32][xpos/32] <= 46) {xpos = xBomb; ypos = yBomb;}
        ypos++;
        bombRect.y = ypos + 10;
    }
}
void Bomb::Render(int x, int y)
{
    bombRect.x = xpos - x + 480;
    bombRect.y = ypos - y + 320;
    SDL_RenderCopy(Game::gRenderer, bombTexture, nullptr, &bombRect);
}
