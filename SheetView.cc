#include <curses.h>
#include <string>
#include "SheetView.h"
#include <iostream>
#include <sstream>


using namespace std;
SheetView::SheetView(int lines, int cols){
	initscr();
    raw();
    noecho();
	win = newwin(lines, cols, 0, 0);


}

void SheetView::tekenheaders(){
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
}

WINDOW* SheetView::getWindow(){
	return win;

}