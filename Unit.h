#ifndef UNIT_H_INCLUDE

#define UNIT_H_INCLUDE
#include "AI.h"
#include "RandomGenerator.h"
#include <string>
#include <utility>
#include <QPoint>
#include <iostream>

class Unit
{
protected:
    double Hp;
    double BaseHp = 200;
    double BaseMana = 100;
    double Level=0;
    double Mana;

public:
    Unit(double level1, double hp1, bool isnpc1, bool isenemy1, bool isstruct1, bool isbreakable1, double Mana1);
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
    virtual std::string GetSaveType() const { return "Unit"; };

    void TakeDamage(double damage_amount) {
        Hp -= damage_amount;
        if (Hp < 0) Hp = 0;
    }
    bool CanUseMana(double mana_cost) const {
        return Mana >= mana_cost;
    }
    void ConsumeMana(double mana_cost) {
        if (CanUseMana(mana_cost)) {
            Mana -= mana_cost;
        }
    }







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
    virtual std::string GetSaveType() const override { return "MainHero"; };
};

class Enemy : public Unit
{
public:
    Enemy();

    virtual ~Enemy();
    virtual std::string Type();
    virtual std::string GetSaveType() const override { return "Enemy"; };
};

class Friend : public Unit
{
public:
    Friend();
    virtual ~Friend();
    virtual std::string Type();
    virtual std::string GetSaveType() const override { return "Friend"; };
};

class StructUnBreak : public Unit
{
public:
    StructUnBreak();
    virtual ~StructUnBreak();
    virtual std::string Type();
    virtual std::string GetSaveType() const override { return "StructUnBreak"; };
};

class StructBreak : public Unit
{
public:
    StructBreak();
    virtual ~StructBreak();
    virtual std::string Type();
    virtual std::string GetSaveType() const override { return "StructBreak"; };
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
