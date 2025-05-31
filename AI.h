#ifndef AI_H_INCLUDE
#define AI_H_INCLUDE

#include <iostream>
#include <vector>
#include "RandomGenerator.h"
using namespace std;
class Spell;

class AI
{
public:
    AI();
    virtual ~AI();
    void MakeDecision();

    int TurnOver; //у кого більше, той і перший атакує
    virtual const Spell* ChooseBestSpell(double currentMana) const;
    virtual void SpellList() const;
    void Run();
    virtual const vector<Spell> &GetSpells() const;

protected:
    vector<Spell> Spells;
};

class Aggresive : public AI
{
public:


    int TurnOver = 100;
    virtual ~Aggresive();
};

class Confused : public AI
{
public:
    int TurnOver = 50;
    const Spell* ChooseBestSpell(double currentMana) const override;
    virtual ~Confused();
};



class Intelligent : public AI
{
private:
    vector<Spell> UpgradedSpells;

public:

    void SpellList() const override;
    Intelligent();
    void UpgradeSpells();
    const vector<Spell> &GetSpells() const override;
    virtual ~Intelligent();
};



class Fearful : public AI
{
public:

    int TurnOver = 20;
    virtual ~Fearful();
};



class MainCharacter : public AI
{
public:
    MainCharacter();
    int TurnOver = 50;
    virtual ~MainCharacter();
protected:
    vector<Spell> HeroSpells;
};



class Friendly : public AI
{
public:

    void Speak();
    virtual ~Friendly();
};

/*class Campfire: public AI{
    public:
  //  double Heal();
 //   virtual ~Campfire();
};*/



class Shop : public Friendly
{
public:
    //  void ShopInteraction();
    virtual ~Shop();
};

class Spell
{
public:
    Spell(string name, double manacost, double damage);
    string name;
    double manacost;
    double damage;
};


#endif
