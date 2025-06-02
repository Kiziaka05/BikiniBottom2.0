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
//

//Для AI
AI::AI()
{
    // Ініціалізуємо заклинання прямо в конструкторі
    Spells = {Spell("Fireball", 10.0, 30.0),
              Spell("Ice Blast", 15.0, 48.3),
              Spell("Quick Jolt", 4.0, 14.0),
              Spell("Frost Shards", 14.0, 50.0),
              Spell("Lightning Bolt", 40.0, 70.1),
              Spell("Spark", 3.0, 8.0),
              Spell("Thunder Strike", 42.0, 85.0),
              Spell("Stone Shard", 5.0, 16.0),
              Spell("Shockwave", 18.0, 58.0),
              Spell("Arcane Missile", 8.0, 25.0)
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
        Spell.damage *= 1.40;
        Spell.manacost *= 0.70;
    }
}


const vector<Spell> &Intelligent::GetSpells() const
{
    return UpgradedSpells;
}
//



//Методи MainCharacter
MainCharacter::MainCharacter() {
heroBaseSpellDefinitions = {
    // Назва Баз.Варт.Баз.Шкода  %Шкоди  %Вартості
    {"Fireball",       10.0,     30.0,      0.08,        -0.03},
    {"Ice Blast",      15.0,     48.3,      0.10,        -0.04},
    {"Quick Jolt",     4.0,      14.0,      0.07,        -0.02},
    {"Frost Shards",   14.0,     50.0,      0.10,        -0.04},
    {"Lightning Bolt", 40.0,     70.1,      0.12,        -0.05},
    {"Spark",          3.0,      8.0,       0.06,        -0.015},
    {"Thunder Strike", 42.0,     85.0,      0.12,        -0.05},
    {"Stone Shard",    5.0,      16.0,      0.07,        -0.02},
    {"Shockwave",      18.0,     58.0,      0.09,        -0.035},
    {"Arcane Missile", 8.0,      25.0,      0.08,        -0.025},
    {"TestImba bolt",  2.0, 100000.0,      0.0,          0.0}
};
    updateSpellStats(1);

}
void MainCharacter::updateSpellStats(int playerLevel) {
    HeroSpells.clear();

    int levelsAboveOne = (playerLevel > 1) ? (playerLevel - 1) : 0;

    for (const auto& baseDef : heroBaseSpellDefinitions) {
        double damageMultiplier = 1.0 + (baseDef.percDamageBonusPerLevel * levelsAboveOne);
        double currentDamage = baseDef.baseDamage * damageMultiplier;

        double manacostMultiplier = 1.0 + (baseDef.percManacostChangePerLevel * levelsAboveOne);
        double currentManacost = baseDef.baseManacost * manacostMultiplier;

        if (baseDef.percManacostChangePerLevel < 0) {
            double minManacostFromBase = baseDef.baseManacost * 0.30;
            if (currentManacost < minManacostFromBase) {
                currentManacost = minManacostFromBase;
            }
        }
        if (currentManacost < 1.0 && baseDef.baseManacost > 0) {
            currentManacost = 1.0;
        }
        if (baseDef.baseManacost > 0 && currentManacost <= 0) {
            currentManacost = 1.0;
        }
        if (currentDamage < 0) {
            currentDamage = 0;
        }

        HeroSpells.emplace_back(baseDef.name, currentManacost, currentDamage);
    }
}

const vector<Spell>& MainCharacter::GetSpells() const {
    return HeroSpells;
}



//Методи Friendly
std::string Friendly::getGreeting() const
{

    return "Greetings, traveler! I am glad to see you in our valley, but be careful, as there is much danger here.";
}
//


//Методи Campfire
Campfire::Campfire() : AI(){}
void Campfire::Heal(Unit* target) {
    if (target) {
        double level = target->GetLevel();
        double baseHp = target->GetBaseHP();
        double baseMana = target->GetBaseMana();


        double newHp = (1.0 + static_cast<double>(level) / 10.0) * baseHp;
        double newMana = (1.0 + static_cast<double>(level) / 10.0) * baseMana;

        target->SetHp(newHp);
        target->SetMana(newMana);

    }
}
//



//Деструктори
MainCharacter::~MainCharacter() {}
Confused::~Confused() {}
Aggresive::~Aggresive() {}
Friendly::~Friendly() {}
Intelligent::~Intelligent() {}
Campfire::~Campfire(){}
AI::~AI() {}
//
