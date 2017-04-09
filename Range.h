#ifndef RANGE_H
#define RANGE_H

#include "CellAdress.h"
#include "Sheet.h"
/* Forward declaration*/
class RangeIterator;

class Range
{
  private:
    CellAdress BeginCellAdress;
    CellAdress EndCellAdress;
    Sheet *sheet;

  public:
    Range();
    CellAdress getBegin();
    CellAdress getEnd();
    Sheet *getSheet();
    Range(CellAdress x, CellAdress y, Sheet *p);

    typedef RangeIterator iterator;
    
    RangeIterator begin(void);
    RangeIterator end(void);
};
#endif //RANGE_H

class RangeIterator : public std::iterator<std::input_iterator_tag, int>
{
  private:
    Range &range;
    size_t offset;

  public:
    RangeIterator(Range &range, size_t offset)
        : range(range), offset(offset)
    {
    }

    bool operator==(const RangeIterator &Riter) const
    {
        return !operator==(Riter);
    }
    Cell *operator->() const
    {
        char k = range.getBegin().getKolomnummer();
        char k1 = range.getEnd().getKolomnummer();
        int i = range.getBegin().getRijnummer();
        int i1 = range.getEnd().getRijnummer();

        char m = offset % (k1 - k);
        int l = offset / (i1 - i);

        return range.getSheet()->getCell((int)(k + m), i + l);
    }
    Cell &operator*() const
    {
        char k = range.getBegin().getKolomnummer();
        char k1 = range.getEnd().getKolomnummer();
        int i = range.getBegin().getRijnummer();
        int i1 = range.getEnd().getRijnummer();

        char m = offset % (k1 - k);
        int l = offset / (i1 - i);

        return *range.getSheet()->getCell((int)(k + m), i + l);
    }
    RangeIterator &operator++()
    {
        ++offset;
    }
};
