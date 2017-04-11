
#include "SheetController.h"
#include "Sheet.h"
#include "SheetView.h"
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
            case 'c':
            break;
            case '\n':
                
                //celbewerking
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

void SheetController::celbewerking(int x, SheetView& s){
    //methode nieuwe window
    //int x = getchar 

    while(x != '\n'){

        switch(x)
}
