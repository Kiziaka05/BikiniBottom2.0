#include "UnitFabric.h"
#include <iostream>

UnitFabric::UnitFabric() {}

UnitFabric::~UnitFabric()
{
    Units.clear();
}

Unit *UnitFabric::Create(string Class, double level, double hp, double mana)
{
    unique_ptr<Unit> newUnit = nullptr;

    if (Class == "MainHero") {

    } else if (Class == "Enemy") {
        newUnit = std::make_unique<Enemy>();
    } else if (Class == "Friend") {
        newUnit = std::make_unique<Friend>();
    } else if (Class == "StructBreak") {
        newUnit = std::make_unique<StructBreak>();
    } else if (Class == "StructUnBreak") {
        newUnit = std::make_unique<StructUnBreak>();
    } else if (Class == "Campfire") {
        newUnit = std::make_unique<CampfireUnit>();
    } else {
        std::cerr << "Unknown class: " << Class << std::endl;
        return nullptr;
    }

    if (!newUnit) {
        return nullptr;
    }

    newUnit->Level = level;
    newUnit->SetInitialHp(hp);
    newUnit->SetInitialMana(mana);

    Units.push_back(move(newUnit));
    return Units.back().get();
}

Unit *UnitFabric::Get(int pos)
{
    if (pos < 0 || pos >= Units.size()) {
        cerr << "Out of bounds: " << pos << endl;
        return NULL;
    }
    return Units[pos].get();
}

void UnitFabric::Remove(int pos)
{
    if (pos < 0 || pos >= Units.size()) {
        cerr << "Out of bounds: " << pos << endl;
        return;
    }
    Units.erase(Units.begin() + pos);
}

void UnitFabric::ClearAll()
{
    Units.clear();
}

int UnitFabric::HowMany()
{
    return Units.size();
}
