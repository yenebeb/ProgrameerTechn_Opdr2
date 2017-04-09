#include "Range.h"
#include "CellAdress.h"
Range::Range()
{
}

CellAdress& Range::getBegin()
{
    return BeginCellAdress;
}
CellAdress& Range::getEnd()
{
    return EndCellAdress;
}
Sheet* Range::getSheet()
{
    return sheet;
}

Range::Range(CellAdress ca1, CellAdress ca2, Sheet *sh)
{
    BeginCellAdress = ca1;
    EndCellAdress = ca2;
    sheet = sh;
}