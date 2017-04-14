
#include "Column.h"
#include "Cell.h"
#include <vector>
#include <fstream>


//Construcor Column
using namespace std;
Column::Column(int size){
	// maakt nieuwe cellen, en pusht ze in vector cellen
    for(int i =0; i < size; i++){
        Cell cel; 
        Cell *c = new Cell();
        cellen.push_back(c);
    }
}

// returns cel op plaat x
Cell* Column::getCell(int x){
    return cellen.at(x);
}

// returns grote van vector cellen
int Column::sizeVec(){
	return cellen.size();
}

// schrijft naar file
void Column::serialize (std:: ostream &output){
	int x = cellen.size() % 9; // x aantal cellen
	char y = 'A'; // kolomLetter

	// print kolomletter naar file, en print voor elke kolom de cellen
	for(int i = 0; i <= x; i++){
		output << y << ":";
		cellen.at(i)->serialize(output);
		y++;
	}
	output << '|';
}

// leest vanuit file
void Column::deserialize (std::ifstream &input){
	int i; // x - y is kolomnummer
	char y = 'A'; // de eerste kolom
	char x; // de kolomletter
	char in; // checkt op :

	input >> in;
	input >> x;

	// zolang x != |, is de input in dezelfde rij
	while(x != '|'){
		i = x - y; // kolomnummer
		input >> in;
		if(in == ':'){
			cellen.at(i)->deserialize(input);
			input >> x;
		}
	}
}

// returns begin iterator van cellen
vector<Cell*>::iterator Column::begin(){
	   return cellen.begin();
}

// returns eind iterator van cellen
vector<Cell*>::iterator Column::end(){
  	  return cellen.end();
}
