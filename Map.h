#ifndef MAP_H_DEFINED
#define MAP_H_DEFINED

#include "Cell.h"
#include <iostream>
#include <vector>

class HexMap
{
public:
    int Width, Height;
    int Radius;
    HexMap(int radius);
    Hex& GetLocation(int q, int r);
    Hex& GetQPointLoc(QPoint& OHex);
    std::vector<std::vector<Hex>>& GetMap() {return MapGrid;}
    bool ContainsHex(int q, int r);
private:
    std::vector<std::vector<Hex>> MapGrid;
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
