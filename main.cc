#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Range.h"
#include "CellAdress.h"
#include "SheetView.h"
#include "Sheet.h"

#include <curses.h>

int main()
{
    // sheet initialization
    Sheet sheet(24, 80);
    int k = 0;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            //     Cell *y = sheet.getCell(i, j);
            std::stringstream ss;
            ss << k;
            std::string s(ss.str());
            std::string x = std::string(s);
            k++;
            sheet.getCell(i, j)->setpointer(x);
        }
    }

    //Cell *c = sheet.getCell(2,2);
    //cout << c->getString();

    // ui
    static const int lines(24);
    static const int cols(160);

    SheetView s(lines, cols);

    s.tekenheaders();
    s.tekeninh(&sheet);

    /*
    std::stringstream ss;
    int b = 80000;
    ss << b;
    std::string f(ss.str());
    std::string x = std::string(f);
    sheet.getCell(2, 2)->setpointer(x);

    s.tekeninh(&sheet);
    */

    WINDOW *win = s.getWindow();

    wmove(win, 1, 10); // set cursor to start position

    /* Wacht tot er op enter wordt gedrukt */
    int ch;
    keypad(win, TRUE);
    refresh();
    
    while ((ch = wgetch(win)) != '\n')
    {
        int key = wgetch(win);
        switch(key)
        {
            case KEY_UP:
            
            break;
            case KEY_DOWN:

            break;
        }
        s.tekeninh(&sheet);
        //mousemask();
    }

    refresh();
    echo();
    endwin();
    return 0;
    /*
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
    */
}
