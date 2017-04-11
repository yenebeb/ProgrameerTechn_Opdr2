#include <curses.h>
#include <string>
#include "SheetView.h"
#include <iostream>
#include <sstream>
#include "Sheet.h"

using namespace std;
SheetView::SheetView(int lines, int cols){
	initscr();
    raw();
    noecho();
	win = newwin(lines, cols, 0, 0);


}

void SheetView::tekenheaders(Sheet* sheet){
    int q = 1;
    char topHeaderChar = 'A';
    const char *topHeader = &topHeaderChar;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j <= 80; j++){
            wattron(win, A_STANDOUT);    
            wmove(win, i, j);

            if(i ==0){
                if(j%8 == 2 && j > 2){
                    waddstr(win, topHeader);
                    topHeaderChar++;
                }
                else if(j > 7){
                    waddstr(win, " ");
                }
                refresh();

            }
            else if(j == 0){
           //     wattr_set(win, old_attr, old_pair, NULL); /* Oude settings terugzetten */
                string s = "   ";
                s += to_string(q);
                for(int k = s.size(); k < 8; k++){
                    s += " ";
                }
                //printw("test"); // << test printw
                const char* x = s.c_str();
                waddstr(win, x);
                q++;
                refresh();
            }
            else if((j-2) % 8 == 0 && j > 7){

                    Cell *d = sheet->getCell(i-1,(j-8)/8);
                    string test  = d->getString();
                    const char *c = test.c_str();
                    waddstr(win,c);
                    refresh;
            }
        }
    }
}
WINDOW* SheetView::getWindow(){
	return win;

}