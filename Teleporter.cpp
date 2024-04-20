#include "Teleporter.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
Teleporter::Teleporter(int x, int y)
{
    x *= 32;
    y *= 32;
    teleporterTexture = TextureManager::LoadTexture("Assets/Object/teleporter.png");
    xTeleporter = x;
    yTeleporter = y;
}
void Teleporter::Update()
{
    if(frame/5 == 1) animation = {0,0,32,32};
    else if(frame/5 == 4) animation = {32,0,32,32};
    else if(frame/5 == 5) animation = {64,0,32,32};
    else if(frame/5 == 3) animation = {0,32,32,32};
    else if(frame/5 == 2) animation = {32,32,32,32};
    else if(frame/5 == 6) animation = {64,32,32,32};
    frame++;
    if(frame/5 >= 6) frame = 0;
}
void Teleporter::Render(int x, int y)
{
    SDL_Rect temp = {xTeleporter - x + 480, yTeleporter - y + 320, 32, 32};
    SDL_RenderCopy(Game::gRenderer, teleporterTexture, &animation, &temp);
}
