#ifndef UNITFABRIC_H_INCLUDE
#define UNITFABRIC_H_INCLUDE
#include "Unit.h"
#include <memory>
#include <vector>
using namespace std;
class UnitFabric
{
private:
    vector<unique_ptr<Unit>> Units;

public:
    UnitFabric();
    ~UnitFabric();

    Unit *Create(string Class, double level, double hp, double mana);
    Unit *Get(int pos);
    int HowMany();
    void Remove(int pos);
    void ClearAll();
};

#endif
