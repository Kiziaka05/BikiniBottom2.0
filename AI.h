#ifndef AI_H_INCLUDE

#define AI_H_INCLUDE
#include <iostream>
#include <vector>
using namespace std;
class Spell;

class AI
{
public:
    AI();
    virtual ~AI();
    void MakeDecision();

    int TurnOver; //у кого більше, той і перший атакує
    double Spellcounter(double BaseMana);
    virtual void SpellList() const;
    void Run();
    virtual const vector<Spell> &GetSpells() const;

    virtual double UseSpell() = 0;

protected:
    vector<Spell> Spells;
};

class Aggresive : public AI
{
public:
    double UseSpell() override;

    int TurnOver = 100;
    virtual ~Aggresive();
};

class Confused : public AI
{
public:
    int TurnOver = 50;
    double UseRandomSpell(double BaseMana);
    virtual ~Confused();
};

class Intelligent : public AI
{
private:
    vector<Spell> UpgradedSpells;

public:
    double UseSpell() override;
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
    int TurnOver = 50;
    double UseSpell() override;
    virtual ~MainCharacter();
};

class Friendly : public AI
{
public:
    double UseSpell() override;
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

class IntelegentTestAI
{
public:
    Intelligent iii;
};

#endif
