
template<typename T>
class CellFormula : public CellValueBase, public SheetObserver {
private:
    T value;
    T calcvalue;
public:
    CellFormula(T initial_value)
        : CellValueBase(), value(initial_value)
        { 
        	SheetObserver* x = *this;
        };
    void setclacValue();

std::string StringStreamValue(){

    return "test";
};

std::string stringValue(){
    std::stringstream ss;
    ss << value;
    std::string s(ss.str());
    return s;
};

std::string stringCalcValue(){
    std::stringstream ss;
    ss << calcvalue;
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