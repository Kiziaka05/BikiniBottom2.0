#include "Map.h"
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QString>
#include "RandomGenerator.h"

int HexMap::GetRadius() const { return Radius; }
const std::vector<std::vector<Hex>>& HexMap::GetMap() const { return MapGrid; }

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
    GenerateUnits();

    QPoint S = {0, 0};
    UpdateVisibility(S);
}

void HexMap::GenerateUnits()
{
    const double UnitChance = 0.1;
    const double EnemyChance = 0.5;
    const double FriendChance = 0.2;
    const double StructBreakChance = 0.15;
    const double StructUnbreakChance = 0.15;

    for(auto& Col : MapGrid)
    {
        for(Hex& Hex_ : Col)
        {
            if(Hex_.GetQR().first == 0 && Hex_.GetQR().second == 0)
                continue;

            if(RandGenerator::RandDoubleInInterval(0.0, 1.0) < UnitChance)
            {
                double UnitTypeRand = RandGenerator::RandDoubleInInterval(0.0, 1.0);
                Unit* NewUnit = nullptr;
                std::string UnitName;

                if(UnitTypeRand < EnemyChance)
                {
                    UnitName = "Enemy";
                    NewUnit = UnitFabric_.Create(UnitName, 1, 100);
                }
                else if(UnitTypeRand < EnemyChance + FriendChance)
                {
                    UnitName = "Friend";
                    NewUnit = UnitFabric_.Create(UnitName, 1, 50);
                }
                else if(UnitTypeRand < EnemyChance + FriendChance + StructBreakChance)
                {
                    UnitName = "StructBreak";
                    NewUnit = UnitFabric_.Create(UnitName, 0, 30);
                }
                else
                {
                    UnitName = "StructUnBreak";
                    NewUnit = UnitFabric_.Create(UnitName, 0, 0);
                }

                if(NewUnit)
                    Hex_.SetUnit(NewUnit);
            }
        }
    }
}

Hex& HexMap::GetChangeableLocation(int q, int r)
{
    int qi = q + Radius;
    if(qi < 0 || qi >= MapGrid.size())
    {
        throw std::out_of_range("Coordinate q out of range");
    }

    auto& Col = MapGrid[qi];
    for(auto& Hex_ : Col)
    {
        if(Hex_.q == q && Hex_.r == r)
            return Hex_;
    }
    throw std::out_of_range("Coordinate r out of range");
}

Hex& HexMap::GetChangeableQPointLoc(const QPoint& OHex)
{
    return GetChangeableLocation(OHex.x(), OHex.y());
}

const Hex& HexMap::GetLocation(int q, int r) const
{
    int qi = q + Radius;
    if(qi < 0 || qi >= MapGrid.size())
    {
        throw std::out_of_range("Coordinate q out of range");
    }

    const auto& Col = MapGrid[qi];
    for(const auto& Hex_ : Col)
    {
        if(Hex_.q == q && Hex_.r == r)
            return Hex_;
    }
    throw std::out_of_range("Coordinate r out of range");
}

const Hex& HexMap::GetQPointLoc(const QPoint& OHex) const
{
    return GetLocation(OHex.x(), OHex.y());
}

bool HexMap::ContainsHex(int q, int r) const
{
    int qi = q + Radius;
    if(qi < 0 || qi >= MapGrid.size())
        return false;

    const auto& Col = MapGrid[qi];
    for(const auto& Hex_ : Col)
    {
        if(Hex_.q == q && Hex_.r == r)
            return true;
    }
    return false;
}

void HexMap::UpdateVisibility(const QPoint& HeroPos)
{
    for(auto& Col : MapGrid)
    {
        for(auto& Hex_ : Col)
        {
            Hex_.IsVisible = false;
        }
    }

    Hex& CenterHex = GetChangeableQPointLoc(HeroPos);
    CenterHex.IsVisible = true;
    CenterHex.IsExplored = true;

    for(auto& Col : MapGrid)
    {
        for(auto& Hex_ : Col)
        {
            if(CenterHex.IsNeighbor(Hex_))
            {
                Hex_.IsVisible = true;
                Hex_.IsExplored = true;
            }
        }
    }
}

void HexMap::SaveToFile(const QString& filePath, const QPoint& heroPos) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream out(&file);
    out << static_cast<qint32>(MapGrid.size());
    out << static_cast<qint32>(Radius);

    for (const auto& Col : MapGrid)
    {
        out << static_cast<qint32>(Col.size());
        for (const Hex& Hex_ : Col)
        {
            out << static_cast<qint32>(Hex_.q)
            << static_cast<qint32>(Hex_.r)
            << static_cast<bool>(Hex_.IsVisible)
            << static_cast<bool>(Hex_.IsExplored);

            if(Hex_.HaveUnit())
            {
                out << static_cast<bool>(true);
                Unit* Unit_ = Hex_.GetUnit();
                QString SaveType = QString::fromStdString(Unit_->GetSaveType());
                out << SaveType
                    << static_cast<qint32>(Unit_->GetLevel())
                    << static_cast<double>(Unit_->GetHP());
            }
            else
                out << static_cast<bool>(false);
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

    if(cols < 0 || radius < 0)
    {
        file.close();
        return;
    }

    Clear();
    this->Radius = radius;

    for (int i = 0; i < cols; ++i)
    {
        qint32 rows;
        in >> rows;
        if(rows < 0)
        {
            file.close();
            Clear();
            return;
        }

        std::vector<Hex> column;
        for (qint32 j = 0; j < rows; ++j)
        {
            qint32 q, r;
            bool isVisible, isExplored;
            in >> q >> r >> isVisible >> isExplored;

            Hex hex(q, r);
            hex.IsVisible = isVisible;
            hex.IsExplored = isExplored;

            bool HaveUnit;
            in >> HaveUnit;

            if(HaveUnit)
            {
                QString QUnitType;
                qint32 UnitLevel;
                double UnitHP;
                in >> QUnitType >> UnitLevel >> UnitHP;
                std::string UnitType = QUnitType.toStdString();

                Unit* NewUnit = UnitFabric_.Create(UnitType, UnitLevel, UnitHP);
                if(NewUnit)
                    hex.SetUnit(NewUnit);
            }

            column.push_back(hex);
        }
        MapGrid.push_back(std::move(column));
    }

    // 🧍 Завантаження позиції героя (q, r)
    qint32 heroQ, heroR;
    in >> heroQ >> heroR;
    heroPos = QPoint(heroQ, heroR);
    UpdateVisibility(heroPos);

    file.close();
}

void HexMap::Clear()
{
    for(auto& Col : MapGrid)
    {
        for(Hex& Hex_ : Col)
        {
            Hex_.ClearUnit();
        }
    }
    MapGrid.clear();
    UnitFabric_.ClearAll();
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

