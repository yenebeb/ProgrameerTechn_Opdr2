#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Range.h"
#include "CellAdress.h"
#include "SheetView.h"
#include "Sheet.h"
#include <string>

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

    std::stringstream ss;
    int b = 222222222;
    ss << b;
    std::string f(ss.str());
    std::string x = std::string(f);
    sheet.getCell(2, 2)->setpointer(x);

    s.tekeninh(&sheet);

    WINDOW *win = s.getWindow();

    wmove(win, 1, 10); // set cursor to start position

    /* Wacht tot er op enter wordt gedrukt */
    int key;
    keypad(win, TRUE);
    refresh();
    cbreak();

    while ((key = wgetch(win)) != 'q')
    {
        //int key = wgetch(win);
        std::vector<int> vec;
        switch (key)
        {

        case KEY_UP:
            vec = s.getCursor();
            if (vec.at(0) > 0)
                vec.at(0)--;
            s.setCursor(vec);
            move(1, 10);
            refresh();
            break;
        case KEY_DOWN:
            vec = s.getCursor();
            if (vec.at(0) < 22)
                vec.at(0)++;
            s.setCursor(vec);
            break;
        case KEY_RIGHT:
            vec = s.getCursor();
            if (vec.at(1) < 8)
                vec.at(1)++;
            s.setCursor(vec);
            break;
        case KEY_LEFT:
            vec = s.getCursor();
            if (vec.at(1) > 0)
                vec.at(1)--;
            s.setCursor(vec);
            break;
        case 'n':
        {
            Range range(CellAdress('B', 1), CellAdress('D', 3), &sheet);
            RangeIterator rir = range.begin();

            string inh = "";
            int value = 0;
            try
            {
                for (int i = 0; i < 4; i++)
                {
                    Cell *z = &*rir;
                    inh = z->getString();
                    value += stoi(inh.c_str());
                    ++rir;
                }
                sheet.getCell(5, 5)->setpointer(to_string(value));
            }
                catch (exception &e)
                {
                    sheet.getCell(5, 5)->setpointer("NAN");
                }
            
            refresh();
            break;
        }
        case '\n':
            vec = s.getCursor();
            WINDOW *popup = newwin(3, 19, 1, 1);
            mvwin(popup, vec.at(0), vec.at(1) * 8 + 3);
            wmove(popup, 1, 1);
            wborder(popup, '|', '|', '-', '-', '+', '+', '+', '+');
            wrefresh(popup);
            // input van user naar cell en display ook pak oude en plaats

            string input = "";
            Cell *d = sheet.getCell(vec.at(0), vec.at(1));
            string inhoud = d->getString();
            wmove(popup, 1, 1);
            const char *c = inhoud.c_str();
            waddstr(popup, c);
            wrefresh(popup);
            while ((key = wgetch(win)) != '\n')
            {
                wmove(popup, 1, 1);
                c = "                 ";
                waddstr(popup, c);
                if (key == KEY_BACKSPACE)
                {
                    if (inhoud.size())
                        inhoud.pop_back();
                }
                else if (inhoud.size() < 17)
                {
                    inhoud += key;
                }
                c = inhoud.c_str();
                wmove(popup, 1, 1);
                waddstr(popup, c);
                wrefresh(popup);
            }
            sheet.getCell(vec.at(0), vec.at(1))->setpointer(inhoud);
            s.tekenheaders();
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
