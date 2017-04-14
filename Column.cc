
#include "Column.h"
#include "Cell.h"
#include <vector>
#include <fstream>


//Construcor Column
using namespace std;
Column::Column(int size){
    for(int i =0; i < size; i++){
        Cell cel;
        Cell *c = new Cell();
        cellen.push_back(c);
    }
}

Cell* Column::getCell(int x){
    return cellen.at(x);
}

int Column::sizeVec(){
	return cellen.size();
}

void Column::serialize (std:: ostream &output){
	//output << cellen.size();
	int x = cellen.size() % 9;
	char y = 'A';

	for(int i = 0; i <= x; i++){
		output << y << ":";
		cellen.at(i)->serialize(output);
		y++;
	}
	output << '|';
}

void Column::deserialize (std::ifstream &output){
	int i;
	char y = 'A';
	char x;
	char in;
	output >> in;
	output >> x;

	while(x != '|'){
		i = x - y;
		output >> in;
		if(in == ':'){
			cellen.at(i)->deserialize(output);
			output >> x;
		}
	}
}


vector<Cell*>::iterator Column::begin(){
	   return cellen.begin();
}

vector<Cell*>::iterator Column::end(){
  	  return cellen.end();
}
