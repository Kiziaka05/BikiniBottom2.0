#include "AI.h"
#include "Unit.h"

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
              Spell("Lightning Bolt", 2.0, 70.1),
             };
}

const Spell* AI::ChooseBestSpell(double currentMana) const
{
    const Spell* bestSpell = nullptr;
    double maxDamage = -1.0;

    for (const Spell& spell : GetSpells()) {
        if (spell.manacost <= currentMana) {
            if (spell.damage > maxDamage) {
                maxDamage = spell.damage;
                bestSpell = &spell;
            }
        }
    }
    return bestSpell;
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
const Spell* Confused::ChooseBestSpell(double currentMana) const
{

    const std::vector<Spell>& allSpells = this->GetSpells();


    std::vector<const Spell*> availableSpellPointers;


    for (const Spell& spell : allSpells) {
        if (spell.manacost <= currentMana) {
            availableSpellPointers.push_back(&spell);
        }
    }


    if (!availableSpellPointers.empty()) {
        int randomIndex = RandGenerator::RandIntInInterval(0, availableSpellPointers.size() - 1);
        return availableSpellPointers[randomIndex];
    }

    return nullptr;
}
//

//Методи MainCharacter
MainCharacter::MainCharacter(){
    Spells = {Spell("Fireball", 10.0, 30.0),
                  Spell("Ice Blast", 15.0, 53.3),
                  Spell("Lightning Bolt", 2.0, 710.1),
                  Spell("TestImba bolt", 2.0, 100000.0)};


}


//Методи Friendly
void Friendly::Speak()
{
    cout << "Greetings, traveler! I am glad to see you in our valley, but be careful, as there is "
            "much danger here.";
}
//


//Методи Campfire
Campfire::Campfire() : AI()
{

}


void Campfire::Heal(Unit* target)
{
    if (target) {
        double level = target->GetLevel();
        double baseHp = target->GetBaseHP();
        double baseMana = target->GetBaseMana();

        double newHp = (1.0 + static_cast<double>(level) / 10.0) * baseHp;
        double newMana = (1.0 + static_cast<double>(level) / 10.0) * baseMana;


       target->SetHp(newHp);
       target->SetMana(newMana);

        std::cout << target->Type() << " rests ... HP: " << newHp << ", Mana: " << newMana << std::endl;
    }
}
//



//Деструктори
MainCharacter::~MainCharacter() {}
Confused::~Confused() {}
Aggresive::~Aggresive() {}
Friendly::~Friendly() {}
Fearful::~Fearful() {}
Intelligent::~Intelligent() {}
Campfire::~Campfire(){}
Shop::~Shop() {}
AI::~AI() {}
//
