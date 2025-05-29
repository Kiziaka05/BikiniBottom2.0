#include "Map.h"
#include <QFile>
#include <QDataStream>
#include <QIODevice>
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

void HexMap::SaveToFile(const QString& filePath, const QPoint& heroPos) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream out(&file);
    out << static_cast<qint32>(MapGrid.size());
    out << static_cast<qint32>(Radius);

    for (const auto& column : MapGrid)
    {
        out << static_cast<qint32>(column.size());
        for (const auto& hex : column)
        {
            out << static_cast<qint32>(hex.q)
            << static_cast<qint32>(hex.r)
            << static_cast<bool>(hex.IsVisible)
            << static_cast<bool>(hex.IsExplored);
        }
    }

    // Записуємо позицію героя
    out << static_cast<qint32>(heroPos.x());
    out << static_cast<qint32>(heroPos.y());

    file.close();
}
void HexMap::LoadFromFile(const QString& filePath, QPoint& heroPos)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QDataStream in(&file);
    qint32 cols, radius;
    in >> cols >> radius;

    Clear();
    Radius = radius;

    for (int i = 0; i < cols; ++i)
    {
        qint32 rows;
        in >> rows;
        std::vector<Hex> column;
        for (int j = 0; j < rows; ++j)
        {
            qint32 q, r;
            bool isVisible, isExplored;
            in >> q >> r >> isVisible >> isExplored;
            Hex hex(q, r);
            hex.IsVisible = isVisible;
            hex.IsExplored = isExplored;
            column.push_back(hex);
        }
        MapGrid.push_back(std::move(column));
    }

    // 🧍 Завантаження позиції героя (q, r)
    qint32 heroQ, heroR;
    in >> heroQ >> heroR;
    heroPos = QPoint(heroQ, heroR);
}

void HexMap::Clear()
{
    MapGrid.clear();
}
