#ifndef SHEET_H
#define SHEET_H

#include "Column.h"
#include "Cell.h"

class Sheet : public Serializable {
private:
    vector<Column*> kolommen;
public:
    // constructor, maakt sheet met
    // x kolommen en y rijen
    Sheet(int x, int y);
    // returns Cell
    // op coordinaat (x, y)
    Cell* getCell(int x, int y);

    // returns begin iterator van kolommen
    std::vector<Column*>::iterator begin();
    // returns eind iterator van kolommen
    std::vector<Column*>::iterator end();

// schrijft kolommen naar outputfile
void serialize(std:: ostream &output);
// leest kolommen van outputfile
void deserialize(std::ifstream &output);

};

#endif //SHEET_H
