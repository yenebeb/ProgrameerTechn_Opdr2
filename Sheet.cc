
#include <vector>
#include "sheet.h"

using namespace std;
Sheet::Sheet(int x, int y){
    for(int i = 0; i < x; i++){
        Column kolom(y);
        kolommen.push_back(kolom);
    }
}

Cell Sheet::getCell(int x, int y){
    Column kolom = kolommen.at(x);
    return kolom.getCell(y);
}

vector<Column>::iterator Sheet::begin(){
    return kolommen.begin();
}

vector<Column>::iterator Sheet::end(){
    return kolommen.end();
}
