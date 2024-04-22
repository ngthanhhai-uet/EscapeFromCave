#ifndef Game_hpp
#define Game_hpp
#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Game
{
private:
public:

    Game();
    ~Game();

    void initGame();
    void handleEvent();
    void updateGame(int x);
    void renderGame();
    void closeGame();
    // - Temporatory varible - //
    bool isRunning;
    bool isLose = false;
    bool isWin = false;
    bool isPause = false;
    int startTime;
    int tempScore;
    int currentLevel;
    bool changeState;
    // - Save varible - //
    bool isEnglish;
    int maxLevel;
    int gCoin;
    int highScore[9];
    bool isInside(int x, int y, int x1, int x2, int y1, int y2);
    enum State
    {
        MENU,
        SELECTMAP,
        SETTING,
        GUIDE,
        SHOP,
        HIGHSCORE,
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5,
        LEVEL6,
        LEVEL7,
        LEVEL8,
        LEVEL9,
        LOSE,
        WIN,
    };
    State gState = MENU;
    void enterState(State id);
    void exitState(State id);
    void switchState(State id);
    SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    Mix_Chunk* gChunk1; // beep //
    Mix_Chunk* gChunk2; // trampoline //
    Mix_Chunk* gChunk3; // coin //
    Mix_Chunk* gChunk4; // win //
    Mix_Chunk* gChunk5; // tele //
    Mix_Chunk* gChunk6; // death by spike //
    Mix_Chunk* gChunk7; // death by bomb? //
};
#endif
