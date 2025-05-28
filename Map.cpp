#include "Map.h"

HexMap::HexMap(int radius) : Radius(radius)
{
    for(int q = -radius; q <=radius; q++)
    {
        int r1 = std::max(-radius, -q - radius);
        int r2 = std::min(radius, -q + radius);
        std::vector<Hex> Column;
        for(int r = r1; r <= r2; r++)
        {
            Column.emplace_back(q,r);
        }
        MapGrid.push_back(Column);
    }
    QPoint S = {0, 0};
    UpdateVisibility(S);
}

Hex& HexMap::GetLocation(int q, int r)
{
    for(auto& Hex_ : MapGrid[q + Radius])
    {
        if(Hex_.r == r)
            return Hex_;
    }
    throw std::out_of_range("No such hex in column");
}

Hex& HexMap::GetQPointLoc(QPoint& OHex)
{
    return GetLocation(OHex.x(), OHex.y());
}

bool HexMap::ContainsHex(int q, int r)
{
    int qi = q + Radius;
    if(qi < 0 || qi >= MapGrid.size())
        return false;
    auto& Col = MapGrid[qi];
    for(auto& Hex_ : Col)
    {
        if(Hex_.q == q && Hex_.r == r)
            return true;
    }
    return false;
}

void HexMap::UpdateVisibility(QPoint& HeroPos)
{
    for(auto& Col : MapGrid)
    {
        for(auto& Hex_ : Col)
        {
            Hex_.IsVisible = false;
        }
    }

    Hex& CenterHex = GetQPointLoc(HeroPos);
    CenterHex.IsVisible = true;
    CenterHex.IsExplored = true;

    for(auto& Col : MapGrid)
    {
        for(auto& Hex_ : Col)
        {
            if(CenterHex.IsHeighbor(Hex_))
            {
                Hex_.IsVisible = true;
                Hex_.IsExplored = true;
            }
        }
    }
}

// void Map::GenerateMap() //������� ��������� ����
// {
//     //���� ������������ ����������� ������� size*size, ���� ����������� � "�������"
//     Size = 3;

//     MapArray.resize(Size);
//     for (int i = 0; i < Size; i++) {
//         MapArray[i].resize(Size);
//         for (int j = 0; j < Size; j++) {
//             MapArray[i][j] = new Cell(i, j);
//         }
//     }
// }

// void Map::RemoveMap() //�������� ���'���
// {
//     if (MapArray.empty()) {
//         std::cout << "Array is empty!";
//         return;
//     }
//     for (int i = 0; i < Size; i++) {
//         for (int j = 0; j < Size; j++) {
//             delete MapArray[i][j];
//         }
//     }
//     MapArray.clear();

//     std::cout << std::endl << "Array cleared!" << std::endl;
// }

// Map::Map() //������� �����������
// {
//     GenerateMap();
// }

// Map::~Map() //����������
// {
//     RemoveMap();
// }

// std::ostream &operator<<(std::ostream &Stream, const Map &MapToPrint)
// {
//     if (MapToPrint.MapArray.empty())
//         return Stream << "Map does not exist!" << std::endl;

//     Stream << "Map displays cell by cell\nHere is a list of abbreviations for parameters:"
//            << "\nv - visibility\nhs - have something?\nvp - is valid position?" << std::endl
//            << std::endl;

//     int Size = MapToPrint.MapArray.size();
//     for (int i = 0; i < Size; i++) {
//         for (int j = 0; j < Size; j++) {
//             Stream << *MapToPrint.MapArray[i][j] << " | ";
//         }
//         Stream << std::endl << std::endl;
//     }

//     return Stream;
// }

// Cell *Map::GetCell(int XLocation1, int YLocation1)
// {
//     return MapArray[XLocation1][YLocation1];
// }

// int Map::GetSize()
// {
//     return Size;
// }
