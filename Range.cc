#include "Range.h"
#include "CellAdress.h"
#include <iostream>
#include <sstream>
#include <string>
Range::Range()
{
}
Range::Range(std::string rangeReferentie, Sheet *sh){
    std::stringstream ss;
    ss.str(rangeReferentie);
    std::string reference;
    std::getline(ss,reference, ':');
    BeginCellAdress = CellAdress(reference);
    std::getline(ss,reference, ':');
    EndCellAdress = CellAdress(reference);
    sheet = sh;
}
CellAdress Range::getBegin()
{
    return BeginCellAdress;
}
CellAdress Range::getEnd()
{
    return EndCellAdress;
}
Sheet *Range::getSheet()
{
    return sheet;
}

Range::Range(CellAdress ca1, CellAdress ca2, Sheet *sh)
{
    BeginCellAdress = ca1;
    EndCellAdress = ca2;
    sheet = sh;
}

RangeIterator Range::begin(void)
{
    return RangeIterator(*this, 0);
}

RangeIterator Range::end(void)
{
    CellAdress a = getBegin();
    CellAdress b = getEnd();
    int breedte = 1 + b.getKolomnummer() - a.getKolomnummer();
    int hoogte = 1 + b.getRijnummer() - a.getRijnummer();
    return RangeIterator(*this, breedte*hoogte);
}