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

    // returns cell op positie x
    Cell* getCell(int x);

    // returns size of cellen
    int sizeVec();

    // returns beginiterator cellen
    std::vector<Cell*>::iterator begin();
    // returns enditerator cellen
    std::vector<Cell*>::iterator end();

    // writes cellen to file
	void serialize (std:: ostream &output);
	// reads from file
	void deserialize (std::ifstream &intput);
};

#endif // COLUMN_H
