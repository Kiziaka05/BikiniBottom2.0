#ifndef CELL_H_DEFINED
#define CELL_H_DEFINED

#include "Unit.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <QPointF>

constexpr float HexSize = 40.0;

class Hex
{
public:
    int q,r;

    Hex(int q_, int r_) : q(q_), r(r_)
    {}

    QPointF GetCenter();
    std::vector<QPointF> GetCorners();
};

class Cell
{
private:
    int XLocation;
    int YLocation;
    bool IsVisible;
    bool HaveSomething;
    bool IsValidPosition;

    void GenerateCell(int XLocation1, int YLocation1);
    void RemoveCell();

protected:
    Unit *CurrUnit;

public:
    Cell(int XLocation1, int YLocation1);
    ~Cell();
    std::pair<int, int> GetLocation();
    bool IsCellVisisble();
    bool IsCellValid();
    bool IsCellHaveSomething();
    friend std::ostream &operator<<(std::ostream &Stream, const Cell &SomeCell);
    Unit *GetUnit();
    void AddUnit();
    void RemoveUnit();
};

#endif //CELL_H_DEFINED
