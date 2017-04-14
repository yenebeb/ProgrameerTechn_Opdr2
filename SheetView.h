#ifndef SHEETVIEW_H
#define SHEETVIEW_H

#include <curses.h>
#include "Sheet.h"
#include <vector>

class SheetView {
public:
	SheetView(int lines, int cols);
	//~SheetView();
	// tekent headers van sheet
	void tekenheaders();
	// tekent inhoud van sheet
	void tekeninh(Sheet* sheet);
	// tekent cursor sheet
	void tekencurs();

	// returns plaats van cursor
	std::vector<int> getCursor(); 
	int getchar();
	// zet cursor op plaats vec
	void setCursor(std::vector<int> vec);
	// returns window
	WINDOW* getWindow();
	

private:
	WINDOW *win;
	std::vector<int> cursor = {0,0};

};

#endif //SHEETVIEW