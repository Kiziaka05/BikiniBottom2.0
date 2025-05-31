#include "Unit.h"

Unit::Unit(double level1, double hp1, bool isnpc1, bool isenemy1, bool isstruct1, bool isbreakable1, double mana1)
{
    Level = level1;
    Hp = hp1;
    IsNPC = isnpc1;
    IsEnemy = isenemy1;
    IsStruct = isstruct1;
    IsBreakable = isbreakable1;
    Mana=mana1;
}
Unit::Unit() {}
Unit::~Unit() {}

MainHero::MainHero(QPoint Pos): Unit(1,  // Level
           0, // HP
           false, false, false, false, // IsNPC, IsEnemy, IsStruct, IsBreakable
           0), //
    Position(Pos)
{
    ai = new MainCharacter();
    this->Hp = (1 + Level / 10.0) * BaseHp;
    this->Mana = (1 + Level / 10.0) * BaseMana;

}

Enemy::Enemy()
    : Unit(0, // Level
           (1 + 0.0 / 10.0) * BaseHp, // HP
           true, true, false, false,  // IsNPC, IsEnemy, IsStruct, IsBreakable
           (1 + 0.0 / 10.0) * BaseMana) // Mana
{
    ai = new Aggresive();

}

Barbarian::Barbarian()
{
    ai = new Aggresive();
    Unit(1, (1 + Level / 10) * BaseHp, 1, 1, 0, 0, ((1 + Level / 10) * BaseMana));
}

Wizard::Wizard()
{
    ai = new Aggresive();
    Unit(1, (1 + Level / 10) * BaseHp, 1, 1, 0, 0, ((1 + Level / 10) * BaseMana));
}

Friend::Friend()
{
    ai = new Friendly();
    Unit(-1, -1, 1, 0, 0, 0, 0);
}

StructBreak::StructBreak()
{
    ai = NULL;
    Unit(-1, 90, 0, 0, 1, 1, 0);
}

StructUnBreak::StructUnBreak()
{
    ai = NULL;
    Unit(-1, -1, 0, 0, 1, 0, 0);
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

QPoint& MainHero::GetPosition()
{
    return Position;
}

void MainHero::MoveTo(QPoint& NewPos)
{
    Position = NewPos;
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
    return Mana;
}
