#include "Game.hpp"
#include "Bat.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "TextManager.hpp"
Game::Game(){}
Game::~Game(){}
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Texture* background;
Mix_Music* gMusic = NULL;
TextManager* text;
Map* map;
Bat* bat;
Bomb* bomb;
Player* player;
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
            text->Render("BANG XEP HANG", 200, 580, 0); text->Render("CUA HANG", 505, 580, 0); text->Render("HUONG DAN", 800, 580, 0);
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
        break;
    case LEVEL2:
        map->DrawMap(camera);
        player->Render();
        bat->Render(player->xpos, player->ypos);
        break;
    case LEVEL3:
        map->DrawMap(camera);
        player->Render();
        bat->Render(player->xpos, player->ypos);
        bomb->Render(player->xpos, player->ypos);
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
        player = new Player("Assets/Character/spider.png",26 * 32 ,37 * 32);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        map = new Map(1);
        break;
    case LEVEL2:
        Mix_FadeOutMusic(500);
        currentLevel = 2;
        player = new Player("Assets/Character/spider.png",48 * 32 ,10 * 32);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        map = new Map(2);
        bat = new Bat(48*32, 10*32, 0);
        break;
    case LEVEL3:
        Mix_FadeOutMusic(500);
        currentLevel = 3;
        player = new Player("Assets/Character/spider.png",19 * 32 ,39 * 32);
        camera = {player->xpos-480, player->ypos-320, 992, 672};
        map = new Map(3);
        bat = new Bat(19 * 32, 37 * 32, 0);
        bomb = new Bomb(18 * 32, 34 * 32, 1);
    default:
        break;
    }
}
void Game::exitState(State id){
    switch(id)
    {
    case MENU:
    case SELECTMAP:
        SDL_DestroyTexture(background); delete text; break;
    case GUIDE:
    case WIN:
    case LOSE:
    case SETTING:
        SDL_DestroyTexture(background); background = nullptr; break;
    case LEVEL1:
        Mix_FadeInMusic(gMusic,-1,500); map = nullptr; player = nullptr; break;
    case LEVEL2:
        Mix_FadeInMusic(gMusic,-1,500); bat = nullptr; player = nullptr; map = nullptr; break;
    case LEVEL3:
        Mix_FadeInMusic(gMusic,-1,500); bat = nullptr; player = nullptr; map = nullptr; break;
    default:
        break;
    }
}
void Game::updateGame(int x){

    switch(gState)
    {
    case LEVEL1:
        player->Update(camera, player->xpos, player->ypos);
        break;
    case LEVEL2:
        player->Update(camera, player->xpos, player->ypos);
        bat->Update(map);
        break;
    case LEVEL3:
        player->Update(camera, player->xpos, player->ypos);
        if(x == 0) bat->Update(map);
        if(player->Collision(bat->hitbox)) isLose = true;
        if(player->Collision(bomb->hitbox)) isLose = true;
        break;
    default:
        break;
    }
    if(isLose) {switchState(LOSE); isLose = false;}
    if(isWin) {switchState(WIN); isWin = false;}
}















//bool Game::isCollision(SDL_Rect a, SDL_Rect b)
//{
//    int left = a.x > b.x ? a.x : b.x;
//    int right = a.x + a.w < b.x + b.w ? a.x + a.w : b.x + b.w;
//    int top = a.y > b.y ? a.y : b.y;
//    int bot = a.y + a.h < b.y + b.h ? a.y + a.h : b.y + b.h;
//    return (left >= right || top >= bot);
//}
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
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "...Closed\n";
}
