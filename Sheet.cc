
#include <vector>
#include "Sheet.h"
#include "SheetObserver.h"

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

void Sheet::addObserver(SheetObserver* ob){
	sheeto.push_back(ob);
}
vector<Column*>::iterator Sheet::begin(){

    return kolommen.begin();
}

vector<Column*>::iterator Sheet::end(){
    return kolommen.end();
}
