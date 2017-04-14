
#include "SheetController.h"
#include "Sheet.h"
#include "SheetView.h"
#include <curses.h>
#include <iostream>
#include <fstream>

using namespace std;
SheetController::SheetController()
{
}

int SheetController::run(SheetView &s, Sheet &sheet)
{
    s.tekenheaders(); // tekenheaders
    s.tekeninh(&sheet); // tekentinhoud
    WINDOW *win = s.getWindow(); // get window van sheetview
    int key;
    keypad(win, TRUE);
    int x = s.getchar();

    // de main loop, exit with q
    while (x != 'q')
    {

        switch (x)
        {
        case 'r':
            readfile(sheet, s);
            updateFormules(s, sheet);

            break;
        case 's':
            savefile(sheet, s);
            break;
        case '\n':
            celbewerking(sheet, s);
            updateFormules(s, sheet);
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

// update alle cellFormula
void SheetController::updateFormules(SheetView &s, Sheet &sheet){
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            string cellValue = sheet.getCell(i, j)->getString();
            if (cellValue != "" && cellValue.at(0) == '=')
            {   
                vector<int> vec;
                vec = s.getCursor();
                vector<CellAdress> vecCa;
                vecCa.push_back(CellAdress(vec.at(0) + 'A', vec.at(1) + 1));
                CellValueBase *y = new CellFormula<string>(cellValue, formule(sheet, cellValue, vecCa));
                sheet.getCell(i, j)->setpointer(y);
            }
        }
    }
}

// slaat de huidige toestand van het programma op 
void SheetController::savefile(Sheet & sheet, SheetView &s){
    filebuf fb;
    string file;
    prompt(sheet, s, file, true); // gebruiker krijgt prompt voor filenaam
    fb.open(file, ios::out); // opent file
    ostream os(&fb);
    sheet.serialize(os); 
}

// maakt sheet op basis van een file
void SheetController::readfile(Sheet & sheet, SheetView & s){
    int x = 0; // aantal kolommen
    int y = 0; // aantal rijen
    string file;
    prompt(sheet, s, file, true);
    ifstream myReadFile;
    myReadFile.open(file);

    if (myReadFile.is_open()) {
        myReadFile >> x; // update aantal kolommen vanuit file
        myReadFile >> y; // update aantal rijen vanuit file
        if(x > 0 && y > 0){
            Sheet s(x, y);
            s.deserialize(myReadFile);
            sheet = s; // update sheet
        }

    }
    myReadFile.close(); //close ifstream
} 

// laat nieuw scherm zien met een border.
// en een bewerkbare text &inhoud
// Als de bool file meegegeven is dan zal er 
// "write filename" in het scherm gezien laten worden
void SheetController::prompt(Sheet &sheet, SheetView &s, string & inhoud, bool file){
    vector<int> vec;
    WINDOW *win = s.getWindow();
    vec = s.getCursor();
    WINDOW *popup = newwin(3, 19, 1, 1); // maak nieuw window
    mvwin(popup, vec.at(0), vec.at(1) * 8 + 3);
    wmove(popup, 1, 1);
    wborder(popup, '|', '|', '-', '-', '+', '+', '+', '+'); // borders van nieuwe winow
    wrefresh(popup);

    // als popup bedoelt is voor het bewerken van een cel
    if(!file){
        Cell *d = sheet.getCell(vec.at(0), vec.at(1)); // haal Cell waarin nieuw scherm aangemaakt is op
        inhoud = d->getString(); // zet inhoud op cellwaarde
    }
    // anders
    else{
        inhoud = "write filename";
    }
    wmove(popup, 1, 1);
    inputPrompt(popup, win, inhoud); // invoer van popup
}

// regelt input voor nieuw input scherm
// dit scherm kan gesloten worden door op enter te drukken
void SheetController::inputPrompt(WINDOW* popup, WINDOW* win, string & inhoud){
    const char *c = inhoud.c_str(); // convert inhoud naar char*
    waddstr(popup, c); // drukt inhoud af in popupscherm
    wrefresh(popup);
    int key; // gedrukte toets
    while ((key = wgetch(win)) != '\n')
    {
        wmove(popup, 1, 1);
        c = "                 ";
        waddstr(popup, c);
        // als backspace wordt gedrukt
        // wordt er een letter weggehaald
        if (key == KEY_BACKSPACE)
        {
            if (inhoud.size())
            {
                inhoud.pop_back();
            }
        }
        else if (inhoud.size() < 17)
        {
            inhoud += key;
        }
        c = inhoud.c_str();
        wmove(popup, 1, 1);
        waddstr(popup, c);
        wrefresh(popup); // na elke toetsinvoer refresh popupscherm
    }
}

// verplaatsen van cursor
// dmv de pijltjes toetsen
void SheetController::moveCursor(int x, SheetView &s)
{
    vector<int> vec; //houd cursorplaats bij
    switch (x)
    {
    case KEY_UP:
        vec = s.getCursor();
        if (vec.at(0) > 0)
            vec.at(0)--;
        s.setCursor(vec);
        break;
    case KEY_DOWN:
        vec = s.getCursor();
        if (vec.at(0) < 22)
            vec.at(0)++;
        s.setCursor(vec);
        break;
    case KEY_RIGHT:
        vec = s.getCursor();
        if (vec.at(1) < 8)
            vec.at(1)++;
        s.setCursor(vec);
        break;
    case KEY_LEFT:
        vec = s.getCursor();
        if (vec.at(1) > 0)
            vec.at(1)--;
        s.setCursor(vec);
        break;
    }
    return;
}

// pakt als invoer een formule string
// bijv. "=SUM(A1:B5)" "=AVG(B1:B5)" "=COUNT(C2:D4)"
// en returnt daarna de uitgerekende waarde van
// die formule als een string
string SheetController::formule(Sheet &sheet, string cellValue, vector<CellAdress> vecCa)
{
    stringstream ss;
    ss.str(cellValue); // convert to stringstream
    string soort;
    getline(ss, soort, '('); //pakt het gedeeldte voor de (
    string reference;
    if (soort == "=SUM")
    {
        getline(ss, reference, ')');
        Range range(reference, &sheet); // maakt range aan
        vecCa.push_back(range.getBegin()); // push begin van range in vecCA
        return berekenSom(sheet, range, vecCa); // berekent som
    }
    if (soort == "=AVG")
    {
        getline(ss, reference, ')');
        Range range(reference, &sheet);// push begin van range in vecCA
        return berekenAvg(sheet, range, vecCa); // berekent gemiddelde
    }
    if (soort == "=COUNT")
    {
        getline(ss, reference, ')');
        Range range(reference, &sheet);// push begin van range in vecCA
        return berekenCount(sheet, range, vecCa); // berekent count
    }
    return nullptr;
}

// berekent de som van alle cellen in een Range
// als daarin formules zitten worden die eerst opnieuw berekent
// en returnt deze waarde als een string 
string SheetController::berekenSom(Sheet &sheet, Range range, vector<CellAdress> vecCa)
{
    RangeIterator rir = range.begin(); // begin iterator range
    RangeIterator rirEnd = range.end(); // end iterator range
    string inh = "";
    float value = 0; // getal waarmee wordt gerekent
    try
    {
        while (rir != rirEnd)
        {
            Cell *z = &*rir;
            inh = z->getString();
            if (inh != "")
            {
                if (inh.at(0) == '=')
                {
                    for (CellAdress res : vecCa)
                    {
                        if (rir.getCellAdress().getKolomnummer() == res.getKolomnummer() && rir.getCellAdress().getRijnummer() == res.getRijnummer())
                            return "ERR";
                    }
                    vecCa.push_back(rir.getCellAdress());
                    value += stof(formule(sheet, inh, vecCa));
                }
                else
                    value += stof(inh.c_str());
            }
            ++rir;
        }
        return to_string(value);
    }
    catch (exception &e)
    {
        return "ERR";
    }
}

// berekent het gemiddelde van alle cellen in een Range
// als daarin formules zitten worden die eerst opnieuw berekent
// en returnt deze waarde als een string
string SheetController::berekenAvg(Sheet &sheet, Range range, vector<CellAdress> vecCa)
{
    RangeIterator rir = range.begin();
    RangeIterator rirEnd = range.end();
    string inh = "";
    float value = 0;
    int count = 0;
    try
    {
        while (rir != rirEnd)
        {
            Cell *z = &*rir;
            inh = z->getString();
            if (inh != "")
            {
                if (inh.at(0) == '=')
                {
                    for (CellAdress res : vecCa)
                    {
                        if (rir.getCellAdress().getKolomnummer() == res.getKolomnummer() && rir.getCellAdress().getRijnummer() == res.getRijnummer())
                            return "ERR";
                    }
                    vecCa.push_back(rir.getCellAdress());
                    string form = formule(sheet, inh, vecCa);
                    if (form == "ERR")
                        return "ERR";
                    value += stof(form.c_str());
                    inh = form;
                }
                else
                {
                    value += stof(inh.c_str());
                }
                bool digit = true;
                for (int i = 0; i < inh.size(); i++)
                {
                    if (!(isdigit(inh.at(i)) || inh.at(i) == ',' || inh.at(i) == '.'))
                        digit = false;
                }
                if (digit)
                {
                    count++;
                }
            }
            ++rir;
        }
        return to_string((value / count));
    }
    catch (exception &e)
    {
        return "ERR";
    }
}

// telt hoeveel cellen exclusief nummers bevatten in een
// range en returnt deze waarde als een string
string SheetController::berekenCount(Sheet &sheet, Range range, vector<CellAdress> vecCa)
{
    RangeIterator rir = range.begin();
    RangeIterator rirEnd = range.end();
    string inh = "";
    int count = 0;
    try
    {
        while (rir != rirEnd)
        {
            Cell *z = &*rir;
            inh = z->getString();
            if (inh != "")
            {
                if (inh.at(0) == '=')
                {
                    for (CellAdress res : vecCa)
                    {
                        if (rir.getCellAdress().getKolomnummer() == res.getKolomnummer() && rir.getCellAdress().getRijnummer() == res.getRijnummer())
                            return "ERR";
                    }
                    vecCa.push_back(rir.getCellAdress());
                    inh = formule(sheet, inh, vecCa);
                }
                bool digit = true;
                for (int i = 0; i < inh.size(); i++)
                {
                    if (!(isdigit(inh.at(i)) || inh.at(i) == ',' || inh.at(i) == '.'))
                        digit = false;
                }
                if (digit)
                {
                    count++;
                }
            }
            ++rir;
        }
        return to_string(count);
    }
    catch (exception &e)
    {
        return "Err";
    }
}

// bewerkt cel, dmv nieuw scherm
void SheetController::celbewerking(Sheet &sheet, SheetView &s)
{
    vector<int> vec;
    string inhoud = "";
    vec = s.getCursor();
   

    prompt(sheet, s, inhoud, false);

    CellValueBase *y;
    // Als inhoud van cel '=' bevat, maak dan cellFormula
    if (inhoud != "" && inhoud.at(0) == '=')
    {
        vector<CellAdress> vecCa;
        vecCa.push_back(CellAdress(vec.at(0) + 'A', vec.at(1) + 1));
        y = new CellFormula<string>(inhoud, formule(sheet, inhoud, vecCa));
    }
    else
    {
        y = new CellValue<string>(inhoud);
    }
    sheet.getCell(vec.at(0), vec.at(1))->setpointer(y);
    s.tekenheaders();
}
