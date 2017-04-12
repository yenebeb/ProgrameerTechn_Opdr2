
#include "SheetController.h"
#include "Sheet.h"
#include "SheetView.h"
#include "Range.h"
#include <curses.h>
SheetController::SheetController(){

}

int SheetController::run(SheetView& s, Sheet& sheet){
	s.tekenheaders();
    s.tekeninh(&sheet);
    WINDOW *win = s.getWindow();
    int key;
    keypad(win, TRUE);
    int x = s.getchar();

	while(x != 'q'){

		switch(x)
		{
            case 'n':
                somberekenen(sheet, s);
            break;
            case '\n':
                celbewerking(sheet, s);
            break;
			case KEY_UP:
            case KEY_DOWN:
            case KEY_RIGHT:
            case KEY_LEFT:
            	moveCursor(x, s);
            break;
		}
        s.tekeninh(&sheet);

		x = s.getchar();
	}
}

void SheetController::moveCursor(int x, SheetView& s){
    std::vector<int> vec;
        
	switch(x)
	{      
		case KEY_UP:
        	vec = s.getCursor();
        	if(vec.at(0)>0) vec.at(0)--;
        	s.setCursor(vec);
        	break;
        case KEY_DOWN:
        	vec = s.getCursor();
        	if(vec.at(0)<22) vec.at(0)++;
        	s.setCursor(vec);
        	break;
        case KEY_RIGHT:
        	vec = s.getCursor();
        	if(vec.at(1)<8) vec.at(1)++;
        	s.setCursor(vec);
        	break;
        case KEY_LEFT:
        	vec = s.getCursor();
        	if(vec.at(1)>0) vec.at(1)--;
        	s.setCursor(vec);
        	break;
    }
    return;

}

void SheetController::somberekenen(Sheet& sheet, SheetView& s){
    
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
                     if(inh != "")
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

}

void SheetController::celbewerking(Sheet& sheet, SheetView& s){
    //methode nieuwe window
    //int x = getchar 
    std::vector<int> vec;
    WINDOW* win = s.getWindow();
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
    int key;
    while ((key = wgetch(win)) != '\n')
    {
        wmove(popup, 1, 1);
        c ="                 ";
        waddstr(popup, c);
        if (key == KEY_BACKSPACE)
        {
            if(inhoud.size()){
                inhoud.pop_back();
            }
        }
            else if(inhoud.size()< 17)
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

}
