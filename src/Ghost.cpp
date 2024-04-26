#include "Ghost.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "../manager/TextureManager.hpp"
#include <vector>
#include <queue>
#include <algorithm>
Ghost::Ghost(int x, int y, Map* map)
{
    x *= 32;
    y *= 32;
    xGhost = x; yGhost = y;
    ghostTexture = TextureManager::LoadTexture("Assets/Object/ghost.png");
    hitbox.x = x; hitbox.y = y; hitbox.w = 32; hitbox.h = 32;
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 70; j++)
        {
            ghostMap[i][j] = map->curr_map[i][j];
        }
    }
}
void Ghost::Update(int x, int y)
{
    std::vector<std::pair<int, int>> path = BFS(xGhost, yGhost, x, y);
    for (const auto& p : path) {
        std::cout << "(" << p.first << ", " << p.second << ") " << "\n";
    }
}
std::vector<std::pair<int, int>> Ghost::BFS(int xS, int yS, int xE, int yE)
{
    xS /= 32;
    yS /= 32;
    xE /= 32;
    yE /= 32;
    bool check[70][60] = {false};
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    std::queue<int> xq;
    std::queue<int> yq;
    xq.push(xS);
    yq.push(yS);
    prev[yS][xS] = {xS, yS};
    check[yS][xS] = true;
    bool isFind = false;
    while (!xq.empty())
    {
        int tempX = xq.front();
        int tempY = yq.front();
        xq.pop();
        yq.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = tempX + dx[i];
            int ny = tempY + dy[i];
            if (nx < 0 || nx >= 60 || ny < 0 || ny >= 70) continue;
            if (ghostMap[ny][nx] <= 64) continue;
            if (check[ny][nx]) continue;
            xq.push(nx);
            yq.push(ny);
            prev[ny][nx] = {tempX, tempY};
            check[ny][nx] = true;
            if (nx == xE && ny == yE)
            {
                isFind = true;
                break;
            }
        }
        if (isFind) break;
    }
    std::vector<std::pair<int, int>> shortestPath;
    std::pair<int, int> end = {xE, yE};
    while (!(end.first == xS && end.second == yS))
    {
        shortestPath.push_back(end);
        end = prev[end.second][end.first];
    }
    shortestPath.push_back({xS, yS});
    reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}
void Ghost::Render(int x, int y)
{
    SDL_Rect temp = {xGhost - x + 480, yGhost - y + 320, 32, 32};
    SDL_RenderCopy(Game::gRenderer, ghostTexture, nullptr, &temp);
}
Ghost::~Ghost()
{
    if (ghostTexture != nullptr)
    {
        SDL_DestroyTexture(ghostTexture);
        ghostTexture = nullptr;
    }
}
