#include "Unit.h"
#include <cstdlib>
#include <iostream>
#include <string>
Unit::Unit(int level1, double hp1, bool isnpc1, bool isenemy1, bool isstruct1, bool isbreakable1)
{
    Level = level1;
    Hp = hp1;
    IsNPC = isnpc1;
    IsEnemy = isenemy1;
    IsStruct = isstruct1;
    IsBreakable = isbreakable1;
}
Unit::Unit() {}
Unit::~Unit() {}

MainHero::MainHero()
{
    Unit(0, (1 + Level / 10) * BaseHp, 0, 0, 0, 0);
    ai = new MainCharacter();
    x = 0;
    y = 0;
}

Enemy::Enemy()
{
    ai = new Aggresive();

    Unit(0, (1 + Level / 10) * BaseHp, 1, 1, 0, 0);
}

Barbarian::Barbarian()
{
    ai = new Aggresive();
    Unit(0, (1 + Level / 10) * BaseHp, 1, 1, 0, 0);
}

Wizard::Wizard()
{
    ai = new Aggresive();
    Unit(0, (1 + Level / 10) * BaseHp, 1, 1, 0, 0);
}

Friend::Friend()
{
    ai = new Friendly();
    Unit(-1, -1, 1, 0, 0, 0);
}

StructBreak::StructBreak()
{
    ai = NULL;
    Unit(-1, 90, 0, 0, 1, 1);
}

StructUnBreak::StructUnBreak()
{
    ai = NULL;
    Unit(-1, -1, 0, 0, 1, 0);
}

MainHero::~MainHero()
{
    if (ai != NULL) {
        delete ai;
    }
}

Enemy::~Enemy()
{
    if (ai != NULL) {
        delete ai;
    }
}

Barbarian::~Barbarian()
{
    if (ai != NULL) {
        delete ai;
    }
}

Wizard::~Wizard()
{
    if (ai != NULL) {
        delete ai;
    }
}

Friend::~Friend()
{
    if (ai != NULL) {
        delete ai;
    }
}

StructBreak::~StructBreak()
{
    if (ai != NULL) {
        delete ai;
    }
}
StructUnBreak::~StructUnBreak()
{
    if (ai != NULL) {
        delete ai;
    }
}

std::string Unit::Type()
{
    return "Unit is base unit";
}

std::string MainHero::Type()
{
    return "Unit is MainHero";
}

std::string Enemy::Type()
{
    return "Unit is Enemy";
}

std::string Friend::Type()
{
    return "Unit is Friend";
}

std::string StructUnBreak::Type()
{
    return "Unit is StructUnBreak";
}

std::string StructBreak::Type()
{
    return "Unit is StructBreak";
}

std::pair<int, int> MainHero::GetLocation()
{
    return std::pair<int, int>(x, y);
}

void MainHero::SetLocation(int XLoc, int YLoc)
{
    x = XLoc;
    y = YLoc;
}

double Unit::GetHP()
{
    return Hp;
}

int Unit::GetLevel()
{
    return Level;
}

double Unit::GetMana()
{
    return BaseMana;
}
