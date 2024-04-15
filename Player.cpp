#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"

Player::Player(const char* pngfile, int x, int y)
{
    playerTexture = TextureManager::LoadTexture(pngfile);
    xpos = x; ypos = y;
}
bool Player::Collision(SDL_Rect rect)
{
    if (xpos + 32 <= rect.x || rect.x + 32 <= xpos || ypos + 32 <= rect.y || rect.y + 32 <= ypos)  return false;
    return true;
}
void Player::Handle(SDL_Event e, Game* game, Map *map)
{
    switch(e.key.keysym.sym)
    {
    case SDLK_DOWN:
        flip = SDL_FLIP_NONE; degrees = +90;
        while(1)
        {
            int type = map->curr_map[ypos/32+1][xpos/32];
            if(type == 124 || type == 130 || type == 131) { game->isLose = true; break;}
            if(type == 120)
            {
                for(int i = 1; i <= 32; i++) {ypos += 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_RIGHT; SDL_PushEvent(&e);
                break;
            }
            if(type == 121)
            {
                for(int i = 1; i <= 32; i++) {ypos += 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_LEFT; SDL_PushEvent(&e);
                break;
            }
            if(type <= 46) break;
            ypos += 1; game->updateGame(); game->renderGame();
        }
        break;
    case SDLK_UP:
        flip = SDL_FLIP_NONE; degrees = -90;
        while(1)
        {

            int type = map->curr_map[(ypos-1)/32][xpos/32];
            if (type == 127 || type == 126 || type == 129){ game->isLose = true; break;}
            if(type == 122)
            {
                for(int i = 1; i <= 32; i++){ ypos -= 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_RIGHT; SDL_PushEvent(&e);
                break;
            }
            if(type == 123)
            {
                for(int i = 1; i <= 32; i++){ ypos -= 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_LEFT; SDL_PushEvent(&e);
                break;
            }
            if(type <= 46) break;
            ypos -= 1; game->updateGame(); game->renderGame();
        }
        break;
    case SDLK_RIGHT:
        flip = SDL_FLIP_NONE; degrees = 0;
        while(1)
        {

            int type = map->curr_map[ypos/32][xpos/32+1];
            if(type == 128 || type == 130 || type == 129) { game->isLose = true; break;}
            if(type <= 46) break;
            if(type == 121)
            {
                for(int i = 1; i <= 32; i++){ xpos += 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_UP; SDL_PushEvent(&e);
                break;
            }
            if(type == 123)
            {
                for(int i = 1; i <= 32; i++) { xpos += 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_DOWN; SDL_PushEvent(&e);
                break;
            }
            xpos += 1; game->updateGame(); game->renderGame();
        }
        break;
    case SDLK_LEFT:
        flip = SDL_FLIP_HORIZONTAL; degrees = 0;
        while(1)
        {
            int type = map->curr_map[ypos/32][(xpos-1)/32];
            if(type == 125 || type == 126 || type == 131) { game->isLose = true; break;}
            if(type == 120)
            {
                for(int i = 1; i <= 32; i++) {xpos -= 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_UP; SDL_PushEvent(&e);
                break;
            }
            if(type == 122)
            {
                for(int i = 1; i <= 32; i++) {xpos -= 1; game->updateGame(); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_DOWN; SDL_PushEvent(&e);
                break;
            }
            if(type <= 46) break;
            xpos -= 1; game->updateGame(); game->renderGame();
        }
        break;
    }
}
void Player::Update(SDL_Rect &camera, int &x, int &y)
{
    camera.x = x - 480;
    camera.y = y - 320;
    x = camera.x + 480;
    y = camera.y + 320;
}
void Player::Render()
{
    SDL_RenderCopyEx(Game::gRenderer, playerTexture, NULL, &dest, degrees, NULL, flip);
}
