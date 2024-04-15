
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
    void DrawMap(SDL_Rect camera); // Draw map follow camera //
    std::vector<std::vector<int>> curr_map;
    SDL_Rect src; // Source's texture position //
    SDL_Rect dest; // Destination render texture position //
    SDL_Texture *tile; // This is element source map //
};
#endif
