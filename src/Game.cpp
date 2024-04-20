#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Peak.hpp"
#include "Trap.hpp"
#include "Coin.hpp"
#include "Lava.hpp"
#include "Teleporter.hpp"
#include "../manager/TextManager.hpp"
#include "../manager/TextureManager.hpp"

#include <string>

Game::Game(){}
Game::~Game(){}
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Texture* background;
Mix_Music* gMusic = NULL;
Mix_Chunk* gChunk1 = NULL;
TextManager* text;
Map* map;
Player* player;
Bat* bat[20];
Bomb* bomb[24];
Peak* peak[7];
Trap* trap[65];
Coin* coin[20];
Lava* lava;
Teleporter *teleporter[20];
SDL_Rect camera;

void Game::handleEvent(){
    SDL_Event gEvent;
    SDL_PollEvent(&gEvent);
	if(gEvent.type == SDL_QUIT) isRunning = false;
	int x, y;
	if(isPause)
    {
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,324,408,292,374)) // Reset //
            {
                switchState(gState);
                isPause = false;
            }
            if(isInside(x,y,454,537,292,374)) isPause = false; // Continue //
            if(isInside(x,y,582,666,292,374)) // Quit //
            {
                switchState(SELECTMAP);
                isPause = false;
            }
            break;
        default:
            break;
        }
        return;
    }
	switch(gState)
	{
    case LEVEL1:
    case LEVEL2:
    case LEVEL3:
    case LEVEL4:
    case LEVEL5:
    case LEVEL6:
    case LEVEL7:
    case LEVEL8:
    case LEVEL9:
        if(gEvent.type == SDL_KEYDOWN) player->Handle(gEvent, this, map);
        break;
    case GUIDE:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,913,970,22,76)) switchState(SELECTMAP);
            break;
        default:
            break;
        }
        break;
    case SHOP:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,913,970,22,76)) switchState(SELECTMAP);
            break;
        default:
            break;
        }
        break;
    case HIGHSCORE:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,913,970,22,76)) switchState(SELECTMAP);
            break;
        default:
            break;
        }
        break;
    case LOSE:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if (isInside(x,y,528,613,430,518)) switchState(SELECTMAP);
            if (isInside(x,y,380,465,430,518))
            {
                if(currentLevel == 1) switchState(LEVEL1);
                else if(currentLevel == 2) switchState(LEVEL2);
                else if(currentLevel == 3) switchState(LEVEL3);
                else if(currentLevel == 4) switchState(LEVEL4);
                else if(currentLevel == 5) switchState(LEVEL5);
                else if(currentLevel == 6) switchState(LEVEL6);
                else if(currentLevel == 7) switchState(LEVEL7);
                else if(currentLevel == 8) switchState(LEVEL8);
                else if(currentLevel == 9) switchState(LEVEL9);
            }
            break;
        default:
            break;
        }
        break;
    case WIN:
        if (maxLevel < currentLevel + 1) maxLevel = currentLevel + 1;
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if (isInside(x,y,528,613,430,518)) switchState(SELECTMAP);
            if (isInside(x,y,380,465,430,518))
            {
                if(currentLevel == 1) switchState(LEVEL2);
                else if(currentLevel == 2) switchState(LEVEL3);
                else if(currentLevel == 3) switchState(LEVEL4);
                else if(currentLevel == 4) switchState(LEVEL5);
                else if(currentLevel == 5) switchState(LEVEL6);
                else if(currentLevel == 6) switchState(LEVEL7);
                else switchState(SELECTMAP);
            }
            break;
        default:
            break;
        }
        break;
    case MENU:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,353,639,288,377)) switchState(SELECTMAP);
            if(isInside(x,y,353,639,401,489)) switchState(SETTING);
            if(isInside(x,y,353,639,514,603)) isRunning = false;
            break;
        default:
            break;
        }
        break;
    case SELECTMAP:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,337,426,181,289))switchState(LEVEL1);
            if(isInside(x,y,450,538,181,279) && maxLevel >= 2) switchState(LEVEL2);
            if(isInside(x,y,562,651,181,279) && maxLevel >= 3) switchState(LEVEL3);
            if(isInside(x,y,282,371,290,388) && maxLevel >= 4) switchState(LEVEL4);
            if(isInside(x,y,395,483,290,388) && maxLevel >= 5) switchState(LEVEL5);
            if(isInside(x,y,508,596,290,388) && maxLevel >= 6) switchState(LEVEL6);
            if(isInside(x,y,621,709,290,388) && maxLevel >= 7) switchState(LEVEL7);
            if(isInside(x,y,337,426,390,490) && maxLevel >= 8) switchState(LEVEL8);
            if(isInside(x,y,450,538,390,490) && maxLevel >= 9) switchState(LEVEL9);
            if(isInside(x,y,914,969,20,76)) switchState(MENU);
            if(isInside(x,y,717,925,553,591)) switchState(GUIDE);
            if(isInside(x,y,71,241,553,591)) switchState(HIGHSCORE);
            if(isInside(x,y,440,568,553,591)) switchState(SHOP);
            break;
        default:
            break;
        }
        break;
    case SETTING:
        switch(gEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x,&y);
            if(isInside(x,y,850,903,58,112)) switchState(MENU);
            if(isInside(x,y,557,607,421,444)){ isEnglish = !isEnglish; switchState(SETTING);}
            if(isInside(x,y,480,527,277,304)) Mix_VolumeMusic(14*0);
            if(isInside(x,y,528,543,288,293)) Mix_VolumeMusic(14*1);
            if(isInside(x,y,544,559,288,293)) Mix_VolumeMusic(14*2);
            if(isInside(x,y,560,575,288,293)) Mix_VolumeMusic(14*3);
            if(isInside(x,y,576,591,288,293)) Mix_VolumeMusic(14*4);
            if(isInside(x,y,592,607,288,293)) Mix_VolumeMusic(14*5);
            if(isInside(x,y,608,623,288,293)) Mix_VolumeMusic(14*6);
            if(isInside(x,y,624,639,288,293)) Mix_VolumeMusic(14*7);
            if(isInside(x,y,640,655,288,293)) Mix_VolumeMusic(14*8);
            if(isInside(x,y,656,705,277,304)) Mix_VolumeMusic(14*9);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
