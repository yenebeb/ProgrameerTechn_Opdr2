#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Range.h"
int main()
{



	cout << endl << endl << endl;
    Sheet sheet(5, 5);
    int k = 0;
    for (int i = 0; i < 5; i++)
    {
	for (int j = 0; j < 5; j++)
	{
	    Cell *y = sheet.getCell(i, j);
	    std::stringstream ss;
	    ss << k;
	    std::string s(ss.str());
	    std::string x = std::string(s);
	    k++;
	    sheet.getCell(i, j)->setpointer(x);
	}
    }
    /*
    for (int i = 0; i < 5; i++)
    {
		for (int j = 0; j < 5; j++)
		{
	    	
			Cell *z = sheet.getCell(i, j);
			//  	vector<Column*>::iterator l = sheet.begin();
			unique_ptr<CellValueBase> test = move(z->readpointer());
			cout << test->stringValue() << " <<<< ";
	    
		}
	cout << std::endl;
    }
    cout << std::endl;
*/
    Range range(CellAdress('B', 1), CellAdress('D', 3), &sheet);
    int kolom = range.getBegin().getKolomnummer();
    int rij = range.getBegin().getRijnummer();

    cout << kolom << rij<< endl;

	int kolom1 = range.getEnd().getKolomnummer();
    int rij1 = range.getEnd().getRijnummer();

	cout << kolom1 << rij1 << endl;

    RangeIterator rir = range.begin();
    for (int i = 0; i < 3; i++)
    {
	++rir;
    }
    Cell *z = &*rir; // wtf is dit werkt deze shit ####yolobolo
    cout << rir.getOffset();
    unique_ptr<CellValueBase> test = move(z->readpointer());
    cout << "value=" << test->stringValue() << " <<<< ";
}
