#include "Unit.h"
#include <qdebug.h>
#include <algorithm>
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
    MaxHp = BaseHp;
    MaxMana = BaseMana;
}
Unit::Unit()
{
    Level = 0;
    Hp = 0;
    IsNPC = false;
    IsEnemy = false;
    IsStruct = false;
    IsBreakable = false;
    Mana = 0;
    MaxHp = BaseHp;
    MaxMana = BaseMana;
}
Unit::~Unit() {}

MainHero::MainHero(QPoint Pos): Unit(1,0,false,false,false,false,0),
    Position(Pos)
{
    ai = new MainCharacter();
    this->Hp = GetMaxHp();
    this->Mana = GetMaxMana();
}

Enemy::Enemy()
    : Unit(0,0,true,true,false,false,0)
{
    ai = new Aggresive();

}

Barbarian::Barbarian()
    : Enemy()
    , Confused()
{

}

Wizard::Wizard()
    : Enemy()
    , Intelligent()
{

}

Warrior::Warrior()
    : Enemy()
    , Confused()
{

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
    //if (ai != NULL) {
    //    delete ai;
    //}
}

Barbarian::~Barbarian()
{
    //if (ai != NULL) {
    //    delete ai;
    //}
}

Wizard::~Wizard()
{
    //if (ai != NULL) {
     //   delete ai;
   // }
}

Warrior::~Warrior()
{
    //if (ai != NULL) {
    //    delete ai;
    //}
}

Friend::~Friend()
{
    //if (ai != NULL) {
     //   delete ai;
    //}
}

StructBreak::~StructBreak()
{
    //if (ai != NULL) {
     //   delete ai;
    //}
}
StructUnBreak::~StructUnBreak()
{
    //if (ai != NULL) {
    //    delete ai;
    //}
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
    else if(this->Hp > GetMaxHp())
    {
        this->Hp = this->GetMaxHp();
    }
    return this->Hp;
}

double Unit::SetMana(double newMana)
{
    this->Mana = newMana;

    if (this->Mana < 0) {
        this->Mana = 0;
    }
    else if(this->Mana > this->GetMaxMana())
    {
        this->Mana = this->GetMaxMana();
    }
    return this->Mana;
}

double Unit::SetLevel(double newLVL)
{
    this->Level = newLVL;
    if (this->Level < 1) {
        this->Level = 1;
    }
    this->Hp = std::min(this->Hp, GetMaxHp());
    this->Mana = std::min(this->Mana, GetMaxMana());
    return this->Level;
}

void Unit::SetInitialHp(double Hp1)
{
    Hp = Hp1;
}

void Unit::SetInitialMana(double Mana1)
{
    Mana = Mana1;
}

double Unit::GetMaxHp() const { return (1 + Level / 10.0) * BaseHp; }
double Unit::GetMaxMana() const { return (1 + Level / 10.0) * BaseMana; }


void MainHero::LevelUp()
{
    SetLevel(this->Level+1);
    this->Hp = GetMaxHp();
    this->Mana = GetMaxMana();
    qDebug()<<"Герой підвищив рівень, новий рівень: " << this->Level
             <<", HP: " << this->Hp <<"/" << GetMaxHp()
             <<", MP: " << this->Mana <<"/" << GetMaxMana();
}
