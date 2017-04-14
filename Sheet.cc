
#include <vector>
#include "Sheet.h"
#include <fstream>

using namespace std;
Sheet::Sheet(int x, int y){
    for(int i = 0; i < x; i++){
        Column* kolom = new Column(y);
        kolommen.push_back(kolom);
    }
}

Cell* Sheet::getCell(int x, int y){
    Column* kolom = kolommen.at(x);
    return kolom->getCell(y);
}

void Sheet::serialize(std:: ostream &output){
    output << kolommen.size() << " " << kolommen.at(0)->sizeVec();
    output << "\n";
    int i = 0;
    for(; i < kolommen.size()-1; i++){
        output << i+1 << " |";
        kolommen.at(i)->serialize(output);
        output << "\n";
    }
    output << i+1 << " |";
    kolommen.at(i)->serialize(output);
    output << "|";

}

void Sheet::deserialize(std::ifstream &input){
    int x = 0;

    while(input.peek() != '|' && x < 40){
        input >> x;
        kolommen.at(x-1)->deserialize(input);
    }
}

vector<Column*>::iterator Sheet::begin(){

    return kolommen.begin();
}

vector<Column*>::iterator Sheet::end(){
    return kolommen.end();
}
