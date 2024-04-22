#include "Game.hpp"
#include "Map.hpp"
#include "../manager/TextureManager.hpp"
#include "Player.hpp"

Player::Player(const char* pngfile, int x, int y)
{
    x *= 32;
    y *= 32;
    playerTexture = TextureManager::LoadTexture(pngfile);
    xpos = x; ypos = y;
}
Player::~Player()
{
    if (playerTexture != nullptr) {
        SDL_DestroyTexture(playerTexture);
        playerTexture = nullptr;
    }
}
bool Player::Collision(SDL_Rect hitbox)
{
    if(xpos + 32 <= hitbox.x || hitbox.x + hitbox.w <= xpos || ypos + 32 <= hitbox.y || hitbox.y + hitbox.h <= ypos) return false;
    return true;
}
void Player::Handle(SDL_Event e, Game* game, Map *map)
{
    switch(e.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        game->isPause = true;
        break;
    case SDLK_DOWN:
        flip = SDL_FLIP_NONE; degrees = +90;
        while(1)
        {
            if(game->currentLevel == 4)
            {
                if (xpos == 30 * 32 && ypos == 43 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 31 * 32; ypos = 46 * 32;}
                else if (xpos == 31 * 32 && ypos == 46 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 30 * 32; ypos = 43 * 32;}
                else if (xpos == 35 * 32 && ypos == 42 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 52 * 32;}
                else if (xpos == 34 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 42 * 32;}
                else if (xpos == 35 * 32 && ypos == 48 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 48 * 32;}
                else if (xpos == 24 * 32 && ypos == 49 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 50 * 32;}
                else if (xpos == 22 * 32 && ypos == 50 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 49 * 32;}
                else if (xpos == 17 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 52 * 32;}
                else if (xpos == 22 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 53 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 58 * 32;}
                else if (xpos == 34 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 53 * 32;}
                else if (xpos == 44 * 32 && ypos == 56 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 31 * 32; ypos = 60 * 32;}
                else if (xpos == 31 * 32 && ypos == 60 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 44 * 32; ypos = 56 * 32;}
                else if (xpos == 24 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 65 * 32;}
                else if (xpos == 34 * 32 && ypos == 65 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 58 * 32;}
                else if (xpos == 23 * 32 && ypos == 64 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 20 * 32; ypos = 71 * 32;}
                else if (xpos == 20 * 32 && ypos == 71 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 64 * 32;}
            }
            if(game->currentLevel == 6)
            {
                if(xpos == 17 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 18 * 32;}
                else if(xpos == 23 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 18 * 32;}

            }
            if(game->currentLevel == 5)
            {
                if(xpos == 24 * 32 && ypos == 22 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 22 * 32;}
            }
            int type = map->curr_map[ypos/32+1][xpos/32];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if(type == 124 || type == 130 || type == 131) { Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type == 120)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++) {ypos += 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_RIGHT; SDL_PushEvent(&e);
                break;
            }
            if(type == 121)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++) {ypos += 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_LEFT; SDL_PushEvent(&e);
                break;
            }
            if(type <= 51)
            {
                Mix_PlayChannel(-1,game->gChunk1,0);
                break;
            }
            ypos += 1; game->updateGame(1); game->renderGame();
        }
        break;
    case SDLK_UP:
        flip = SDL_FLIP_NONE; degrees = -90;
        while(1)
        {
            if(game->currentLevel == 4)
            {
                if (xpos == 30 * 32 && ypos == 43 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 31 * 32; ypos = 46 * 32;}
                else if (xpos == 31 * 32 && ypos == 46 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 30 * 32; ypos = 43 * 32;}
                else if (xpos == 35 * 32 && ypos == 42 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 52 * 32;}
                else if (xpos == 34 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 42 * 32;}
                else if (xpos == 35 * 32 && ypos == 48 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 48 * 32;}
                else if (xpos == 24 * 32 && ypos == 49 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 50 * 32;}
                else if (xpos == 22 * 32 && ypos == 50 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 49 * 32;}
                else if (xpos == 17 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 52 * 32;}
                else if (xpos == 22 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 53 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 58 * 32;}
                else if (xpos == 34 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 53 * 32;}
                else if (xpos == 44 * 32 && ypos == 56 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 31 * 32; ypos = 60 * 32;}
                else if (xpos == 31 * 32 && ypos == 60 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 44 * 32; ypos = 56 * 32;}
                else if (xpos == 24 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 65 * 32;}
                else if (xpos == 34 * 32 && ypos == 65 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 58 * 32;}
                else if (xpos == 23 * 32 && ypos == 64 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 20 * 32; ypos = 71 * 32;}
                else if (xpos == 20 * 32 && ypos == 71 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 64 * 32;}
            }
            if(game->currentLevel == 6)
            {
                if(xpos == 17 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 18 * 32;}
                else if(xpos == 23 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 18 * 32;}

            }
            if(game->currentLevel == 5)
            {
                if(xpos == 24 * 32 && ypos == 22 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 22 * 32;}
            }
            int type = map->curr_map[(ypos-1)/32][xpos/32];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if (type == 127 || type == 126 || type == 129){ Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type == 122)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++){ ypos -= 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_RIGHT; SDL_PushEvent(&e);
                break;
            }
            if(type == 123)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++){ ypos -= 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_LEFT; SDL_PushEvent(&e);
                break;
            }
            if(type <= 51)
            {
                Mix_PlayChannel(-1,game->gChunk1,0);
                break;
            }
            ypos -= 1; game->updateGame(1); game->renderGame();
        }
        break;
    case SDLK_RIGHT:
        flip = SDL_FLIP_NONE; degrees = 0;
        while(1)
        {
            if(game->currentLevel == 4)
            {
                if (xpos == 30 * 32 && ypos == 43 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 31 * 32; ypos = 46 * 32;}
                else if (xpos == 31 * 32 && ypos == 46 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 30 * 32; ypos = 43 * 32;}
                else if (xpos == 35 * 32 && ypos == 42 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 52 * 32;}
                else if (xpos == 34 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 42 * 32;}
                else if (xpos == 35 * 32 && ypos == 48 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 48 * 32;}
                else if (xpos == 24 * 32 && ypos == 49 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 50 * 32;}
                else if (xpos == 22 * 32 && ypos == 50 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 49 * 32;}
                else if (xpos == 17 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 52 * 32;}
                else if (xpos == 22 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 53 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 58 * 32;}
                else if (xpos == 34 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 53 * 32;}
                else if (xpos == 44 * 32 && ypos == 56 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 31 * 32; ypos = 60 * 32;}
                else if (xpos == 31 * 32 && ypos == 60 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 44 * 32; ypos = 56 * 32;}
                else if (xpos == 24 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 65 * 32;}
                else if (xpos == 34 * 32 && ypos == 65 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 58 * 32;}
                else if (xpos == 23 * 32 && ypos == 64 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 20 * 32; ypos = 71 * 32;}
                else if (xpos == 20 * 32 && ypos == 71 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 64 * 32;}
            }
            if(game->currentLevel == 6)
            {
                if(xpos == 17 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 18 * 32;}
                else if(xpos == 23 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 18 * 32;}

            }
            if(game->currentLevel == 5)
            {
                if(xpos == 24 * 32 && ypos == 22 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 22 * 32;}
            }
            int type = map->curr_map[ypos/32][xpos/32+1];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if(type == 128 || type == 130 || type == 129) { Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type <= 51)
            {
                Mix_PlayChannel(-1,game->gChunk1,0);
                break;
            }
            if(type == 121)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++){ xpos += 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_UP; SDL_PushEvent(&e);
                break;
            }
            if(type == 123)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++) { xpos += 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_DOWN; SDL_PushEvent(&e);
                break;
            }
            xpos += 1; game->updateGame(1); game->renderGame();
        }
        break;
    case SDLK_LEFT:
        flip = SDL_FLIP_HORIZONTAL; degrees = 0;
        while(1)
        {
            if(game->currentLevel == 4)
            {
                if (xpos == 30 * 32 && ypos == 43 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 31 * 32; ypos = 46 * 32;}
                else if (xpos == 31 * 32 && ypos == 46 * 32) { Mix_PlayChannel(-1,game->gChunk5,0);xpos = 30 * 32; ypos = 43 * 32;}
                else if (xpos == 35 * 32 && ypos == 42 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 52 * 32;}
                else if (xpos == 34 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 42 * 32;}
                else if (xpos == 35 * 32 && ypos == 48 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 35 * 32; ypos = 48 * 32;}
                else if (xpos == 24 * 32 && ypos == 49 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 50 * 32;}
                else if (xpos == 22 * 32 && ypos == 50 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 49 * 32;}
                else if (xpos == 17 * 32 && ypos == 51 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 52 * 32;}
                else if (xpos == 22 * 32 && ypos == 52 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 51 * 32;}
                else if (xpos == 24 * 32 && ypos == 53 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 58 * 32;}
                else if (xpos == 34 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 53 * 32;}
                else if (xpos == 44 * 32 && ypos == 56 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 31 * 32; ypos = 60 * 32;}
                else if (xpos == 31 * 32 && ypos == 60 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 44 * 32; ypos = 56 * 32;}
                else if (xpos == 24 * 32 && ypos == 58 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 34 * 32; ypos = 65 * 32;}
                else if (xpos == 34 * 32 && ypos == 65 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 24 * 32; ypos = 58 * 32;}
                else if (xpos == 23 * 32 && ypos == 64 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 20 * 32; ypos = 71 * 32;}
                else if (xpos == 20 * 32 && ypos == 71 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 64 * 32;}
            }
            if(game->currentLevel == 6)
            {
                if(xpos == 17 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 23 * 32; ypos = 18 * 32;}
                else if(xpos == 23 * 32 && ypos == 18 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 17 * 32; ypos = 18 * 32;}

            }
            if(game->currentLevel == 5)
            {
                if(xpos == 24 * 32 && ypos == 22 * 32) { Mix_PlayChannel(-1,game->gChunk5,0); xpos = 22 * 32; ypos = 22 * 32;}
            }
            int type = map->curr_map[ypos/32][(xpos-1)/32];
            if(type == 118) { Mix_PlayChannel(-1,game->gChunk4,0); game->isWin = true; break; }
            if(type == 125 || type == 126 || type == 131) { Mix_PlayChannel(-1,game->gChunk6,0); game->isLose = true; break;}
            if(type == 120)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++) {xpos -= 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_UP; SDL_PushEvent(&e);
                break;
            }
            if(type == 122)
            {
                Mix_PlayChannel(-1,game->gChunk2,0);
                for(int i = 1; i <= 32; i++) {xpos -= 1; game->updateGame(1); game->renderGame();}
                SDL_Event e; e.type = SDL_KEYDOWN; e.key.keysym.sym = SDLK_DOWN; SDL_PushEvent(&e);
                break;
            }
            if(type <= 51)
            {
                Mix_PlayChannel(-1,game->gChunk1,0);
                break;
            }
            xpos -= 1; game->updateGame(1); game->renderGame();
        }
        break;
    }
}
void Player::Update(SDL_Rect &camera, int x, int y)
{
    camera.x = x - 480; camera.y = y - 320;
}
void Player::Render()
{
    SDL_Rect temp = {480,320,32,32};
    SDL_RenderCopyEx(Game::gRenderer, playerTexture, NULL, &temp, degrees, NULL, flip);
}
