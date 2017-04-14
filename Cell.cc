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
    CellValueBase *y; // maak nieuwe pointer CellValueBase
    y = value.get(); // zet gelijk aan value
    // als value een nullptr is, return lege string
    if(y == nullptr){
        return "";
    }
    return y->stringValue();
}

// idem getstring, voor calcvalue
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
    unique_ptr<CellValueBase> x(y); //maak nieuwe unique pointer, naar y
    value = move(x); // laat value naar de inhoud van x pointen. Dit vewijdert de x pointer
}

void Cell::serialize (ostream &output){
    // getstring from cellValueBase
    std::string inhoud = this->getString();
    inhoud += "|"; // plaats | achter inhoud
    output << inhoud; //print naar file
}


void Cell::deserialize (std::ifstream &input){
    char x; // char om in te lezen
    CellValueBase *y; // de cellValueBase die aangemaakt moet worden
    string inhoud = "";
    input.get(x); 
    
    // lees character en sla het op in sting inhoud
    // totdat x gelijk is aan | 
    while(x != '|'){
        inhoud += x; 
        input.get(x);
    }
    size_t search = inhoud.find("="); // zoekt naar = teken in string inhoud
    
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
