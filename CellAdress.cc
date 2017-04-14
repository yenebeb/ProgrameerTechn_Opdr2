#include "CellAdress.h"
#include <iostream>
#include <sstream>

CellAdress::CellAdress(char colnaam, int rijnmr)
{
    kolomnummer = colnaam - 'A';
    rijnummer = rijnmr - 1;
    //ctor
}
CellAdress::CellAdress()
{

}

// maakt celladress, met input celreferentie
CellAdress::CellAdress(std::string celreferentie)
{
    kolomnummer = celreferentie.at(0) - 'A'; 
    std::string myString = celreferentie.substr(1, 3);
    rijnummer = atoi(myString.c_str()) - 1;
}

CellAdress::~CellAdress()
{
    //dtor
}

// returns kolomnummer
int CellAdress::getKolomnummer()
{
    return kolomnummer;
}

// returns rijnummer
int CellAdress::getRijnummer()
{
    return rijnummer;
}

// maakt celladress vanuit celreferentie, en returnt de gemaakte CellAdess
CellAdress CreateFromReference(std::string celreferentie)
{
    return CellAdress(celreferentie);
}