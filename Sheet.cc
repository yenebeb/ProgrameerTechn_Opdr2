
#include <vector>
#include "Sheet.h"
#include "SheetObserver.h"
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

void Sheet::cellVerandert(const Cell &cell){
	if(sheeto.size() > 0){
		for(vector<SheetObserver*>::iterator it = sheeto.begin(); it != sheeto.end(); ++it) {
			SheetObserver* x =*it;
			x->cellChanged(cell);
		}
	}
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

void Sheet::deserialize(std::ifstream &output){
    int x = 0;

    while(output.peek() != '|' && x < 40){
        output >> x;
        kolommen.at(x-1)->deserialize(output);
    }
}



void Sheet::addObserver(SheetObserver* ob){
	sheeto.push_back(ob);
}

vector<Column*>::iterator Sheet::begin(){

    return kolommen.begin();
}

vector<Column*>::iterator Sheet::end(){
    return kolommen.end();
}
