#ifndef SHEET_H
#define SHEET_H

#include "Column.h"
#include "Cell.h"
#include "SheetObserver.h"

class Sheet {
private:
    vector<Column*> kolommen;
    vector<SheetObserver*> sheeto;
public:
    // constructor, makes x kolommen met grote y
    Sheet(int x, int y);
    Cell* getCell(int x, int y);
    void cellVerandert(const Cell &cell);
    void addObserver(SheetObserver* x);
    std::vector<Column*>::iterator begin();
    std::vector<Column*>::iterator end();
};

#endif //SHEET_H
