#include "CellAdress.h"

CellAdress::CellAdress(char colnaam, int rijnmr)
{
    kolomnummer = (int) colnaam- 'A';
    rijnummer = rijnmr -1;
    //ctor
}

CellAdress::CellAdress(std::string celreferentie)
{
    kolomnummer = celreferentie.at(0) - 'A';
    rijnummer = celreferentie.at(1) - 1;
}

CellAdress::CellAdress()
{
}

CellAdress::~CellAdress()
{
    //dtor
}
char CellAdress::getKolomnummer()
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
    CellAdress Ca = CellAdress(celreferentie.at(0), (int)celreferentie.at(1) - 1);
}