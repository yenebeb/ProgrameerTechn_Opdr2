#ifndef CELL_H
#define CELL_H


#include <memory>
#include "SheetObserver.h"
#include <string>
#include <sstream>
#include <iostream>

class CellValueBase;
class SheetObserver;

class Cell{
private :
    std::unique_ptr<CellValueBase> value ;
public :
    Cell();
    Cell(const Cell &c);
    std::unique_ptr<CellValueBase> readpointer();
    void setpointer(CellValueBase *y);
    void clearpointer();
    std::string getCalcString();

    std::string getString();
};

//
//
class CellValueBase : public Cell {
private:

public:
    CellValueBase();
    virtual ~CellValueBase(){};
    virtual std::string StringStreamValue(){};
    virtual std::string stringValue(){};
    virtual float floatValue(){};
    virtual std::string stringCalcValue(){};
};


//
//
template<typename T>
class CellValue final : public CellValueBase {
private:
    T value;
public:
    CellValue(T initial_value)
        : CellValueBase(), value(initial_value)
        { };

std::string StringStreamValue(){

    return "test";
};

std::string stringValue(){
    std::stringstream ss;
    ss << value;
    std::string s(ss.str());
    return s;
}

std::string stringCalcValue()
    {};

float floatValue(){
    //float x = float(value);
    return 5.3;
}



};

template<typename T>
class CellFormula : public CellValueBase, public SheetObserver {
private:
    T value;
    T calcvalue;
public:
    CellFormula(T initial_value, T calc_value)
        : CellValueBase(), value(initial_value), calcvalue(calc_value)
        { };
    std::string stringCalcValue(){
        std::stringstream ss;
        ss << calcvalue;
        std::string s(ss.str());
        return s;
    };

std::string StringStreamValue(){

    return "test";
};

std::string stringValue(){
    std::stringstream ss;
    ss << value;
    std::string s(ss.str());
    return s;
};



float floatValue(){
    //float x = float(value);
    return 5.3;
};

void cellChanged(const Cell &cell){

};
};
#endif // CELL_H
