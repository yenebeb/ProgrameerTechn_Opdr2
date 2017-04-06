#include "Cell.h"
#include "CellValueBase.h"

using namespace std;
Cell::Cell(){
    value = nullptr;
}

std::unique_ptr<CellValueBase> Cell::readpointer(){
//    return value;

}

void Cell::setpointer(string x){
    CellValue<string> waarde(x);
//    value(new CellValueBase(), (CellValueBase) waarde);
}

void Cell::clearpointer(){
    value = nullptr;
}

CellValueBase::CellValueBase(){

};
