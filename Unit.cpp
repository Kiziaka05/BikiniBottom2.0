#include "Unit.h"


const double HEALTH_EPSILON = 1e-9;
Unit::Unit(double level1, double hp1, bool isnpc1, bool isenemy1, bool isstruct1, bool isbreakable1, double mana1)
{
    Level = level1;
    Hp = hp1;
    IsNPC = isnpc1;
    IsEnemy = isenemy1;
    IsStruct = isstruct1;
    IsBreakable = isbreakable1;
    Mana = mana1;
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
    double initialCalculatedHp = (1.0 + static_cast<double>(Level) / 10.0) * BaseHp;
    double initialCalculatedMana = (1.0 + static_cast<double>(Level) / 10.0) * BaseMana;


    SetInitialHp(initialCalculatedHp);
    SetInitialMana(initialCalculatedMana);

}

Enemy::Enemy()
    : Unit(0, // Level
           (1 + Level / 10.0) * BaseHp, // HP
           true, true, false, false,  // IsNPC, IsEnemy, IsStruct, IsBreakable
           (1 + Level / 10.0) * BaseMana) // Mana
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

CampfireUnit::CampfireUnit()
    : Unit(0, 4, 0, 0, 1, 1, 0)
{
    this->ai = new Campfire();
    this->IsStruct = true;
    this->IsBreakable = true;
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

CampfireUnit::~CampfireUnit()
{

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

std::string CampfireUnit::Type()
{
    return "Unit is Campfire";
}


void MainHero::MoveTo(QPoint& NewPos)
{
    Position = NewPos;
}

double Unit::GetHP()
{
    return Hp;
}

double Unit::GetLevel()
{
    return Level;
}

double Unit::GetMana()
{
    return Mana;
}

double Unit::GetBaseMana() const
{
    return BaseMana;
}
double Unit::GetBaseHP() const
{
    return BaseHp;
}
double Unit::SetHp(double newHp)
{
    this->Hp = newHp;

    if (this->Hp < HEALTH_EPSILON) {
        this->Hp = 0;
    }
    else if(this->Hp > this->MaxHp)
    {
        this->Hp = this->MaxHp;
    }
    return this->Hp;
}

double Unit::SetMana(double newMana)
{
    this->Mana = newMana;

    if (this->Mana < 0) {
        this->Mana = 0;
    }
    else if(this->Mana > this->MaxMana)
    {
        this->Mana = this->MaxMana;
    }
    return this->Mana;
}

void Unit::SetInitialHp(double Hp1)
{
    Hp = Hp1;
    MaxHp = Hp1;
}

void Unit::SetInitialMana(double Mana1)
{
    Mana = Mana1;
    MaxMana = Mana1;
}

double Unit::GetMaxHp() const { return (1 + Level / 10.0) * MaxHp; }
double Unit::GetMaxMana() const { return (1 + Level / 10.0) * MaxMana; }



