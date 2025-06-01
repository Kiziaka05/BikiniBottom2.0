#ifndef MAP_H_DEFINED
#define MAP_H_DEFINED

#include "Cell.h"
#include "UnitFabric.h"
#include <iostream>
#include <vector>

class HexMap
{
private:
    int Radius;
    std::vector<std::vector<Hex>> MapGrid;
    UnitFabric UnitFabric_;
    int GetHexDistance(int q, int r) const;
    Hex& GetChangeableLocation(int q, int r);
    Hex& GetChangeableQPointLoc(const QPoint& OHex);
    void GenerateUnits();

public:
    HexMap(int radius);
    int GetRadius() const;
    const Hex& GetLocation(int q, int r) const;
    const Hex& GetQPointLoc(const QPoint& OHex) const;
    const std::vector<std::vector<Hex>>& GetMap() const;
    bool ContainsHex(int q, int r) const;
    void UpdateVisibility(const QPoint& HeroPos);
    void SaveToFile(const QString& filePath, const QPoint& heroPos, double HeroHP,double HeroMP, double HeroLVL) const;
    bool LoadFromFile(const QString& filePath, QPoint& heroPos, double& HeroHP,double& HeroMP, double& HeroLVL);
    void Clear();
    void ClearUnitAt(const QPoint& position);
};

#endif //MAP_H_DEFINED
