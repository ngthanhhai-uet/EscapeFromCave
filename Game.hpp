#ifndef Game_hpp
#define Game_hpp
#include <iostream>
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
    bool isRunning;
    bool isEnglish = true;
    bool isLose = false;
    bool isWin = false;
    bool changeState;
    bool isInside(int x, int y, int x1, int x2, int y1, int y2);
    enum State
    {
        MENU,
        SELECTMAP,
        SETTING,
        GUIDE,
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5,
        LEVEL6,
        LOSE,
        WIN,
    };
    State gState = MENU;
    void enterState(State id);
    void exitState(State id);
    void switchState(State id);
    int maxLevel = 3;
    int currentLevel = 1;
    SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
};
#endif
