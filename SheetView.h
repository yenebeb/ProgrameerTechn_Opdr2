#ifndef SHEETVIEW_H
#define SHEETVIEW_H

#include <curses.h>
#include "Sheet.h"
#include <vector>
class SheetView {
public:
	SheetView(int lines, int cols);
	//~SheetView();
	void tekenheaders();
	void tekeninh(Sheet* sheet);
	void tekencurs();
	std::vector<int> getcursor();
	void setcursor();
	char getchar();
	WINDOW* getWindow();
	

private:
	WINDOW *win;
	std::vector<int> cursor = {1,10};

};

#endif //SHEETVIEW