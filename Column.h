#ifndef COLUMN_H
#define COLUMN_H

#include "Cell.h"
#include <vector>

using namespace std;
class Column {
private:
    vector<Cell*> cellen;
public:
    //constructor, maakt x aantal cellen
    Column(int x);
    Cell* getCell(int x);
    std::vector<Cell*>::iterator begin();
    std::vector<Cell*>::iterator end();
};

#endif // COLUMN_H
