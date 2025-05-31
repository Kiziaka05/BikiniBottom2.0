#include "AI.h"

using namespace std;

//Заклинання

const vector<Spell> &AI::GetSpells() const
{
    return Spells;
}

Spell::Spell(string name, double manacost, double damage)
{
    this->name = name;
    this->manacost = manacost;
    this->damage = damage;
}

void AI::SpellList() const
{
    int n = GetSpells().size();
    for (int i = 0; i < n; i++) {
        cout << endl
             << i << " Spell name: " << Spells[i].name << " costs " << Spells[i].manacost
             << " mana and deals " << Spells[i].damage << endl;
    }
}
//

//Для AI
AI::AI()
{
    // Ініціалізуємо заклинання прямо в конструкторі
    Spells = {Spell("Fireball", 10.0, 30.0),
              Spell("Ice Blast", 15.0, 53.3),
              Spell("Lightning Bolt", 2.0, 710.1)};
}

double AI::Spellcounter(double BaseMana)
{
    double maxDamage = 0;

    for (const auto &Spell : GetSpells()) {
        // Перевіряємо, чи заклинання можна використати за обмеженням мани
        if (Spell.manacost <= BaseMana) {
            maxDamage = max(maxDamage, Spell.damage); // Оновлюємо максимальний урон
        }
    }
    return maxDamage;
}
//

//Методи Intelligent
Intelligent::Intelligent()
    : AI()
{
    this->UpgradeSpells();
}

void Intelligent::UpgradeSpells()
{
     this->UpgradedSpells = this->Spells;
    for (auto &Spell : UpgradedSpells) {
        Spell.damage *= 1.05;
        Spell.manacost *= 0.95;
    }
}

void Intelligent::SpellList() const
{ // Перевизначений метод
    int n = UpgradedSpells.size();
    for (int i = 0; i < n; i++) {
        cout << endl
             << i << " Spell name: " << UpgradedSpells[i].name << " costs "
             << UpgradedSpells[i].manacost << " mana and deals " << UpgradedSpells[i].damage
             << endl;
    }
}

const vector<Spell> &Intelligent::GetSpells() const
{
    return UpgradedSpells;
}
//

//Методи Confused
double Confused::UseRandomSpell(double BaseMana)
{
    double Damage = 0.0;
    vector<Spell> S = GetSpells();

    vector<Spell> availableSpells;
    for (const auto &spell : S) {
        if (spell.manacost <= BaseMana) {
            availableSpells.push_back(spell);
        }
    }

    if (!availableSpells.empty()) {
        // Вибираємо випадкове заклинання
        int randomIndex = RandGenerator::RandIntInInterval(0, availableSpells.size() - 1);
        Damage = availableSpells[randomIndex].damage;
    }

    return Damage;
}
//

//Методи MainCharacter
double MainCharacter::UseSpell()
{
    cout << "Use 1 spell in your move:";
    SpellList();
    int c;
    double AttackDamage;
    cin >> c;
    switch (c) {
    case '0':
        AttackDamage = Spells[c].damage;
        break;
    case '1':
        AttackDamage = Spells[c].damage;
        break;
    case '2':
        AttackDamage = Spells[c].damage;
        break;
    }
    return AttackDamage;
}
//

//Методи Friendly
void Friendly::Speak()
{
    cout << "Greetings, traveler! I am glad to see you in our valley, but be careful, as there is "
            "much danger here.";
}
//

//Методи, які не потребують реалізації в певних класах. Для того, щоб створювати на пряму
double Aggresive::UseSpell()
{
    return 0.0;
}
double Friendly::UseSpell()
{
    return 0.0;
}
double Intelligent::UseSpell()
{
    return 0.0;
}
//

//Деструктори
MainCharacter::~MainCharacter() {}
Confused::~Confused() {}
Aggresive::~Aggresive() {}
Friendly::~Friendly() {}
Fearful::~Fearful() {}
Intelligent::~Intelligent() {}
//Campfire::~Campfire(){}
Shop::~Shop() {}
AI::~AI() {}
//