void Game::renderGame(){
    SDL_RenderClear(gRenderer);
    if(isPause)
    {
        background = TextureManager::LoadTexture("Assets/State/pause.png");
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        return;
    }
    switch(gState)
    {
    case SHOP:
        {
            SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
            std::string temp = std::to_string(gCoin);
            text->Render(temp.c_str(), 110, 70, 0);
        }
        break;
    case HIGHSCORE:
        {
            SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
            std::string temp = std::to_string(highScore[0]);
            text->Render(temp.c_str(), 487, 308, 1);
            temp = std::to_string(highScore[1]);
            text->Render(temp.c_str(), 487, 361, 1);
            temp = std::to_string(highScore[2]);
            text->Render(temp.c_str(), 487, 415, 1);
            temp = std::to_string(highScore[3]);
            text->Render(temp.c_str(), 487, 470, 1);
            temp = std::to_string(highScore[4]);
            text->Render(temp.c_str(), 487, 524, 1);
            temp = std::to_string(highScore[5]);
            text->Render(temp.c_str(), 487, 576, 1);
        }
        break;
    case MENU:
    case SELECTMAP:
    case GUIDE:
    case SETTING:
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        break;
    case WIN:
        {
            SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
            std::string temp = "FINISHED LEVEL " + std::to_string(currentLevel);
            text->Render(temp.c_str(), 496, 240, 1);
            temp = "Your time: " + std::to_string(tempScore);
            text->Render(temp.c_str(), 496, 300, 1);
            temp = "Min time: " + std::to_string(highScore[currentLevel-1]);
            text->Render(temp.c_str(), 496, 360, 1);
        }
        break;
    case LOSE:
        {
            SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
            text->Render("You die, too noob", 496, 240, 1);
            text->Render("Death by ", 496, 300, 1);
            text->Render("Good luck", 496, 360, 1);
        }
        break;
    case LEVEL1:
    case LEVEL2:
    case LEVEL3:
    case LEVEL4:
    case LEVEL5:
    case LEVEL6:
    case LEVEL7:
        map->DrawMap(camera);
        player->Render();
        if(lava != nullptr)
        {
            lava->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 20; i++)
        {
            if(coin[i] == nullptr) break;
            coin[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 20; i++)
        {
            if(teleporter[i] == nullptr) break;
            teleporter[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 20; i++)
        {
            if(bat[i] == nullptr) break;
            bat[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 65; i++)
        {
            if(trap[i] == nullptr) break;
            trap[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 7; i++)
        {
            if(peak[i] == nullptr) break;
            peak[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 24; i++)
        {
            if(bomb[i] == nullptr) break;
            bomb[i]->Render(player->xpos, player->ypos);
        }
        {
            std::string temp = "Coin: " + std::to_string(gCoin);
            text->Render(temp.c_str(), 30, 20, 0);
            temp = "Time: " + std::to_string(SDL_GetTicks()-startTime);
            text->Render(temp.c_str(), 30, 60, 0);
        }
        break;
    default:
        break;
    }
    SDL_RenderPresent(gRenderer);
}
void Game::enterState(State id){
    switch(id)
    {
    case LOSE:
        text = new TextManager(37);
        background = TextureManager::LoadTexture("Assets/State/lose.png");
        break;
    case WIN:
        text = new TextManager(37);
        background = TextureManager::LoadTexture("Assets/State/win.png");
        break;
    case MENU:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/menu_en.png");
        else background = TextureManager::LoadTexture("Assets/State/menu_vn.png");
        break;
    case SELECTMAP:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/selectmap_en.png");
        else background = TextureManager::LoadTexture("Assets/State/selectmap_vn.png");
        break;
    case SETTING:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/setting_en.png");
        else background = TextureManager::LoadTexture("Assets/State/setting_vn.png");
        break;
    case HIGHSCORE:
        text = new TextManager(25);
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/highscore_en.png");
        else background = TextureManager::LoadTexture("Assets/State/highscore_vn.png");
        break;
    case SHOP:
        text = new TextManager(35);
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/shop_en.png");
        else background = TextureManager::LoadTexture("Assets/State/shop_vn.png");
        break;
    case GUIDE:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/guide_en.png");
        else background = TextureManager::LoadTexture("Assets/State/guide_vn.png");
        break;
    case LEVEL1:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        currentLevel = 1;
        startTime = SDL_GetTicks();
        player = new Player("Assets/Character/spider.png",25,12);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        bat[0] = new Bat (30,49,0);
        bat[1] = new Bat (32,51,0);
        bat[2] = new Bat (35,56,0);
        trap[0] = new Trap (19,33,1);
        trap[1] = new Trap (17,33,2);
        trap[2] = new Trap (18,34,3);
        trap[3] = new Trap (18,32,4);
        trap[4] = new Trap (20,39,1);
        trap[5] = new Trap (20,40,1);
        trap[6] = new Trap (20,41,1);
        trap[7] = new Trap (21,42,4);
        trap[8] = new Trap (22,42,4);
        trap[9] = new Trap (23,42,4);
        break;
    case LEVEL2:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        startTime = SDL_GetTicks();
        currentLevel = 2;
        player = new Player("Assets/Character/spider.png",42,97);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        bat[0] = new Bat (32,96,1);
        bat[1] = new Bat (28,94,1);
        bat[2] = new Bat (30,88,1);
        bat[3] = new Bat (40,88,0);
        bat[4] = new Bat (38,83,0);
        bat[5] = new Bat (42,71,1);
        bat[6] = new Bat (39,73,1);
        bat[7] = new Bat (31,66,1);
        bat[8] = new Bat (37,52,1);
        bat[9] = new Bat (42,56,1);
        bat[10] = new Bat (45,61,1);
        bat[11] = new Bat (35,45,1);
        bat[12] = new Bat (22,41,0);
        bat[13] = new Bat (22,39,0);
        bat[14] = new Bat (17,30,0);
        bat[15] = new Bat (17,22,0);
        bat[16] = new Bat (20,21,0);
        bat[17] = new Bat (17,20,0);
        bat[18] = new Bat (34,12,0);
        bat[19] = new Bat (22,12,1);
        trap[0] = new Trap (34,93,4);
        trap[1] = new Trap (28,89,1);
        trap[2] = new Trap (28,90,1);
        trap[3] = new Trap (42,78,4);
        trap[4] = new Trap (43,78,4);
        trap[5] = new Trap (43,75,2);
        trap[6] = new Trap (43,76,2);
        trap[7] = new Trap (44,77,3);
        trap[8] = new Trap (29,77,1);
        trap[9] = new Trap (27,77,2);
        trap[10] = new Trap (28,64,3);
        trap[11] = new Trap (29,64,3);
        trap[12] = new Trap (30,64,3);
        trap[13] = new Trap (31,64,3);
        trap[14] = new Trap (38,54,4);
        trap[15] = new Trap (39,54,4);
        trap[16] = new Trap (38,56,3);
        trap[17] = new Trap (39,56,3);
        trap[18] = new Trap (37,62,1);
        trap[19] = new Trap (37,63,1);
        trap[20] = new Trap (38,63,4);
        trap[21] = new Trap (39,63,4);
        trap[22] = new Trap (42,63,4);
        trap[23] = new Trap (49,54,1);
        trap[24] = new Trap (47,54,2);
        trap[25] = new Trap (48,55,3);
        trap[26] = new Trap (37,54,4);
        trap[27] = new Trap (43,49,1);
        trap[28] = new Trap (43,48,1);
        trap[29] = new Trap (43,47,1);
        trap[30] = new Trap (43,46,1);
        trap[31] = new Trap (44,45,4);
        trap[32] = new Trap (45,46,1);
        trap[33] = new Trap (45,47,1);
        trap[34] = new Trap (48,42,1);
        trap[35] = new Trap (47,43,3);
        trap[36] = new Trap (46,42,2);
        trap[37] = new Trap (47,41,4);
        trap[38] = new Trap (28,43,1);
        trap[39] = new Trap (26,43,2);
        trap[40] = new Trap (27,42,4);
        trap[41] = new Trap (25,25,2);
        trap[42] = new Trap (25,26,2);
        trap[43] = new Trap (25,17,3);
        trap[44] = new Trap (26,17,3);
        trap[45] = new Trap (27,17,3);
        trap[46] = new Trap (30,16,1);
        trap[47] = new Trap (30,11,3);
        trap[48] = new Trap (29,11,3);
        trap[49] = new Trap (28,11,3);
        trap[50] = new Trap (25,11,1);
        trap[51] = new Trap (22,11,2);
        trap[52] = new Trap (23,12,3);
        trap[53] = new Trap (24,12,3);
        trap[54] = new Trap (23,10,4);
        trap[55] = new Trap (24,10,4);
        trap[56] = new Trap (28,76,4);
        trap[57] = new Trap (27,64,3);
        trap[58] = new Trap (43,63,4);
        break;
    case LEVEL3:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        currentLevel = 3;
        startTime = SDL_GetTicks();
        player = new Player("Assets/Character/spider.png",52,60);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        bomb[0] = new Bomb (54,23,2);
        bomb[1] = new Bomb (53,15,3);
        bomb[2] = new Bomb (47,19,3);
        bomb[3] = new Bomb (45,15,2);
        bomb[4] = new Bomb (44,25,3);
        bomb[5] = new Bomb (37,22,3);
        bomb[6] = new Bomb (33,32,2);
        bomb[7] = new Bomb (32,29,4);
        bomb[8] = new Bomb (30,24,2);
        bomb[9] = new Bomb (30,14,4);
        bomb[10] = new Bomb (29,14,4);
        bomb[11] = new Bomb (27,33,2);
        bomb[12] = new Bomb (19,30,3);
        bomb[13] = new Bomb (34,12,3);
        break;
    case LEVEL4:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        currentLevel = 4;
        startTime = SDL_GetTicks();
        player = new Player("Assets/Character/spider.png",50,12);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        teleporter[0] = new Teleporter (30,43);
        teleporter[1] = new Teleporter (31,46);
        teleporter[2] = new Teleporter (35,42);
        teleporter[3] = new Teleporter (34,52);
        teleporter[4] = new Teleporter (24,51);
        teleporter[5] = new Teleporter (24,49);
        teleporter[6] = new Teleporter (22,50);
        teleporter[7] = new Teleporter (17,51);
        teleporter[8] = new Teleporter (22,52);
        teleporter[9] = new Teleporter (24,53);
        teleporter[10] = new Teleporter (34,58);
        teleporter[11] = new Teleporter (44,56);
        teleporter[12] = new Teleporter (31,60);
        teleporter[13] = new Teleporter (24,58);
        teleporter[14] = new Teleporter (23,64);
        teleporter[15] = new Teleporter (34,65);
        teleporter[16] = new Teleporter (20,71);
        teleporter[17] = new Teleporter (35,48);
        teleporter[18] = new Teleporter (20,71);
        bat[0] = new Bat (15,68,1);
        bat[1] = new Bat (18,72,0);
        bomb[0] = new Bomb (25,62,1);
        bomb[1] = new Bomb (32,55,2);
        bomb[2] = new Bomb (36,60,1);
        bomb[3] = new Bomb (42,64,4);
        peak[0] = new Peak (50,17);
        peak[1] = new Peak (43,24);
        peak[2] = new Peak (50,28);
        peak[3] = new Peak (38,28);
        peak[4] = new Peak (33,21);
        peak[5] = new Peak (22,34);
        peak[6] = new Peak (44,21);
        trap[0] = new Trap (62,21,1);
        trap[1] = new Trap (60,21,2);
        trap[2] = new Trap (61,22,3);
        trap[3] = new Trap (61,20,4);
        trap[4] = new Trap (57,19,1);
        trap[5] = new Trap (22,19,2);
        trap[6] = new Trap (56,20,3);
        trap[7] = new Trap (56,18,4);
        trap[8] = new Trap (54,31,1);
        trap[9] = new Trap (52,31,2);
        trap[10] = new Trap (53,32,3);
        trap[11] = new Trap (53,30,4);
        trap[12] = new Trap (26,19,1);
        trap[13] = new Trap (26,20,1);
        trap[14] = new Trap (24,19,2);
        trap[15] = new Trap (24,20,2);
        trap[16] = new Trap (25,18,4);
        trap[17] = new Trap (25,21,3);
        trap[18] = new Trap (27,26,3);
        trap[19] = new Trap (28,26,3);
        trap[20] = new Trap (29,26,3);
        trap[21] = new Trap (30,26,3);
        trap[22] = new Trap (21,26,1);
        trap[23] = new Trap (21,27,1);
        trap[24] = new Trap (21,28,1);
        trap[25] = new Trap (21,29,1);
        trap[26] = new Trap (21,30,1);
        trap[27] = new Trap (22,30,4);
        trap[28] = new Trap (23,30,4);
        trap[29] = new Trap (24,30,4);
        trap[30] = new Trap (25,30,4);
        trap[31] = new Trap (26,30,4);
        trap[32] = new Trap (27,30,4);
        trap[33] = new Trap (22,32,3);
        trap[34] = new Trap (24,32,3);
        trap[35] = new Trap (25,32,3);
        trap[36] = new Trap (26,32,3);
        trap[37] = new Trap (27,32,3);
        trap[38] = new Trap (31,32,4);
        trap[39] = new Trap (30,32,4);
        trap[40] = new Trap (29,33,2);
        trap[41] = new Trap (30,34,3);
        trap[42] = new Trap (31,34,3);
        trap[43] = new Trap (22,36,4);
        trap[44] = new Trap (23,36,4);
        trap[45] = new Trap (24,36,4);
        trap[46] = new Trap (25,36,4);
        trap[47] = new Trap (26,36,4);
        trap[48] = new Trap (24,46,4);
        trap[49] = new Trap (25,46,4);
        trap[50] = new Trap (26,46,4);
        trap[51] = new Trap (27,46,4);
        trap[52] = new Trap (28,46,4);
        trap[53] = new Trap (29,46,4);
        trap[54] = new Trap (25,51,4);
        trap[55] = new Trap (26,51,4);
        trap[56] = new Trap (27,51,4);
        trap[57] = new Trap (28,51,4);
        trap[58] = new Trap (29,51,4);
        trap[59] = new Trap (32,51,4);
        trap[60] = new Trap (33,51,4);
        trap[61] = new Trap (34,52,1);
        trap[62] = new Trap (55,19,2);
        break;
    case LEVEL5:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        currentLevel = 5;
        startTime = SDL_GetTicks();
        player = new Player("Assets/Character/spider.png",37,25);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        teleporter[0] = new Teleporter (22,22);
        teleporter[1] = new Teleporter (24,22);
        bomb[0] = new Bomb (29,18,3);
        bomb[1] = new Bomb (21,15,2);
        bomb[2] = new Bomb (17,19,3);
        trap[0] = new Trap (40,17,2);
        trap[1] = new Trap (40,18,2);
        trap[2] = new Trap (40,19,2);
        trap[3] = new Trap (27,17,4);
        trap[4] = new Trap (30,15,4);
        trap[5] = new Trap (31,16,1);
        trap[6] = new Trap (30,17,3);
        trap[7] = new Trap (21,16,1);
        trap[8] = new Trap (19,16,2);
        trap[9] = new Trap (20,17,3);
        trap[10] = new Trap (20,15,4);
        trap[11] = new Trap (18,23,1);
        trap[12] = new Trap (16,23,2);
        trap[13] = new Trap (17,24,3);
        trap[14] = new Trap (17,22,4);
        break;
    case LEVEL6:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        currentLevel = 6;
        startTime = SDL_GetTicks();
        player = new Player("Assets/Character/robin.png",19,12);
        map = new Map(currentLevel);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        teleporter[0] = new Teleporter (17,18);
        teleporter[1] = new Teleporter (23,18);
        coin[0] = new Coin (23,16);
        bomb[0] = new Bomb (29,16,3);
        trap[0] = new Trap (18,23,4);
        trap[1] = new Trap (19,23,4);
        trap[2] = new Trap (23,22,4);
        trap[3] = new Trap (24,22,4);
        trap[4] = new Trap (25,22,4);
        trap[5] = new Trap (26,22,4);
        trap[6] = new Trap (27,22,4);
        break;
    case LEVEL7:
        text = new TextManager(30);
        Mix_FadeOutMusic(500);
        currentLevel = 7;
        startTime = SDL_GetTicks();
        map = new Map(currentLevel);
        player = new Player("Assets/Character/robin.png",20,73);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        lava = new Lava(0,79);
        break;
    default:
        break;
    }
}
void Game::exitState(State id){
    switch(id)
    {
    case MENU:
    case SELECTMAP:
    case GUIDE:
    case SETTING:
        SDL_DestroyTexture(background);
        background = nullptr;
        break;
    case WIN:
    case LOSE:
    case HIGHSCORE:
    case SHOP:
        SDL_DestroyTexture(background);
        background = nullptr;
        delete text;
        text = nullptr;
        break;
    case LEVEL1:
    case LEVEL2:
    case LEVEL3:
    case LEVEL4:
    case LEVEL5:
    case LEVEL6:
    case LEVEL7:
    case LEVEL8:
    case LEVEL9:
        Mix_FadeInMusic(gMusic,-1,500);
        delete text;
        delete player;
        delete map;
        delete lava;
        for (int i = 0; i < 20; i++) delete coin[i];
        for (int i = 0; i < 24; i++) delete bomb[i];
        for (int i = 0; i < 7; i++) delete peak[i];
        for (int i = 0; i < 20; i++) delete bat[i];
        for (int i = 0; i < 63; i++) delete trap[i];
        for (int i = 0; i < 20; i++) delete coin[i];
        for (int i = 0; i < 20; i++) delete teleporter[i];
        break;
    default:
        break;
    }
}
void Game::updateGame(int x){
    if(isPause) return;
    switch(gState)
    {
    case LEVEL1:
    case LEVEL2:
    case LEVEL3:
    case LEVEL4:
    case LEVEL5:
    case LEVEL6:
    case LEVEL7:
        player->Update(camera, player->xpos, player->ypos);
        /// Update objects ///
        if(!x)
        {
            if (lava != nullptr) lava->Update();
            for (int i = 0; i < 20; i++)
            {
                if(coin[i] == nullptr) break;
                coin[i]->Update();
            }
            for (int i = 0; i < 20; i++)
            {
                if(teleporter[i] == nullptr) break;
                teleporter[i]->Update();
            }
            for (int i = 0; i < 24; i++)
            {
                if (bomb[i] == nullptr) break;
                bomb[i]->Update(map);
            }
            for (int i = 0; i < 65; i++)
            {
                if(trap[i] == nullptr) break;
                trap[i]->Update();
            }
            for (int i = 0; i < 7; i++)
            {
                if(peak[i] == nullptr) break;
                peak[i]->Update();
            }
            for (int i = 0; i < 20; i++)
            {
                if(bat[i] == nullptr) break;
                bat[i]->Update(map);
            }
        }
        /// Collision objects
        if(lava != nullptr && player->Collision(lava->hitbox))
        {
            isLose = true;
            break;
        }
        for (int i = 0; i < 20; i++)
        {
            if(coin[i] == nullptr) break;
            if(player->Collision(coin[i]->hitbox) && !coin[i]->collected)
            {
                coin[i]->collected = true;
                gCoin++;
            }
        }
        for (int i = 0; i < 24; i++)
        {
            if(bomb[i] == nullptr) break;
            if(player->Collision(bomb[i]->hitbox) && bomb[i]->wait == false)
            {
                isLose = true;
                break;
            }
        }
        for(int i = 0; i < 65; i++)
        {
            if(trap[i] == nullptr) break;
            if(player->Collision(trap[i]->hitbox))
            {
                if(trap[i]->activated && SDL_GetTicks() - trap[i]->activatedTime > 400)
                {
                    isLose = true;
                    break;
                }
                else if (!trap[i]->activated)
                {
                    trap[i]->activatedTime = SDL_GetTicks();
                    trap[i]->activated = true;
                }
            }
        }
        for (int i = 0; i < 20; i++)
        {
            if(bat[i] == nullptr) break;
            if(player->Collision(bat[i]->hitbox))
            {
                isLose = true;
                break;
            }
        }
        for (int i = 0; i < 7; i++)
        {
            if(peak[i] == nullptr) break;
            if(player->Collision(peak[i]->hitbox) && peak[i]->activated)
            {
                isLose = true;
                break;
            }
        }
        break;
    default:
        break;
    }
    if(isLose) {switchState(LOSE); isLose = false;}
    if(isWin)
    {
        tempScore = SDL_GetTicks() - startTime;
        if(tempScore < highScore[currentLevel-1])
        {
            highScore[currentLevel-1] = tempScore;
        }
        isWin = false;
        switchState(WIN);
    }
}































































































bool Game::isInside(int x, int y,int x1, int x2, int y1, int y2)
{
    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}
void Game::switchState(State id)
{
    Game::exitState(gState);
    Game::enterState(id);
    gState = id;
    changeState = true;
    SDL_Delay(100);
}
void Game::initGame()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Openning...\n";
    TTF_Init();
    gWindow = SDL_CreateWindow("Escape From Cave",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 992, 672, 0);
    Mix_OpenAudio( 30000, MIX_DEFAULT_FORMAT, 2, 2048 );
    gMusic = Mix_LoadMUS("Assets/Sound/music.mp3");
    gChunk1 = Mix_LoadWAV("Assets/Sound/chunk1.wav");
    Mix_PlayMusic(gMusic,-1);
    gRenderer = SDL_CreateRenderer(gWindow,-1,0);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    // Export save game file //
    std::ifstream file("Assets/savegame.txt");
    file >> isEnglish;
    file >> maxLevel;
    file >> gCoin;
    for (int i = 0; i < 9; i++) file >> highScore[i];
    file.close();
    enterState(gState);
}
void Game::closeGame()
{
    // Import save game file //
    std::ofstream file("Assets/savegame.txt");
    file << isEnglish;
    file << " ";
    file << maxLevel;
    file << " ";
    file << gCoin;
    for (int i = 0; i < 9; i++)
    {
        file << " ";
        file << highScore[i];
    }
    file.close();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	Mix_FreeChunk(gChunk1);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "...Closed\n";
}
