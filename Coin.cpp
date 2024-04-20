#include "Coin.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
Coin::Coin(int x, int y)
{
    x *= 32;
    y *= 32;
    coinTexture = TextureManager::LoadTexture("Assets/Object/coin.png");
    xCoin = x;
    yCoin = y;
    hitbox.x = x; hitbox.y = y;
    hitbox.w = 32; hitbox.h = 32;
}
void Coin::Update()
{
    if(frame/6 == 1) animation = {0,0,32,32};
    else if(frame/6 == 2) animation = {32,0,32,32};
    else if(frame/6 == 3) animation = {64,0,32,32};
    else if(frame/6 == 4) animation = {96,0,32,32};
    frame++;
    if(frame/6 >= 4) frame = 0;
}
void Coin::Render(int x, int y)
{
    SDL_Rect temp = {xCoin - x + 480, yCoin - y + 320, 32, 32};
    if(!collected) SDL_RenderCopy(Game::gRenderer,coinTexture,&animation,&temp);
}
