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
        CellAdress(std::string colnaam, int rijnmr);
        void CreateFromReference(std::string celreferentie);
        virtual ~CellAdress();

    protected:
};

#endif // CELLADRESS_H
