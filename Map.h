#ifndef MAP_H_DEFINED
#define MAP_H_DEFINED

#include "Cell.h"
#include <iostream>
#include <vector>

class HexMap
{
public:
    int Width, Height;
    std::vector<std::vector<Hex>> MapGrid;

    HexMap(int w, int h);
    Hex& GetLocation(int q, int r);
};

class Map
{
private:
    int Size;
    std::vector<std::vector<Cell *>> MapArray;

    void GenerateMap();
    void RemoveMap();

public:
    Map();
    ~Map();
    friend std::ostream &operator<<(std::ostream &Stream, const Map &MapToPrint);
    int GetSize();
    Cell *GetCell(int XLocation1, int YLocation1);
};

#endif //MAP_H_DEFINED
