#ifndef RANGE_H
#define RANGE_H

#include "CellAdress.h"
/* Forward declaration*/
class RangeIterator;

class Range {
private:
    CellAdress beginCellAdress;
    CellAdress EndCellAdress;
public:
    RangeIterator begin();
    Rangeterator end();
};
#endif //RANGE_H

class RangeIterator{


}

