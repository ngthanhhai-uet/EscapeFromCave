#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Peak.hpp"
#include "Trap.hpp"
#include "TextManager.hpp"
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
Bomb* bomb[14];
Peak* peak;
Trap* trap[59];
SDL_Rect camera;

void Game::handleEvent(){
    SDL_Event gEvent;
    SDL_PollEvent(&gEvent);
	if(gEvent.type == SDL_QUIT) isRunning = false;
	int x, y;
	switch(gState)
	{
    case LEVEL1:
    case LEVEL2:
    case LEVEL3:
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
//        case SDL_MOUSEMOTION:
//            SDL_GetMouseState(&x,&y);
//            if(isInside(x,y,353,639,288,377))
//            {
//                text->Render("PLAY",496,336,1);
//                SDL_RenderPresent(gRenderer);
//            }
//            if(isInside(x,y,353,639,401,489))
//            {
//                text->Render("SETTING",496,447,1);
//                SDL_RenderPresent(gRenderer);
//            }
//            if(isInside(x,y,353,639,514,603))
//            {
//                text->Render("QUIT",496,558,1);
//                SDL_RenderPresent(gRenderer);
//            }
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
            if(isInside(x,y,295,396,186,299)) switchState(LEVEL1);
            if(isInside(x,y,445,546,186,299) && maxLevel >= 2) switchState(LEVEL2);
            if(isInside(x,y,595,696,186,299) && maxLevel >= 3) switchState(LEVEL3);
            if(isInside(x,y,295,396,347,460) && maxLevel >= 4) switchState(LEVEL4);
            if(isInside(x,y,445,546,347,460) && maxLevel >= 5) switchState(LEVEL5);
            if(isInside(x,y,595,696,347,460) && maxLevel >= 6) switchState(LEVEL6);
            if(isInside(x,y,913,970,21,76)) switchState(MENU);
            if(isInside(x,y,560,890,568,600)) switchState(GUIDE);
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
    switch(gState)
    {
    case MENU:
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        if(isEnglish == true)
        {
            text->Render("PLAY", 496, 335, 0); text->Render("SETTING", 496, 450, 0); text->Render("QUIT", 496, 560, 0);
        }
        else
        {
            text->Render("CHOI", 496, 335, 0); text->Render("CAI DAT", 496, 450, 0); text->Render("THOAT", 496, 560, 0);
        }
        break;
    case SELECTMAP:
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        if(isEnglish == true)
        {
            text->Render("LEADERBOARD", 200, 580, 0); text->Render("STORE", 500, 580, 0); text->Render("HOW TO PLAY", 800, 580, 0);
            text->Render("I",347,245,0); text->Render("II",497,245,0); text->Render("III",647,245,0);
            text->Render("IV",347,405,0); text->Render("V",496,406,0); text->Render("VI",645,405,0);
        }
        else
        {
            text->Render("DIEM CAO", 200, 580, 0); text->Render("CUA HANG", 505, 580, 0); text->Render("HUONG DAN", 800, 580, 0);
        }
        break;
    case GUIDE:
    case WIN:
    case LOSE:
    case SETTING:
        SDL_RenderCopy(Game::gRenderer,background,NULL,NULL);
        break;
    case LEVEL1:
        map->DrawMap(camera);
        player->Render();
        for (int i = 0; i < 10; i++)
        {
            trap[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 3; i++)
        {
            bat[i]->Render(player->xpos, player->ypos);
        }
        break;
    case LEVEL2:
        map->DrawMap(camera);
        player->Render();
        for (int i = 0; i < 59; i++)
        {
            trap[i]->Render(player->xpos, player->ypos);
        }
        for (int i = 0; i < 20; i++)
        {
            bat[i]->Render(player->xpos, player->ypos);
        }
        break;
    case LEVEL3:
        map->DrawMap(camera);
        player->Render();
        for (int i = 0; i < 14; i++) bomb[i]->Render(player->xpos, player->ypos);
        break;
    case LEVEL4:
        break;
    case LEVEL5:
        break;
    default:
        break;
    }
//        map->DrawMap(camera);
//        player->Render();
//        bat->Render(player->xpos, player->ypos);
//        bomb->Render(player->xpos, player->ypos);
//        peak->Render(player->xpos, player->ypos);
//        trap->Render(player->xpos, player->ypos);
    SDL_RenderPresent(gRenderer);
}
void Game::enterState(State id){
    switch(id)
    {
    case LOSE:
        background = TextureManager::LoadTexture("Assets/State/lose.png");
        break;
    case WIN:
        background = TextureManager::LoadTexture("Assets/State/win.png");
        break;
    case MENU:
        background = TextureManager::LoadTexture("Assets/State/menu.png");
        text = new TextManager(35);
        break;
    case SELECTMAP:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/selectmap_en.png");
        else background = TextureManager::LoadTexture("Assets/State/selectmap_vn.png");
        text = new TextManager(35);
        break;
    case SETTING:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/setting_en.png");
        else background = TextureManager::LoadTexture("Assets/State/setting_vn.png");
        break;
    case GUIDE:
        if (isEnglish == true) background = TextureManager::LoadTexture("Assets/State/guide_en.png");
        else background = TextureManager::LoadTexture("Assets/State/guide_vn.png");
        break;
    case LEVEL1:
        Mix_FadeOutMusic(500);
        currentLevel = 1;
        map = new Map(currentLevel);
        player = new Player("Assets/Character/spider.png",25,12);
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
        Mix_FadeOutMusic(500);
        currentLevel = 2;
        map = new Map(currentLevel);
        player = new Player("Assets/Character/spider.png",42,97);
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
        Mix_FadeOutMusic(500);
        currentLevel = 3;
        map = new Map(currentLevel);
        player = new Player("Assets/Character/spider.png",30,33); // 52 60
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
        break;
    case LEVEL5:
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
        SDL_DestroyTexture(background);
        delete text;
        break;
    case GUIDE:
    case WIN:
    case LOSE:
    case SETTING:
        SDL_DestroyTexture(background);
        background = nullptr;
        break;
    case LEVEL1:
        Mix_FadeInMusic(gMusic,-1,500);
//        delete map;
        map = nullptr;
//        delete player;
        player = nullptr;
        for (int i = 0; i < 3; i++)
        {
//            delete bat[i];
            bat[i] = nullptr;
        }
        for (int i = 0; i < 10; i++)
        {
//            delete trap[i];
            trap[i] = nullptr;
        }
        break;
    case LEVEL2:
        Mix_FadeInMusic(gMusic,-1,500);
        map = nullptr;
        player = nullptr;
        for (int i = 0; i < 20; i++) bat[i] = nullptr;
        for (int i = 0; i < 59; i++) trap[i] = nullptr;
        break;
    case LEVEL3:
        Mix_FadeInMusic(gMusic,-1,500);
        map = nullptr;
        player = nullptr;
        for (int i = 0; i < 14; i++) bomb[i] = nullptr;
        break;
    case LEVEL4:
        break;
    case LEVEL5:
        break;
    default:
        break;
    }
}
void Game::updateGame(int x){

    switch(gState)
    {
    case LEVEL1:
        player->Update(camera, player->xpos, player->ypos);
        if(!x)
        {
            for (int i = 0; i < 3; i++) bat[i]->Update(map);
            for (int i = 0; i < 10; i++) trap[i]->Update();
        }
        for (int i = 0; i < 3; i++)
        {
            if(player->Collision(bat[i]->hitbox))
            {
                isLose = true;
                break;
            }
        }
        for(int i = 0; i < 10; i++)
        {
            if(player->Collision(trap[i]->hitbox))
            {
                if(trap[i]->activated)
                {
                    if(SDL_GetTicks() - trap[i]->activatedTime > 300)
                    {
                        isLose = true;
                        break;
                    }
                }
                else
                {
                    trap[i]->activatedTime = SDL_GetTicks();
                    trap[i]->activated = true;
                }
            }
        }
        break;
    case LEVEL2:
        player->Update(camera, player->xpos, player->ypos);
        if(!x)
        {
            for (int i = 0; i < 20; i++) bat[i]->Update(map);
            for (int i = 0; i < 59; i++) trap[i]->Update();
        }
        for (int i = 0; i < 20; i++)
        {
            if(player->Collision(bat[i]->hitbox))
            {
                isLose = true;
                break;
            }
        }
        for(int i = 0; i < 59; i++)
        {
            if(player->Collision(trap[i]->hitbox))
            {
                if(trap[i]->activated)
                {
                    if(SDL_GetTicks() - trap[i]->activatedTime > 300)
                    {
                        isLose = true;
                        break;
                    }
                }
                else
                {
                    trap[i]->activatedTime = SDL_GetTicks();
                    trap[i]->activated = true;
                }
            }
        }
        break;
    case LEVEL3:
        player->Update(camera, player->xpos, player->ypos);
        if(!x)
        {
            for (int i = 0; i < 14; i++) bomb[i]->Update(map);
        }
        for (int i = 0; i < 14; i++)
        {
            if(player->Collision(bomb[i]->hitbox))
            {
//                isLose = true;
                break;
            }
        }
        break;
    case LEVEL4:
        break;
    case LEVEL5:
        break;
    default:
        break;
    }
    /*
    player->Update(camera, player->xpos, player->ypos);
        if(!x)
        {
            bat->Update(map);
            bomb->Update(map);
            peak->Update();
            trap->Update();
        }
        if(player->Collision(bat->hitbox)) isLose = true;
        if(player->Collision(bomb->hitbox)) isLose = true;
        if(player->Collision(peak->hitbox) && peak->activated) isLose = true;
        if(player->Collision(trap->hitbox))
        {
            if(trap->activated)
            {
                if(SDL_GetTicks()-trap->activatedTime>500) isLose = true;
            }
            else
            {
                trap->activatedTime = SDL_GetTicks();
                trap->activated = true;
            }
        }
    */
    if(isLose) {switchState(LOSE); isLose = false;}
    if(isWin) {switchState(WIN); isWin = false;}
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
    enterState(gState);
}
void Game::closeGame()
{
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
