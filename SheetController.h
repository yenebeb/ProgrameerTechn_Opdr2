#ifndef SHEETCONTROLLER_H
#define SHEETCONTROLLER_H

#include "SheetView.h"
#include "Sheet.h"

class SheetController{
public:
	SheetController();
	int run(SheetView& s, Sheet& sheet);
	void moveCursor(int x, SheetView& s); 
	void celbewerking(Sheet& sheet, SheetView& s);
	void somberekenen(Sheet& sheet, SheetView& s);
private:
	
	
};

#endif //SHEETCONROLLER