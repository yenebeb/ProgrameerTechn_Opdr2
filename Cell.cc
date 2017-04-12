#include "Cell.h"
#include "SheetObserver.h"
#include <memory>
#include <iostream>

using namespace std;
Cell::Cell()
{
    value = unique_ptr<CellValueBase>(nullptr);
}

Cell::Cell(const Cell &o)
{
    value = unique_ptr<CellValueBase>(nullptr);
}

unique_ptr<CellValueBase> Cell::readpointer()
{
    unique_ptr<CellValueBase> y = move(value);
    return y;
}

string Cell::getString()
{
    CellValueBase *y;
    y = value.get();
    if(y == nullptr){
        return "";
    }
    return y->stringValue();
}

string Cell::getCalcString()
{
    CellValueBase *y;
    y = value.get();
    if(y == nullptr){
        return "";
    }
    return y->stringCalcValue();
}

void Cell::setpointer(CellValueBase *y)
{
    unique_ptr<CellValueBase> x(y);
    value = move(x);
    //Sheet seintje
    //Sheet.cellverandert(this*)

}
/*
void Cell::setpointer(string s)
{
    CellValueBase *y = new CellValue<string>(s);
    unique_ptr<CellValueBase> x(y);
    value = move(x);
    //Sheet seintje
    //Sheet.cellverandert(this*)

}*/

void Cell::clearpointer()
{
    value.reset();
}

CellValueBase::CellValueBase(){

};
