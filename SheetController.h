#ifndef SHEETCONTROLLER_H
#define SHEETCONTROLLER_H

#include "SheetView.h"
#include "Sheet.h"
#include <string>
#include "Range.h"

class SheetController{
public:
	// default constructor
	SheetController();

	// main loop om het programma te runnen
	int run(SheetView& s, Sheet& sheet);

	// method om de cursor te bewegen
	// where x = lastpressed button
	void moveCursor(int x, SheetView& s); 

	// methode om een cel te kunnen bewerken
	void celbewerking(Sheet& sheet, SheetView& s);
	
	// methode om de huidige toestand van het programma op te slaan
	void savefile(Sheet& sheet, SheetView & s);
	// methode om een nieuwe sheet te maken vanuit een file
	void readfile(Sheet& sheet, SheetView & s);
	// methode die input voor popup regelt
	void inputPrompt(WINDOW* popup, WINDOW* win, string & inhoud);
	// methode die popup genereert
	void prompt(Sheet &sheet, SheetView &s, string & string, bool file);
	// methode om alle formules te updaten
	void updateFormules(SheetView &s, Sheet &sheet);


	// Methode die juiste formule bepaalt
	std::string formule(Sheet &sheet, string value, vector<CellAdress> vecCa);
	// somberekeningen
	std::string berekenSom(Sheet &sheet, Range range,vector<CellAdress> vecCa);
	// berekent gemiddelde
	std::string berekenAvg(Sheet &sheet, Range range, vector<CellAdress> vecCa);
	// berekent aantal cellen met getallen
	std::string berekenCount(Sheet &sheet, Range range, vector<CellAdress> vecCa);
private:
	
	
};

#endif //SHEETCONROLLER
