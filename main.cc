#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Range.h"
#include "CellAdress.h"
#include "SheetView.h"
#include <curses.h>

int main()
{
    // sheet initialization
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
    
   // Cell *c = sheet.getCell(2,2);
   // cout << c->getString();



    
    // ui
    static const int lines(24);
    static const int cols(160);


    SheetView s(lines, cols);
    s.tekenheaders();
    WINDOW *win = s.getWindow();
    attr_t old_attr; /* Huidige settings onthouden */

    short old_pair;
    wattr_get(win, &old_attr, &old_pair, NULL);

    wmove(win, 0, 0);
    //waddstr(win, "HELLO WORLD!!!");
    wattr_set(win, old_attr, old_pair, NULL); /* Oude settings terugzetten */


    Range a("A2:B5", &sheet);

    /* Wacht tot er op enter wordt gedrukt */
    int ch;
    while ((ch = wgetch(win)) != '\n')
    {
        //mousemask();
    }

    refresh();
    echo();
    endwin();
    return 0;
    cout << endl
         << endl
         << endl;

    cout << "end=" << a.getEnd().getKolomnummer() << a.getEnd().getRijnummer() << endl;


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

    cout << kolom << rij << endl;

    int kolom1 = range.getEnd().getKolomnummer();
    int rij1 = range.getEnd().getRijnummer();

    cout << kolom1 << rij1 << endl;

    RangeIterator rir = range.begin();
    for (int i = 0; i < 8; i++)
    {
        ++rir;
        Cell *z = &*rir;
        cout << rir.getOffset();
        unique_ptr<CellValueBase> test = move(z->readpointer());
        cout << "value=" << test->stringValue() << " <<<< ";
    }
}
