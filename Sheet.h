#ifndef SHEET_H
#define SHEET_H

#include "Column.h"
#include "Cell.h"

class Sheet {
private:
    vector<Column> kolommen;
public:
    // constructor, makes x kolommen met grote y
    Sheet(int x, int y);
    Cell getCell(int x, int y);
    std::vector<Column>::iterator begin();
    std::vector<Column>::iterator end();
};

#endif //SHEET_H
