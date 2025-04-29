#include "RenderGame.h"

RenderGame::RenderGame(Map *GameMap1)
{
    GameMap = GameMap1;
};

RenderGame::~RenderGame() {};

void RenderGame::Render()
{
    if (GameMap == nullptr) {
        std::cout << "Some problem with map initialization!" << std::endl;
        return;
    }
    std::cout << *GameMap;
};
