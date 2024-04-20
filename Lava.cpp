#include "Lava.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
Lava::Lava(int x, int y)
{
    lavaTexture = TextureManager::LoadTexture("Assets/Object/lava.png");
    xLava = x;
    yLava = y;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = 31 * 32;
    hitbox.h = 32;
}
void Lava::Update()
{
    yLava -= 2;
    hitbox.y = yLava;
}
void Lava::Render(int x, int y)
{
    SDL_Rect temp = {xLava - x + 480, yLava - y + 320, 992, 672};
    SDL_RenderCopy(Game::gRenderer, lavaTexture, nullptr, &temp);
}
