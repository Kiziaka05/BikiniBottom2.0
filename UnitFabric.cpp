#include "UnitFabric.h"
#include <iostream>

UnitFabric::UnitFabric() {}

UnitFabric::~UnitFabric()
{
    Units.clear();
}

Unit *UnitFabric::Create(string Class, int level, double hp)
{
    unique_ptr<Unit> Unit = NULL;
    if (Class == "MainHero") {
        //Unit = make_unique<MainHero>();
    } else if (Class == "Enemy") {
        Unit = make_unique<Enemy>();
    } else if (Class == "Friend") {
        Unit = make_unique<Friend>();
    } else if (Class == "StructBreak") {
        Unit = make_unique<StructBreak>();
    } else if (Class == "StructUnBreak") {
        Unit = make_unique<StructUnBreak>();
    } else {
        cerr << "Unknown class: " << Class << endl;
        return NULL;
    }

    Unit->Level = level;
    Unit->Hp = hp;

    Units.push_back(move(Unit));
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
