
#include "Column.h"
#include "Cell.h"
#include <vector>

//Construcor Column
using namespace std;
Column::Column(int size){
    for(int i =0; i < size; i++){
        Cell cel;
        Cell c(cel);
        cellen.push_back(Cell());
    }
}

Cell Column::getCell(int x){
    return cellen.at(x);
}

vector<Cell>::iterator Column::begin(){
    //return cellen.begin();
}

vector<Cell>::iterator Column::end(){
    //return cellen.end();
}
