
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
	int x = cellen.size() % 9; // x aantal cellen
	char y = 'A'; // kolomLetter

	for(int i = 0; i <= x; i++){
		output << y << ":";
		cellen.at(i)->serialize(output);
		y++;
	}
	output << '|';
}

void Column::deserialize (std::ifstream &input){
	int i; // x - y is kolomnummer
	char y = 'A'; // de eerste kolom
	char x; // de kolomletter
	char in; // checkt op :

	input >> in;
	input >> x;

	while(x != '|'){
		i = x - y;
		input >> in;
		if(in == ':'){
			cellen.at(i)->deserialize(input);
			input >> x;
		}
	}
}


vector<Cell*>::iterator Column::begin(){
	   return cellen.begin();
}

vector<Cell*>::iterator Column::end(){
  	  return cellen.end();
}
