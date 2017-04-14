#ifndef CELLADRESS_H
#define CELLADRESS_H

#include <string>
class CellAdress
{
    private:
        int kolomnummer; //kolomnummer
        int rijnummer; // rijnummer
    public:
        // default constructor
        CellAdress();
        // construcot, colnaam = kolomnaam, rijnmr = rijnummer
        CellAdress(char colnaam, int rijnmr);
        // constructor met celreferentie
        CellAdress(std::string celreferentie);
        // maakt en returnt CellAdress met een celreferentie
        CellAdress CreateFromReference(std::string celreferentie);
        virtual ~CellAdress();
        int getKolomnummer(); // returns kolomnummer
        int getRijnummer(); // returns rijnummer

    protected:
};

#endif // CELLADRESS_H
