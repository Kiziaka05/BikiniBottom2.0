#ifndef RENDERGAME_H_DEFINED
#define RENDERGAME_H_DEFINED

#include "Cell.h"
#include "Map.h"

class RenderGame
{
private:
    Map *GameMap;

public:
    RenderGame(Map *GameMap1);
    ~RenderGame();
    void Render();
};

#endif //RENDERGAME_H_DEFINED
