#include "Map.h"
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QString>
#include <QDebug>
#include "RandomGenerator.h"

int HexMap::GetRadius() const { return Radius; }
const std::vector<std::vector<Hex>>& HexMap::GetMap() const { return MapGrid; }


HexMap::HexMap(int radius) : Radius(radius), EnemyCounter(0)
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
    std::vector<QPoint> CenterNeighbors = {{1,0},{1,-1},{0,-1},{-1,0},{-1,1},{0,1}};
    std::vector<QPoint> ValidForCampfire;
    for(const auto& CN : CenterNeighbors)
    {
        if(ContainsHex(CN.x(), CN.y()))
            ValidForCampfire.push_back(CN);
    }

    QPoint GuaranteedCampfirePos = QPoint(-999, -999);
    if(!ValidForCampfire.empty())
    {
        int RandIndx = RandGenerator::RandIntInInterval(0, ValidForCampfire.size() - 1);
        GuaranteedCampfirePos = ValidForCampfire[RandIndx];

        Hex& CampfireHex = GetChangeableQPointLoc(GuaranteedCampfirePos);
        if(!CampfireHex.HaveUnit())
        {
            Unit* Campfire = UnitFabric_.Create("Campfire", 0, 3, 3);
            if(Campfire)
            {
                CampfireHex.SetUnit(Campfire);
            }
        }
    }

    const double UnitChance = 0.1;
    const double EnemyChance = 0.5;
    const double FriendChance = 0.2;
    const double StructBreakChance = 0.15;
    const double StructUnbreakChance = 0.15;
    const double CampfireChance = 0.02;

    for(auto& Col : MapGrid)
    {
        for(Hex& Hex_ : Col)
        {
            QPoint CurrHexPos(Hex_.GetQR().first, Hex_.GetQR().second);
            if(Hex_.GetQR().first == 0 && Hex_.GetQR().second == 0)
                continue;
            if(CurrHexPos == GuaranteedCampfirePos)
                continue;

            if(RandGenerator::RandDoubleInInterval(0.0, 1.0) < CampfireChance)
            {
                Unit* Campfire = UnitFabric_.Create("Campfire", 0, 3, 3);
                if(Campfire)
                {
                    Hex_.SetUnit(Campfire);
                    continue;
                }
            }
            else if(RandGenerator::RandDoubleInInterval(0.0, 1.0) < UnitChance)
            {
                double UnitTypeRand = RandGenerator::RandDoubleInInterval(0.0, 1.0);
                Unit* NewUnit = nullptr;
                std::string UnitName;

                if(UnitTypeRand < EnemyChance)
                {

                    const double BarbarianChance = 0.4;
                    const double WarriorChance = 0.4;
                    const double WizardChance = 0.2;

                    double EnemyTypeRand = RandGenerator::RandDoubleInInterval(0.0, 1.0);

                    if(EnemyTypeRand < BarbarianChance)
                    {
                        UnitName = "Barbarian";
                        NewUnit = UnitFabric_.Create(UnitName, 1, 200, 50);
                    }
                    else if(EnemyTypeRand < BarbarianChance + WarriorChance)
                    {
                        UnitName = "Warrior";
                        NewUnit = UnitFabric_.Create(UnitName, 1, 250, 100);
                    }
                    else
                    {
                        UnitName = "Wizard";
                        NewUnit = UnitFabric_.Create(UnitName, 1, 150, 200);
                    }
                    if (NewUnit) {
                        EnemyCounter++;
                    }
                }
                else if(UnitTypeRand < EnemyChance + FriendChance)
                {
                    UnitName = "Friend";
                    NewUnit = UnitFabric_.Create(UnitName, 1, 50, 0);
                }
                else if(UnitTypeRand < EnemyChance + FriendChance + StructBreakChance)
                {
                    UnitName = "StructBreak";
                    NewUnit = UnitFabric_.Create(UnitName, 0, 30, 0);
                }
                else
                {
                    UnitName = "StructUnBreak";
                    NewUnit = UnitFabric_.Create(UnitName, 0, 0, 0);
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

void HexMap::SaveToFile(const QString& filePath, const QPoint& heroPos, double HeroHP,double HeroMP, double HeroLVL) const
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
                    << static_cast<double>(Unit_->GetHP())
                    << static_cast<double>(Unit_->GetMana());
            }
            else
                out << static_cast<bool>(false);
        }
    }

    // Записуємо позицію героя
    out << static_cast<qint32>(heroPos.x());
    out << static_cast<qint32>(heroPos.y());
    out << static_cast<double>(HeroHP);
    out << static_cast<double>(HeroMP);
    out << static_cast<double>(HeroLVL);
    file.close();
}
bool HexMap::LoadFromFile(const QString& filePath, QPoint& heroPos, double& HeroHP,double& HeroMP, double& HeroLVL)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QDataStream in(&file);
    qint32 cols, radius, loadedEnemyCounter;
    in >> cols >> radius>> loadedEnemyCounter;

    if(cols < 0 || radius < 0)
    {
        file.close();
        return false;
    }

    Clear();
    this->Radius = radius;
    this->EnemyCounter = loadedEnemyCounter;
    for (int i = 0; i < cols; ++i)
    {
        qint32 rows;
        in >> rows;
        if(rows < 0)
        {
            file.close();
            Clear();
            return false;
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
                double UnitMana;
                in >> QUnitType >> UnitLevel >> UnitHP >> UnitMana;
                std::string UnitType = QUnitType.toStdString();

                Unit* NewUnit = UnitFabric_.Create(UnitType, UnitLevel, UnitHP, UnitMana);
                if(NewUnit)
                    hex.SetUnit(NewUnit);
            }

            column.push_back(hex);
        }
        MapGrid.push_back(std::move(column));
    }
    qint32 heroQ, heroR;
    in >> heroQ >> heroR;
    heroPos = QPoint(heroQ, heroR);
    in >> HeroHP;
    in >> HeroMP;
    in >> HeroLVL;
    UpdateVisibility(heroPos);

    file.close();
    return true;
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
    EnemyCounter = 0;
}

void HexMap:: ClearUnitAt(const QPoint& position){
    if (ContainsHex(position.x(), position.y()))
    {
        Hex& hexToModify = GetChangeableQPointLoc(position);
        hexToModify.ClearUnit();
    }
    else
    {


        qDebug() << "HexMap::ClearUnitAt: Attempted to clear unit at invalid position" << position;

    }

}



int HexMap::GetEnemyCount() const
{
    return EnemyCounter;
}

void HexMap::DecrementEnemyCount()
{
    if (EnemyCounter > 0)
    {
        EnemyCounter--;
    }
    qDebug() << "EnemyCounter decremented. Current count: " << EnemyCounter;
}
