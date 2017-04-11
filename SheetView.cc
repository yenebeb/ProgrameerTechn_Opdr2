#include <curses.h>
#include <string>
#include "SheetView.h"
#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Sheet.h"

using namespace std;
SheetView::SheetView(int lines, int cols)
{
    initscr();
    raw();
    noecho();
    win = newwin(lines, cols, 0, 0);
}

void SheetView::tekenheaders()
{
    int q = 1;
    char topHeaderChar = 'A';
    const char *topHeader = &topHeaderChar;

    attr_t old_attr; /* Huidige settings onthouden */
    short old_pair;
    wattr_get(win, &old_attr, &old_pair, NULL);

    wattron(win, A_STANDOUT);
    wmove(win, 0, 0);
    //teken de top header
    for (int j = 0; j <= 80; j++)
    {
        wmove(win, 0, j);
        if (j % 8 == 2 && j > 2)
        {
            waddstr(win, topHeader);
            topHeaderChar++;
        }
        else if (j > 7)
        {
            waddstr(win, " ");
        }
    }
    //teken side header
    for (int i = 1; i < 24; i++)
    {
        wmove(win, i, 0);
        string s = "   ";
        s += to_string(q);
        for (int k = s.size(); k < 8; k++)
        {
            s += " ";
        }
        const char *x = s.c_str();
        waddstr(win, x);
        q++;
    }
    refresh();
    wattr_set(win, old_attr, old_pair, NULL);
}

void SheetView::tekeninh(Sheet *sheet)
{
    attr_t old_attr; /* Huidige settings onthouden */
    short old_pair;
    wattr_get(win, &old_attr, &old_pair, NULL);
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j <= 80; j++)
        {
            wmove(win, i, j);
            if ((j - 2) % 8 == 0 && j > 7 && i > 0)
            {
                if(cursor.at(0)+1 == i && cursor.at(1)*8+10 == j){
                    wattron(win, A_STANDOUT);
                }
                Cell *d = sheet->getCell(i - 1, (j - 8) / 8);
                string test = d->getString();
                const char *c = test.c_str();
                waddstr(win, c);
                wattr_set(win, old_attr, old_pair, NULL);
                refresh();
            }
        }
    }
}

std::vector<int> SheetView::getCursor()
{
    return cursor;
}

void SheetView::setCursor(std::vector<int> cur)
{
    cursor = cur;
    wmove(win, 1+cur.at(0), 10+cur.at(1)*8);
    refresh();
}

char SheetView::getchar(){
    int ch;
    keypad(win, TRUE);
    refresh();
    ch = wgetch(win);
    return ch;
}

WINDOW *SheetView::getWindow()
{
    return win;
}