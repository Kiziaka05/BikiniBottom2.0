#include "Cell.h"

float Hex::GetWidth()
{
    return HexSize * 2;
}

float Hex::GetHeight()
{
    return std::sqrt(3.0) / 2.0 * GetWidth();
}

QPointF Hex::GetCenter()
{
    float x = HexSize * 3.0 / 2.0 * q;
    float y = GetHeight() * (r + 0.5 * (q % 2));

    return {x,y};
}

std::vector<QPointF> Hex::GetCorners()
{
    std::vector<QPointF> Corners;
    QPointF Center = GetCenter();

    for(int i = 0; i < 6; i++)
    {
        float Angle = M_PI / 6 + i * M_PI / 3;
        float x = Center.x() + HexSize * std::cos(Angle);
        float y = Center.y() + HexSize * std::sin(Angle);
        Corners.emplace_back(x,y);
    }
    return Corners;
}

void Cell::AddUnit()
{
    if (!HaveSomething)
        return;

    int RandomValue = 1 + rand() % 100;
    if (RandomValue <= 30)
        CurrUnit = new Enemy();
    else if (RandomValue > 30 && RandomValue < 50)
        CurrUnit = new Friend();
    else if (RandomValue >= 50 && RandomValue < 70)
        CurrUnit = new StructBreak();
    else
        CurrUnit = new StructUnBreak();
}

void Cell::RemoveUnit()
{
    if (!HaveSomething)
        return;

    HaveSomething = false;
    IsValidPosition = true;
    delete CurrUnit;
}

Unit *Cell::GetUnit()
{
    return CurrUnit;
}

void Cell::GenerateCell(int XLocation1, int YLocation1)
{
    XLocation = XLocation1;
    YLocation = YLocation1;
    HaveSomething = rand() % 2;
    IsValidPosition = rand() % 2;
    IsVisible = rand() % 2;

    if (HaveSomething) {
        AddUnit();
    }
}

void Cell::RemoveCell()
{
    RemoveUnit();
    IsVisible = false;
    IsValidPosition = false;
    XLocation = -1;
    YLocation = -1;
}

Cell::Cell(int XLocation1, int YLocation1)
{
    GenerateCell(XLocation1, YLocation1);
}

Cell::~Cell()
{
    RemoveCell();
}

std::pair<int, int> Cell::GetLocation()
{
    return std::pair<int, int>(XLocation, YLocation);
}

bool Cell::IsCellVisisble()
{
    return IsVisible;
}

bool Cell::IsCellValid()
{
    return IsValidPosition;
}

bool Cell::IsCellHaveSomething()
{
    return HaveSomething;
}

std::ostream &operator<<(std::ostream &Stream, const Cell &SomeCell)
{
    if (SomeCell.HaveSomething) {
        Stream << SomeCell.CurrUnit->Type();
    } else {
        Stream << "v: " << SomeCell.IsVisible << "vp: " << SomeCell.IsValidPosition
               << "hs: " << SomeCell.HaveSomething;
    }
    return Stream;
}
