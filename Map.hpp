#ifndef Map_hpp
#define Map_hpp
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
class Map
{
public:
    Map(int level);
    ~Map();
    void LoadMap(int level);
    void DrawMap(SDL_Rect camera);
    std::vector<std::vector<int>> curr_map;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture *tile;
};
#endif
