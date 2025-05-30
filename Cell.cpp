#include "Cell.h"

std::pair<int, int> Hex::GetQR() const { return std::make_pair(q, r); }
bool Hex::VisibilityState() const { return IsVisible; }
bool Hex::ExplorationState() const { return IsExplored; }

QPointF Hex::GetCenter() const
{
    float x = HexSize * 3.0 / 2.0 * q;
    float y = HexSize * std::sqrt(3.0) * (r + q / 2.0);

    return {x,y};
}

std::vector<QPointF> Hex::GetCorners() const
{
    std::vector<QPointF> Corners;
    QPointF Center = GetCenter();

    for(int i = 0; i < 6; i++)
    {
        float AngleDeg = 60.0 * i;
        float AngleRad = AngleDeg * M_PI / 180.0;
        float x = Center.x() + HexSize * std::cos(AngleRad);
        float y = Center.y() + HexSize * std::sin(AngleRad);
        Corners.emplace_back(x,y);
    }
    return Corners;
}

bool Hex::IsNeighbor(const Hex& OHex) const
{
    int dq = OHex.q - q;
    int dr = OHex.r - r;
    const std::vector<QPoint> Directions = {
        {1,0},{1,-1},{0,-1},
        {-1,0},{-1,1},{0,1}
    };

    for(const auto& Dir : Directions)
    {
        if(dq == Dir.x() && dr == Dir.y())
            return true;
    }
    return false;
}

// void Cell::AddUnit()
// {
//     if (!HaveSomething)
//         return;

//     int RandomValue = 1 + rand() % 100;
//     if (RandomValue <= 30)
//         CurrUnit = new Enemy();
//     else if (RandomValue > 30 && RandomValue < 50)
//         CurrUnit = new Friend();
//     else if (RandomValue >= 50 && RandomValue < 70)
//         CurrUnit = new StructBreak();
//     else
//         CurrUnit = new StructUnBreak();
// }

// void Cell::RemoveUnit()
// {
//     if (!HaveSomething)
//         return;

//     HaveSomething = false;
//     IsValidPosition = true;
//     delete CurrUnit;
// }

// Unit *Cell::GetUnit()
// {
//     return CurrUnit;
// }

// void Cell::GenerateCell(int XLocation1, int YLocation1)
// {
//     XLocation = XLocation1;
//     YLocation = YLocation1;
//     HaveSomething = rand() % 2;
//     IsValidPosition = rand() % 2;
//     IsVisible = rand() % 2;

//     if (HaveSomething) {
//         AddUnit();
//     }
// }

// void Cell::RemoveCell()
// {
//     RemoveUnit();
//     IsVisible = false;
//     IsValidPosition = false;
//     XLocation = -1;
//     YLocation = -1;
// }

// Cell::Cell(int XLocation1, int YLocation1)
// {
//     GenerateCell(XLocation1, YLocation1);
// }

// Cell::~Cell()
// {
//     RemoveCell();
// }

// std::pair<int, int> Cell::GetLocation()
// {
//     return std::pair<int, int>(XLocation, YLocation);
// }

// bool Cell::IsCellVisisble()
// {
//     return IsVisible;
// }

// bool Cell::IsCellValid()
// {
//     return IsValidPosition;
// }

// bool Cell::IsCellHaveSomething()
// {
//     return HaveSomething;
// }

// std::ostream &operator<<(std::ostream &Stream, const Cell &SomeCell)
// {
//     if (SomeCell.HaveSomething) {
//         Stream << SomeCell.CurrUnit->Type();
//     } else {
//         Stream << "v: " << SomeCell.IsVisible << "vp: " << SomeCell.IsValidPosition
//                << "hs: " << SomeCell.HaveSomething;
//     }
//     return Stream;
// }
