#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Range.h"
#include "CellAdress.h"
#include <curses.h>

int main()
{

    static const int lines(24);
    static const int cols(160);

    initscr();
    raw();
    noecho();

    /* Maak een venster, grootte lines x cols */
    WINDOW *win = newwin(lines, cols, 0, 0);
    keypad(win, TRUE); /* Enable keypad input */
    attr_t old_attr; /* Huidige settings onthouden */
    short old_pair;
    int q = 1;
    wattr_get(win, &old_attr, &old_pair, NULL);
    for(int i = 0; i <= 24; i++){
        for(int j = 0; j <= 80; j++){
            wattron(win, A_STANDOUT);    
            wmove(win, i, j);

            if(i ==0){
                if(j%10 == 0){
                    waddstr(win,"a");
                }
                else{
                    waddstr(win, " ");
                }
                refresh();

            }
            else if(j == 0){
                wattr_set(win, old_attr, old_pair, NULL); /* Oude settings terugzetten */
                string s = to_string(q);
                //printw("test"); // << test printw
                const char* x = s.c_str();
                waddstr(win, x);
                q++;
                refresh();
            }
            else if(i==5 && j == 30) {
                ostringstream os;
                os << "test";
                string begin = os.str();
                const char *c = begin.c_str();
                waddstr(win, c);

                refresh();            

            }

        }
        printw("\n");
    }
    /* Verplaats cursor rij 10, kolom 20 */
   
    /* Nogmaals, maar nu op een achtergrond */
 
   // wattr_get(win, &old_attr, &old_pair, NULL);

    wattron(win, A_STANDOUT);
    wmove(win, 0, 0);
    //waddstr(win, "HELLO WORLD!!!");
    wattr_set(win, old_attr, old_pair, NULL); /* Oude settings terugzetten */
    Sheet sheet(5, 5);

    Range a("A2:B5", &sheet);
    /* 
    ostringstream os;
    os << "begin= "  << a.getBegin().getKolomnummer() << a.getBegin().getRijnummer();
    string begin = os.str();
    const char *c = begin.c_str();
    waddstr(win, c); */
    
    /* Wacht tot er op enter wordt gedrukt */
    int ch;
    while ((ch = wgetch(win)) != '\n'){
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
