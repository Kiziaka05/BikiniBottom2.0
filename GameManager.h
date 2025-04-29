#ifndef GAMEMANAGER_H_DEFINED
#define GAMEMANAGER_H_DEFINED

#include "AI.h"
#include "Cell.h"
#include "Event.h"
#include "Map.h"
#include "RenderGame.h"
#include "Unit.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class GameManager
{
private:
    Map *GameMap;
    MainHero *Hero;
    RenderGame *NewRender;
    Event *NewEvent;

public:
    GameManager();
    ~GameManager();

    void GameLoop();
};

#endif //GAMEMANAGER_H_DEFINED
