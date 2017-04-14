#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "CellAdress.h"
#include "SheetView.h"
#include "Sheet.h"
#include "SheetController.h"
#include <string>
#include <fstream>

#include <curses.h>

int main()
{
    
    // ui
     // sheet initialization
    Sheet sheet(24, 80);
    int k = 0;
    static const int lines(24);
    static const int cols(160);

    SheetView s(lines, cols);
    SheetController sc;
    sc.run(s, sheet);    

    WINDOW *win = s.getWindow();
    endwin();
    return 0;
    
}
