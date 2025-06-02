#include "UnitFabric.h"
#include "AI.h"
#include <iostream>

UnitFabric::UnitFabric() {}

UnitFabric::~UnitFabric()
{
    Units.clear();
}

Unit *UnitFabric::Create(string Class, double level, double hp, double mana)
{
    unique_ptr<Unit> newUnit = nullptr;
    double finalHp = hp;
    double finalMana = mana;
    const double FORMULA_BASE_HP = 200.0;
    const double FORMULA_BASE_MANA = 100.0;
    if (Class == "MainHero") {

    } else if (Class == "Enemy") {
        newUnit = std::make_unique<Enemy>();
    }else if (Class == "Wizard") {
        newUnit = std::make_unique<Wizard>();
        finalHp = (0.8 + level / 5.0) * FORMULA_BASE_HP;
        finalMana = (1.3 + level / 0.8) * FORMULA_BASE_MANA;

    }else if (Class == "Barbarian") {
        newUnit = std::make_unique<Barbarian>();
        finalHp = (5.0 + level / 4.5) * FORMULA_BASE_HP;
        finalMana = (1.2 + level / 6.0) * FORMULA_BASE_MANA;


    }else if (Class == "Warrior") {
        newUnit = std::make_unique<Warrior>();
        finalHp = (2.5 + level / 4) * FORMULA_BASE_HP;
        finalMana = (1.3 + level / 5.0) * FORMULA_BASE_MANA;

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
    newUnit->SetInitialHp(finalHp);
    newUnit->SetInitialMana(finalMana);

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
