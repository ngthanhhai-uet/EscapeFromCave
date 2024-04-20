#ifndef Peak_hpp
#define Peak_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Peak
{
public:
    Peak(int x, int y);
    ~Peak();
    void Update();
    void Render(int x, int y);
    int xPeak; int yPeak;
    bool activated = false;
    SDL_Rect hitbox;
    SDL_Texture* peakon;
    SDL_Texture* peakoff;
    // Quan li thoi gian //
    int offTime = 0;
    int onTime = 0;
    int lastTime = 0;
    int deltaTime();
};
#endif // Peak_hpp
