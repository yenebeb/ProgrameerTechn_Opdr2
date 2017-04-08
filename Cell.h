#ifndef CELL_H
#define CELL_H


#include <memory>
#include <string>
#include <sstream>
#include <iostream>

class CellValueBase;

class Cell{
private :
    std::unique_ptr<CellValueBase> value ;
public :
    Cell();
    Cell(const Cell &c);
    std::unique_ptr<CellValueBase> readpointer();
    void setpointer(std::string s);
    void clearpointer();
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

float floatValue(){
    //float x = float(value);
    return 5.3;
}

};

#endif // CELL_H
