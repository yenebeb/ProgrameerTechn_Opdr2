#include "Cell.h"
#include "SheetObserver.h"
#include <memory>
#include <iostream>
#include <fstream>

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

void Cell::serialize (ostream &output){

    std::string inhoud = this->getString(); //ophalen en afkappen na 8 tekens
   
    inhoud += " |";
    output << inhoud;
}

void Cell::deserialize (std::ifstream &output){
    char x;
    CellValueBase *y;
    string inhoud = "";
    output.get(x);
    while(x != '|'){
        inhoud += x;
        output.get(x);

    }
    if(inhoud.find_first_not_of(' ') == std::string::npos){
        inhoud = "";
    }

        size_t search = inhoud.find("=");
        if(search != string::npos){
            y = new CellFormula<string>(inhoud, "");
        }
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
