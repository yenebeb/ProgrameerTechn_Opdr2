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
    // defaultconstructor
    Range();
    // constructor
    Range(std::string rangeReferentie, Sheet *sh);
    // returns eerste CellAdress
    CellAdress getBegin();
    // returns laatste CellAdress
    CellAdress getEnd();
    // returns pointer naar sheet
    Sheet *getSheet();
    // maakt range, met 
    // beginCellAdres = x, 
    // eindCelladres = y,
    // op sheet p.
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
    {}
    bool operator==(const RangeIterator &Riter) const
    {
        return &Riter.range == &range && Riter.offset == offset;
    }
    bool operator!=(const RangeIterator &Riter) const
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
        int k = range.getBegin().getKolomnummer();
        int k1 = range.getEnd().getKolomnummer();

        int i = range.getBegin().getRijnummer();
        int i1 = range.getEnd().getRijnummer();

        char m = offset / (k1 - k + 1);
        int l = offset % (k1 - k + 1);


        return *range.getSheet()->getCell((int)(i + m), k + l);
    }
    CellAdress getCellAdress(){
        int k = range.getBegin().getKolomnummer();
        int k1 = range.getEnd().getKolomnummer();

        int i = range.getBegin().getRijnummer();
        int i1 = range.getEnd().getRijnummer();
        char m = offset / (k1 - k + 1);
        int l = offset % (k1 - k + 1);
        return CellAdress('A'+k+l, i+m+1);
    }
    RangeIterator &operator++()
    {
        ++offset;
        return *this;
    }
    int getOffset(){
        return offset;
    }
};
