#ifndef Ghost_hpp
#define Ghost_hpp
#include "Map.hpp"
class Ghost
{
public:
    Ghost(int x, int y, Map *map);
    ~Ghost();
    int xGhost;
    int yGhost;
    std::vector<std::pair<int,int>> BFS(int xS, int yS, int xE, int yE);
    void Update(int x, int y);
    void Render(int x, int y);
    int ghostMap[60][70] = {0};
    std::pair<int, int> prev[60][70];
    SDL_Rect hitbox;
    SDL_Texture *ghostTexture;
};
#endif // Ghost_hpp
