#include <curses.h>
#include <string>
#include "SheetView.h"
#include "Sheet.h"
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
                string s = "   ";
                s += to_string(q);
                for(int k = s.size(); k < 8; k++){
                    s += " ";
                }
                const char* x = s.c_str();
                waddstr(win, x);
                q++;
                refresh();
            }
        }
    }
}

void SheetView::tekeninh(Sheet sheet){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j <= 80; j++){
            wmove(win, i, j);
            if(i != 0 && (j-2) % 8 == 0 && j > 7){
                Cell *c = sheet.getCell(2,2);
                string begin = c->getString();
            }
        }
    }
}

WINDOW* SheetView::getWindow(){
	return win;

}