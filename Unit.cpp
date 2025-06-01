#include "Unit.h"
#include <algorithm> // Для std::min
#include <QDebug>    // Для qDebug()

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
    MaxHp = BaseHp;   // ДОДАНО: Ініціалізація MaxHp базовим значенням
    MaxMana = BaseMana; // ДОДАНО: Ініціалізація MaxMana базовим значенням
}

Unit::Unit()
{
    // Конструктор за замовчуванням
    Level = 0;
    Hp = 0;
    IsNPC = false;
    IsEnemy = false;
    IsStruct = false;
    IsBreakable = false;
    Mana = 0;
    MaxHp = BaseHp;   // ДОДАНО: Ініціалізація MaxHp базовим значенням
    MaxMana = BaseMana; // ДОДАНО: Ініціалізація MaxMana базовим значенням
}

Unit::~Unit() {}


// ОНОВЛЕНО: Конструктор MainHero
MainHero::MainHero(QPoint Pos)
    : Unit(1,  // Level
           0, // HP (буде встановлено до MaxHp)
           false, false, false, false, // IsNPC, IsEnemy, IsStruct, IsBreakable
           0), // Mana (буде встановлено до MaxMana)
    Position(Pos)
{
    ai = new MainCharacter();
    // Встановлюємо поточні HP та Mana до їх максимальних значень для початкового рівня
    this->Hp = GetMaxHp();
    this->Mana = GetMaxMana();
    // SetInitialHp та SetInitialMana більше не потрібні тут
}

// ОНОВЛЕНО: Конструктор Enemy
Enemy::Enemy()
    : Unit(0, 0, true, true, false, false, 0) // Ініціалізуємо Unit з 0 HP/Mana, Fabric їх встановить
{
    ai = new Aggresive();
}

// ОНОВЛЕНО: Конструктор Barbarian
Barbarian::Barbarian()
    : Enemy()   // Викликаємо конструктор Enemy, який створить ai = new Aggresive()
    , Confused() // Викликаємо конструктор Confused
{
    // Не потрібно тут знову ai = new Aggresive();
}

// ОНОВЛЕНО: Конструктор Wizard
Wizard::Wizard()
    : Enemy() // Викликаємо конструктор Enemy, який створить ai = new Aggresive()
    , Intelligent() // Викликаємо конструктор Intelligent
{
    // Не потрібно тут знову ai = new Aggresive();
}

// ОНОВЛЕНО: Конструктор Warrior
Warrior::Warrior()
    : Enemy() // Викликаємо конструктор Enemy, який створить ai = new Aggresive()
    , Confused() // Викликаємо конструктор Confused
{
    // Не потрібно тут знову ai = new Aggresive();
}


Friend::Friend()
    : Unit(-1, -1, 1, 0, 0, 0, 0) // Правильний виклик конструктора базового класу
{
    ai = new Friendly();
}

StructBreak::StructBreak()
    : Unit(-1, 90, 0, 0, 1, 1, 0) // Правильний виклик конструктора базового класу
{
    ai = NULL;
}

StructUnBreak::StructUnBreak()
    : Unit(-1, -1, 0, 0, 1, 0, 0) // Правильний виклик конструктора базового класу
{
    ai = NULL;
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

// Деструктори без ручного видалення ai, оскільки його видаляє UnitFabric або базовий клас Enemy
Enemy::~Enemy() {}
Barbarian::~Barbarian() {}
Wizard::~Wizard() {}
Warrior::~Warrior() {}
Friend::~Friend() {}
StructBreak::~StructBreak() {}
StructUnBreak::~StructUnBreak() {}
CampfireUnit::~CampfireUnit() {}


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

// ОНОВЛЕНО: SetHp з коректним обмеженням
double Unit::SetHp(double newHp)
{
    this->Hp = newHp;

    if (this->Hp < HEALTH_EPSILON) {
        this->Hp = 0;
    }
    else if(this->Hp > GetMaxHp()) // КОРИГУВАННЯ: Використовуємо GetMaxHp()
    {
        this->Hp = GetMaxHp(); // КОРИГУВАННЯ: Використовуємо GetMaxHp()
    }
    return this->Hp;
}

// ОНОВЛЕНО: SetMana з коректним обмеженням
double Unit::SetMana(double newMana)
{
    this->Mana = newMana;

    if (this->Mana < 0) {
        this->Mana = 0;
    }
    else if(this->Mana > GetMaxMana()) // КОРИГУВАННЯ: Використовуємо GetMaxMana()
    {
        this->Mana = GetMaxMana(); // КОРИГУВАННЯ: Використовуємо GetMaxMana()
    }
    return this->Mana;
}

// ОНОВЛЕНО: SetLevel, як було погоджено
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

// SetInitialHp та SetInitialMana тепер просто встановлюють поточні значення
void Unit::SetInitialHp(double Hp1)
{
    Hp = Hp1;
}

void Unit::SetInitialMana(double Mana1)
{
    Mana = Mana1;
}

// ОНОВЛЕНО: GetMaxHp використовує BaseHp для розрахунку
double Unit::GetMaxHp() const { return (1 + Level / 10.0) * BaseHp; }
// ОНОВЛЕНО: GetMaxMana використовує BaseMana для розрахунку
double Unit::GetMaxMana() const { return (1 + Level / 10.0) * BaseMana; }


// Метод LevelUp для MainHero
void MainHero::LevelUp()
{
    SetLevel(this->Level + 1); // Використовуємо SetLevel для підвищення рівня

    // Повністю відновлюємо HP та Mana при підвищенні рівня
    this->Hp = GetMaxHp();
    this->Mana = GetMaxMana();

    qDebug() << "Герой підвищив рівень! Новий рівень: " << this->Level
             << ", HP: " << this->Hp << "/" << GetMaxHp()
             << ", Mana: " << this->Mana << "/" << GetMaxMana();
}
