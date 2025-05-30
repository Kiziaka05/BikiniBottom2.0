#ifndef CELL_H_DEFINED
#define CELL_H_DEFINED

#include "Unit.h"
#include "RandomGenerator.h"
#include <utility>
#include <cmath>
#include <vector>
#include <QPointF>

class Hex
{
private:
    int q,r;
    bool IsVisible;
    bool IsExplored;

public:

    static constexpr float HexSize = 60.0;
    Hex(int q_, int r_) : q(q_), r(r_), IsVisible(false), IsExplored(false)
    {}

    std::pair<int, int> GetQR() const;
    bool VisibilityState() const;
    bool ExplorationState() const;
    QPointF GetCenter() const;
    std::vector<QPointF> GetCorners() const;
    bool IsNeighbor(const Hex& OHex) const;
    friend class HexMap;
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
