#ifndef CELL_H_DEFINED
#define CELL_H_DEFINED

#include "Unit.h"
#include "RandomGenerator.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <QPointF>

constexpr float HexSize = 60.0;

class Hex
{
public:
    int q,r;
    bool IsVisible = false;
    bool IsExplored = false;

    Hex(int q_, int r_) : q(q_), r(r_)
    {}

    QPointF GetCenter();
    std::vector<QPointF> GetCorners();
    bool IsHeighbor(Hex& OHex);
};

// class Cell
// {
// private:
//     int XLocation;
//     int YLocation;
//     bool IsVisible;
//     bool HaveSomething;
//     bool IsValidPosition;

//     void GenerateCell(int XLocation1, int YLocation1);
//     void RemoveCell();

// protected:
//     Unit *CurrUnit;

// public:
//     Cell(int XLocation1, int YLocation1);
//     ~Cell();
//     std::pair<int, int> GetLocation();
//     bool IsCellVisisble();
//     bool IsCellValid();
//     bool IsCellHaveSomething();
//     friend std::ostream &operator<<(std::ostream &Stream, const Cell &SomeCell);
//     Unit *GetUnit();
//     void AddUnit();
//     void RemoveUnit();
// };

#endif //CELL_H_DEFINED
