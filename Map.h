#ifndef MAP_H_DEFINED
#define MAP_H_DEFINED

#include "Cell.h"
#include <iostream>
#include <vector>

class Map
{
private:
    int Size;
    std::vector<std::vector<Cell *>> MapArray;

    void GenerateMap();
    void RemoveMap();

public:
    Map();
    ~Map();
    friend std::ostream &operator<<(std::ostream &Stream, const Map &MapToPrint);
    int GetSize();
    Cell *GetCell(int XLocation1, int YLocation1);
};

#endif //MAP_H_DEFINED
