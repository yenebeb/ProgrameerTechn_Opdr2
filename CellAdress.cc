#include "CellAdress.h"

CellAdress::CellAdress(char colnaam, int rijnmr){
    kolomnummer = (int) colnaam;
    rijnummer = rijnmr;
    //ctor
}
CellAdress::CellAdress(std::string celreferentie){
    kolomnummer = celreferentie.at(0);
    rijnummer = (int)celreferentie.at(1)+1;
}
CellAdress::~CellAdress(){
    //dtor
}


CellAdress CreateFromReference(std::string celreferentie){
    //TODO: throw exception
    CellAdress Ca = CellAdress(celreferentie.at(0), (int)celreferentie.at(1)+1);
}