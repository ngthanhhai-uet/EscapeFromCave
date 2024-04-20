#ifndef Teleporter_hpp
#define Teleporter_hpp
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
class Teleporter
{
public:
    Teleporter(int x, int y);
    ~Teleporter();
    int xTeleporter;
    int yTeleporter;
    int frame = 0;
    SDL_Texture *teleporterTexture;
    SDL_Rect animation;
    void Update();
    void Render(int x, int y);
};
#endif // Teleporter_hpp
