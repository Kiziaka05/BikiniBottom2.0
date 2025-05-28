#ifndef MAP_H_DEFINED
#define MAP_H_DEFINED

#include "Cell.h"
#include <iostream>
#include <vector>

class HexMap
{
private:
    int Radius;
    std::vector<std::vector<Hex>> MapGrid;

    Hex& GetChangeableLocation(int q, int r);
    Hex& GetChangeableQPointLoc(const QPoint& OHex);

public:
    HexMap(int radius);
    int GetRadius() const;
    const Hex& GetLocation(int q, int r) const;
    const Hex& GetQPointLoc(const QPoint& OHex) const;
    const std::vector<std::vector<Hex>>& GetMap() const;
    bool ContainsHex(int q, int r) const;
    void UpdateVisibility(const QPoint& HeroPos);
};

// class Map
// {
// private:
//     int Size;
//     std::vector<std::vector<Cell *>> MapArray;

//     void GenerateMap();
//     void RemoveMap();

// public:
//     Map();
//     ~Map();
//     friend std::ostream &operator<<(std::ostream &Stream, const Map &MapToPrint);
//     int GetSize();
//     Cell *GetCell(int XLocation1, int YLocation1);
// };

#endif //MAP_H_DEFINED
