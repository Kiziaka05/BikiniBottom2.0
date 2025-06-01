#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

namespace RandGenerator
{
    extern std::mt19937 gen;
    int RandIntInInterval(int left, int right);
    double RandDoubleInInterval(double left, double right);
}

#endif // RANDOMGENERATOR_H
