#include "Range.h"
#include "CellAdress.h"
#include <iostream>
#include <sstream>
#include <string>
Range::Range()
{
}
Range::Range(std::string rangeReferentie){
    std::stringstream ss;
    ss.str(rangeReferentie);

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