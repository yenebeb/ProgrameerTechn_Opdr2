#ifndef SHEET_H
#define SHEET_H

#include "Column.h"
#include "Cell.h"
#include "SheetObserver.h"

class Sheet : public Serializable {
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

void serialize(std:: ostream &output);

void deserialize(std::ifstream &output);

};

#endif //SHEET_H
