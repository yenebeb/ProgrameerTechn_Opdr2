#include "Range.h"
#include "CellAdress.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
Range::Range()
{
}
//Range constructor dmv een string en een sheet
Range::Range(string rangeReferentie, Sheet *sh){
    stringstream ss;
    ss.str(rangeReferentie);
    string reference;
    getline(ss,reference, ':');
    BeginCellAdress = CellAdress(reference);
    getline(ss,reference, ':');
    EndCellAdress = CellAdress(reference);
    sheet = sh;
}
// returnt de BeginCellAdress
CellAdress Range::getBegin()
{
    return BeginCellAdress;
}
// returnt de EndCellAdress 
CellAdress Range::getEnd()
{
    return EndCellAdress;
}
//returnt de sheet
Sheet *Range::getSheet()
{
    return sheet;
}
// Range constructer
Range::Range(CellAdress ca1, CellAdress ca2, Sheet *sh)
{
    BeginCellAdress = ca1;
    EndCellAdress = ca2;
    sheet = sh;
}

// returnt de begin iterator
RangeIterator Range::begin(void)
{
    return RangeIterator(*this, 0);
}
// returnt de end iterator
RangeIterator Range::end(void)
{
    CellAdress a = getBegin();
    CellAdress b = getEnd();
    int breedte = 1 + b.getKolomnummer() - a.getKolomnummer();
    int hoogte = 1 + b.getRijnummer() - a.getRijnummer();
    return RangeIterator(*this, breedte*hoogte);
}