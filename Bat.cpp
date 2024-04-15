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
void Bat::Update()
{
    if(!typeBat)
    {
        if(xpos == xBat - 64 || xBat + 64 == xpos) vBat = -vBat;
        xpos += vBat;
        batRect.x = xpos;
    }
    else
    {
        if(ypos == yBat - 64 || yBat + 64 == ypos) yBat = - yBat;
        ypos += vBat;
        batRect.y = ypos;
    }
}
void Bat::Render()
{
    SDL_RenderCopy(Game::gRenderer, batTexture, nullptr, &batRect);
}
