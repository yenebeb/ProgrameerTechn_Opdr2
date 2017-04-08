#include "Cell.h"
#include <memory>
#include <iostream>

using namespace std;
Cell::Cell(){
    value = unique_ptr<CellValueBase>(nullptr);
}

Cell::Cell(const Cell& o){
    value = unique_ptr<CellValueBase>(nullptr);
}

unique_ptr<CellValueBase> Cell::readpointer(){
    unique_ptr<CellValueBase> y = move(value);
    return y;

}

void Cell::setpointer(string s){
    CellValueBase* y = new CellValue<string>(s);
    unique_ptr<CellValueBase> x(y);
    value = move(x);
}

void Cell::clearpointer(){
    value.reset();
}

CellValueBase::CellValueBase(){

};
