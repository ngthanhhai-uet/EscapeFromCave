#ifndef Trap_hpp
#define Trap_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Trap
{
public:
    Trap(int x, int y, int type);
    void Update();
    void Render(int x, int y);
    SDL_Rect hitbox;
    SDL_Texture* trapoff;
    SDL_Texture* trapon;
    bool activated;
    int activatedTime;
    int xTrap, yTrap;
    int typeTrap;
};
#endif // Trap_hpp
