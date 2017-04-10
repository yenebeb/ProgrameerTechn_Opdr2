#ifndef CELLADRESS_H
#define CELLADRESS_H

#include <string>
class CellAdress
{
    private:
        int kolomnummer;
        int rijnummer;
    public:
        CellAdress();
        CellAdress(char colnaam, int rijnmr);
        CellAdress(std::string celreferentie);
        CellAdress CreateFromReference(std::string celreferentie);
        virtual ~CellAdress();
        int getKolomnummer();
        int getRijnummer();

    protected:
};

#endif // CELLADRESS_H
