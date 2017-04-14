#ifndef CELL_H
#define CELL_H


#include <memory>
#include "Serializable.h"
#include <string>
#include <sstream>
#include <iostream>

class CellValueBase;
class Serializable;

class Cell : public Serializable {
private :
    std::unique_ptr<CellValueBase> value;
public :
    Cell();
    Cell(const Cell &c);

    // returns pointer value
    std::unique_ptr<CellValueBase> readpointer(); 
    // sets value
    void setpointer(CellValueBase *y); 
    // sets value to nullptr
    void clearpointer(); 

    // returns string of a CellFormula
    std::string getCalcString(); 
    // returns string of a CellValue
    std::string getString(); 
    // writes to file
    // output has the outputstream
    void serialize (std:: ostream &output); 
    // reads from file
    // input has the inputstream
    void deserialize (std::ifstream &intput); 

};

//
//
class CellValueBase : public Cell {
private:

public:
    CellValueBase();
    virtual ~CellValueBase(){};
    virtual std::string stringValue(){};
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
    
    T getValue(){
        return value;
    }

// returns value als string
std::string stringValue(){
    return getValue();
}

std::string stringCalcValue(){};

};

template<typename T>
class CellFormula : public CellValueBase {
private:
    T value;
    T calcvalue;
public:
    CellFormula(T initial_value, T calc_value)
        : CellValueBase(), value(initial_value), calcvalue(calc_value)
        { };
    T getValue(){
        return value;
    }
    T getCalcValue(){
        return calcvalue;
    }

// returns calcvalue als string
std::string stringCalcValue(){
    return getCalcValue();
};

// returns value als string
std::string stringValue(){
    return getValue();
};


};
#endif // CELL_H
