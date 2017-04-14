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

// tekent de headers van sheet
void SheetView::tekenheaders()
{
    int sideHeaderInt = 1;
    char topHeaderChar = 'A';
    const char *topHeader = &topHeaderChar;

    attr_t old_attr; /* Huidige settings onthouden */
    short old_pair;
    wattr_get(win, &old_attr, &old_pair, NULL);
    wmove(win, 0, 0);
    waddstr(win, "        "); // hoekje links boven
    wattron(win, A_STANDOUT);

    //teken de top header
    for (int j = 0; j < 80; j++)
    {
        wmove(win, 0, j);
        if (j % 8 == 4 && j > 4)
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
        s += to_string(sideHeaderInt);
        for (int k = s.size(); k < 8; k++)
        {
            s += " ";
        }
        const char *x = s.c_str();
        waddstr(win, x);
        sideHeaderInt++;
    }
    refresh();
    wattr_set(win, old_attr, old_pair, NULL);
}

// tekent inhoud van cellen op het scherm
void SheetView::tekeninh(Sheet *sheet)
{
    attr_t old_attr; /* Huidige settings onthouden */
    short old_pair;
    wattr_get(win, &old_attr, &old_pair, NULL);
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            wmove(win, i, j);
            if ((j) % 8 == 0 && j > 6 && i > 0)
            {
                if (cursor.at(0) + 1 == i && cursor.at(1) * 8 + 8 == j)
                {
                    wattron(win, A_STANDOUT);
                }
                Cell *d = sheet->getCell(i - 1, (j - 8) / 8); // getcell op huidige plaats
                string inhoud = d->getString().substr(0,8); //ophalen en afkappen na 8 tekens
                
                // als string inhoud niet leeg is, en begint met =
                // getCalcString
                if(inhoud != "" && inhoud.at(0) == '='){
                    inhoud = d->getCalcString().substr(0,8); 
                }
                for(int k = inhoud.size(); k < 6; k++){ // vult de string met spaties aan de voorkant als die minder dan 6 characters lang is
                    inhoud = " "+ inhoud;
                }

                for (int k = inhoud.size(); k < 8; k++) // vult de string met spaties aan de achterkant als die minder dan 8 characters lang is
                {
                    inhoud += " ";
                }
                const char *c = inhoud.c_str();
                waddstr(win, c);
                wattr_set(win, old_attr, old_pair, NULL);
                refresh();
            }
        }
    }
    wmove(win, 1 + cursor.at(0), 8 + cursor.at(1) * 8);
}

// returns de huidige locatie van de cursor
std::vector<int> SheetView::getCursor()
{
    return cursor;
}

// zet de cursor op nieuwe locatie
// cur
void SheetView::setCursor(std::vector<int> cur)
{
    cursor = cur;
    wmove(win, 1 + cur.at(0), 8 + cur.at(1) * 8);
    refresh();
}

// lees character van keypad
// returns int waarde van de character
int SheetView::getchar()
{
    int ch;
    keypad(win, TRUE);
    refresh();
    ch = wgetch(win);
    return ch;
}

// returns window
WINDOW *SheetView::getWindow()
{
    return win;
}