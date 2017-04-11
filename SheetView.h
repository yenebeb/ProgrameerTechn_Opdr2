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

	std::vector<int> getCursor();
	int getchar();
	void setCursor(std::vector<int> vec);
	WINDOW* getWindow();
	

private:
	WINDOW *win;
	std::vector<int> cursor = {0,0};

};

#endif //SHEETVIEW