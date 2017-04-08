#ifndef RANGE_H
#define RANGE_H

#include "CellAdress.h"
#include "Sheet.h"
/* Forward declaration*/
class RangeIterator;

class Range {
private:
    CellAdress BeginCellAdress;
    CellAdress EndCellAdress;
    Sheet *sheet;
public:
    Range();
    Range(CellAdress x, CellAdress y , Sheet* p);
    RangeIterator begin();
    RangeIterator end();
};
#endif //RANGE_H

class RangeIterator : public std::iterator<std::input_iterator_tag, int>{
private:
    Range &range;
    size_t offset;
 /*
public:
    RangeIterator(Range &range,  size_t offset)
        : Range(range), offset(offset)
    {}
*/
    
};

