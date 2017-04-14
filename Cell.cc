#include "Cell.h"
#include <memory>
#include <fstream>
#include <string>
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

    // if value is a nullptr, return empty string
    if(y == nullptr){
        return "";
    }
    return y->stringCalcValue();
}

void Cell::setpointer(CellValueBase *y)
{
    unique_ptr<CellValueBase> x(y);
    value = move(x);
}

void Cell::serialize (ostream &output){
    // getstring from cellValueBase
    std::string inhoud = this->getString();
    inhoud += "|";
    output << inhoud;
}


void Cell::deserialize (std::ifstream &input){
    char x;
    CellValueBase *y;
    string inhoud = "";
    input.get(x);
    while(x != '|'){
        inhoud += x;
        input.get(x);
    }
    size_t search = inhoud.find("=");
    
    // if '=' has been found, make CellFormula
    if(search != string::npos){
        y = new CellFormula<string>(inhoud, "");
    }
    // else make CellValue
    else{
        y = new CellValue<string>(inhoud);
    }
    this->setpointer(y);
}

void Cell::clearpointer()
{
    value.reset();
}

CellValueBase::CellValueBase(){

};
