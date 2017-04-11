#ifndef SHEETVIEW_H
#define SHEETVIEW_H

#include <curses.h>
class SheetView {
public:
	SheetView(int lines, int cols);
	//~SheetView();
	void tekenheaders();
	void tekeninh();
	void tekencurs();
	void getcursor();
	void setcursor();
	WINDOW* getWindow();


private:
	WINDOW *win;


};

#endif //SHEETVIEW