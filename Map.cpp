#include "Map.h"

HexMap::HexMap(int w, int h)
{
    Width = w;
    Height = h;
    MapGrid.resize(Width);
    for(int q = 0; q < Width; q++)
    {
        MapGrid[q].reserve(Height);
        for(int r = 0; r < Height; r++)
        {
            MapGrid[q].emplace_back(q, r);
        }
    }
}

Hex& HexMap::GetLocation(int q, int r)
{
    return MapGrid[q][r];
}

void Map::GenerateMap() //������� ��������� ����
{
    //���� ������������ ����������� ������� size*size, ���� ����������� � "�������"
    Size = 3;

    MapArray.resize(Size);
    for (int i = 0; i < Size; i++) {
        MapArray[i].resize(Size);
        for (int j = 0; j < Size; j++) {
            MapArray[i][j] = new Cell(i, j);
        }
    }
}

void Map::RemoveMap() //�������� ���'���
{
    if (MapArray.empty()) {
        std::cout << "Array is empty!";
        return;
    }
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            delete MapArray[i][j];
        }
    }
    MapArray.clear();

    std::cout << std::endl << "Array cleared!" << std::endl;
}

Map::Map() //������� �����������
{
    GenerateMap();
}

Map::~Map() //����������
{
    RemoveMap();
}

std::ostream &operator<<(std::ostream &Stream, const Map &MapToPrint)
{
    if (MapToPrint.MapArray.empty())
        return Stream << "Map does not exist!" << std::endl;

    Stream << "Map displays cell by cell\nHere is a list of abbreviations for parameters:"
           << "\nv - visibility\nhs - have something?\nvp - is valid position?" << std::endl
           << std::endl;

    int Size = MapToPrint.MapArray.size();
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            Stream << *MapToPrint.MapArray[i][j] << " | ";
        }
        Stream << std::endl << std::endl;
    }

    return Stream;
}

Cell *Map::GetCell(int XLocation1, int YLocation1)
{
    return MapArray[XLocation1][YLocation1];
}

int Map::GetSize()
{
    return Size;
}
