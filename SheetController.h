#ifndef SHEETCONTROLLER_H
#define SHEETCONTROLLER_H

#include "SheetView.h"
#include "Sheet.h"
#include <string>
#include "Range.h"

class SheetController{
public:
	SheetController();
	int run(SheetView& s, Sheet& sheet);
	void moveCursor(int x, SheetView& s); 
	void celbewerking(Sheet& sheet, SheetView& s);
	void savefile(Sheet& sheet, SheetView & s);
	void readfile(Sheet& sheet, SheetView & s);
	void inputPrompt(WINDOW* popup, WINDOW* win, string & inhoud);
	void prompt(Sheet &sheet, SheetView &s, string & file);

	//string somberekenen(Sheet& sheet, int y, int x);
	std::string formule(Sheet &sheet, string value);
	std::string berekenSom(Sheet &sheet, Range range);
	std::string berekenAvg(Sheet &sheet, Range range);
	std::string berekenCount(Sheet &sheet, Range range);
private:
	
	
};

#endif //SHEETCONROLLER
