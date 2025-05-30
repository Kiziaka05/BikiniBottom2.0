#include "RandomGenerator.h"

namespace RandGenerator
{
    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());

    int RandIntInInterval(int left, int right)
    {
        std::uniform_int_distribution<> distribution(left, right);
        return distribution(gen);
    }

    double RandDoubleInInterval(double left, double right)
    {
        std::uniform_real_distribution<> distribution(left, right);
        return distribution(gen);
    }
}
