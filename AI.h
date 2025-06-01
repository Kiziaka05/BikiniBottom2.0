#ifndef AI_H_INCLUDE
#define AI_H_INCLUDE

#include <iostream>
#include <vector>
#include "RandomGenerator.h"
using namespace std;
class Spell;
class Unit;
class AI
{
public:
    AI();
    virtual ~AI();

    int TurnOver; //у кого більше, той і перший атакує
    virtual const Spell* ChooseBestSpell(double currentMana) const;
    virtual void SpellList() const;
    virtual const vector<Spell> &GetSpells() const;

protected:
    vector<Spell> Spells;
};




//методи Aggresive
class Aggresive : public AI
{
public:
    int TurnOver = 100;
    virtual ~Aggresive();
};



//Методи Confused
class Confused : public AI
{
public:
    int TurnOver = 1000;
    const Spell* ChooseBestSpell(double currentMana) const override;
    virtual ~Confused();
};


//Методи Intelligent
class Intelligent : public AI
{
private:
    vector<Spell> UpgradedSpells;

public:
    int TurnOver = 75;
    void SpellList() const override;
    Intelligent();
    void UpgradeSpells();
    const vector<Spell> &GetSpells() const override;
    virtual ~Intelligent();
};



//Методи MainCharacter
class MainCharacter : public AI
{
public:
    MainCharacter();
    int TurnOver = 50;

    void updateSpellStats(int playerLevel);
    const vector<Spell>& GetSpells() const override;
    virtual ~MainCharacter();
protected:
    vector<Spell> HeroSpells;
private:
    struct BaseSpellDefinition {
        std::string name;
        double baseManacost;
        double baseDamage;

        double percDamageBonusPerLevel;
        double percManacostChangePerLevel;
    };
    std::vector<BaseSpellDefinition> heroBaseSpellDefinitions;
};



//Методи Friendly
class Friendly : public AI
{
public:

    std::string getGreeting() const;
    virtual ~Friendly();
};


//Методи Campfire
class Campfire: public AI{
    public:
    Campfire();
    void Heal(Unit* target);

   virtual ~Campfire();
};


//
class Spell
{
public:
    Spell(string name, double manacost, double damage);
    string name;
    double manacost;
    double damage;
};


#endif
