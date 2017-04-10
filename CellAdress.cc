#include "CellAdress.h"
#include <iostream>
#include <sstream>
CellAdress::CellAdress(char colnaam, int rijnmr)
{
    kolomnummer = colnaam - 'A';
    rijnummer = rijnmr -1;
    //ctor
}

CellAdress::CellAdress(std::string celreferentie)
{

    kolomnummer = celreferentie.at(0) - 'A';
    std::string myString = celreferentie.substr(1,3);
    rijnummer = atoi(myString.c_str()) -1;
}

CellAdress::CellAdress()
{
}

CellAdress::~CellAdress()
{
    //dtor
}
int CellAdress::getKolomnummer()
{
    return kolomnummer;
}
int CellAdress::getRijnummer()
{
    return rijnummer;
}

CellAdress CreateFromReference(std::string celreferentie)
{
    //TODO: throw exception
    return CellAdress(celreferentie);
}