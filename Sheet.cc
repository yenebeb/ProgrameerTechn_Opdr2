
#include <vector>
#include "Sheet.h"
#include <fstream>

using namespace std;

// maakt nieuwe Sheet met
// x rijregels en y kolomregels.
Sheet::Sheet(int x, int y){
    for(int i = 0; i < x; i++){
        Column* kolom = new Column(y);
        kolommen.push_back(kolom);
    }
}

// returns de cell op plaat (x,y) van de sheet
Cell* Sheet::getCell(int x, int y){
    Column* kolom = kolommen.at(x);
    return kolom->getCell(y);
}

// schrijft naar file
void Sheet::serialize(std:: ostream &output){
    output << kolommen.size() << " " << kolommen.at(0)->sizeVec(); // prints aantal rijen en kolommen
    output << "\n";
    int i = 0;
    // print elke kolom
    for(; i < kolommen.size()-1; i++){
        output << i+1 << " |";
        kolommen.at(i)->serialize(output);
        output << "\n";
    }
    // print laatste kolom
    output << i+1 << " |";
    kolommen.at(i)->serialize(output);
    output << "|";

}

// leest van file
void Sheet::deserialize(std::ifstream &input){
    int x = 0;
    // zolang het einde van de file (|) niet is bereikt
    // wordt er een nieuwe kolom gelezen
    while(input.peek() != '|'){
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
