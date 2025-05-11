#ifndef UNIT_H_INCLUDE

#define UNIT_H_INCLUDE
#include "AI.h"
#include <random>
#include <string>
#include <utility>
#include <QPoint>

class Unit
{
protected:
    double Hp;
    int BaseHp = 200;
    double BaseMana = 100;
    int Level;

public:
    Unit(int level1, double hp1, bool isnpc1, bool isenemy1, bool isstruct1, bool isbreakable1);
    Unit();
    virtual ~Unit();
    bool IsNPC;
    bool IsEnemy;
    bool IsStruct;
    bool IsBreakable;
    virtual std::string Type();
    AI *ai;
    friend class UnitFabric;
    double GetHP();
    int GetLevel();
    double GetMana();
};

class MainHero : public Unit
{
public:
    QPoint Position;
    MainHero(QPoint Pos);
    virtual ~MainHero();
    virtual std::string Type();
    QPoint& GetPosition();
    void MoveTo(QPoint& NewPos);
};

class Enemy : public Unit
{
public:
    Enemy();

    virtual ~Enemy();
    virtual std::string Type();
};

class Friend : public Unit
{
public:
    Friend();
    virtual ~Friend();
    virtual std::string Type();
};

class StructUnBreak : public Unit
{
public:
    StructUnBreak();
    virtual ~StructUnBreak();
    virtual std::string Type();
};

class StructBreak : public Unit
{
public:
    StructBreak();
    virtual ~StructBreak();
    virtual std::string Type();
};

class Wizard : public Enemy, public Intelligent
{
public:
    Wizard();
    virtual ~Wizard();
};

class Barbarian : public Enemy, public Aggresive
{
public:
    Barbarian();
    virtual ~Barbarian();
};

#endif // UNIT_H_INCLUDE
