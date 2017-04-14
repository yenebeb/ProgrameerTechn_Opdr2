#ifndef COLUMN_H
#define COLUMN_H

#include "Cell.h"
#include "Serializable.h"
#include <vector>

using namespace std;
class Column : public Serializable {
private:
    vector<Cell*> cellen;
public:
    //constructor, maakt x aantal cellen
    Column(int x);
    Cell* getCell(int x);
    int sizeVec();
    std::vector<Cell*>::iterator begin();
    std::vector<Cell*>::iterator end();
	void serialize (std:: ostream &output);

	void deserialize (std::ifstream &output);
};

#endif // COLUMN_H
