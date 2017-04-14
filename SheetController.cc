
#include "SheetController.h"
#include "Sheet.h"
#include "SheetView.h"
#include <curses.h>
#include <iostream>
#include <fstream>
SheetController::SheetController()
{
}

int SheetController::run(SheetView &s, Sheet &sheet)
{
    s.tekenheaders();
    s.tekeninh(&sheet);
    WINDOW *win = s.getWindow();
    int key;
    keypad(win, TRUE);
    int x = s.getchar();


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
                std::vector<int> vec;
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
    std::filebuf fb;
    string file;
    prompt(sheet, s, file, true);
    fb.open(file, std::ios::out);
    std::ostream os(&fb);
    sheet.serialize(os);
}

// maakt sheet op basis van een file
void SheetController::readfile(Sheet & sheet, SheetView & s){
    int x =0;
    int y = 0;
    string file;
    prompt(sheet, s, file, true);
    ifstream myReadFile;
    myReadFile.open(file);
    if (myReadFile.is_open()) {
        myReadFile >> x;
        myReadFile >> y;

        cout << x;
        cout << y;
        if(x > 0 && y > 0){
            Sheet s(24, 80);
            s.deserialize(myReadFile);
            sheet = s;
        }

    }
}

// laat nieuw scherm zien
void SheetController::prompt(Sheet &sheet, SheetView &s, string & inhoud, bool file){
    std::vector<int> vec;
    WINDOW *win = s.getWindow();
    vec = s.getCursor();
    WINDOW *popup = newwin(3, 19, 1, 1);
    mvwin(popup, vec.at(0), vec.at(1) * 8 + 3);
    wmove(popup, 1, 1);
    wborder(popup, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(popup);
    if(!file){
        Cell *d = sheet.getCell(vec.at(0), vec.at(1));
        inhoud = d->getString();
    }
    else{
        inhoud = "write filename";
    }
    wmove(popup, 1, 1);
    inputPrompt(popup, win, inhoud);}

// regelt input voor nieuw scherm
void SheetController::inputPrompt(WINDOW* popup, WINDOW* win, string & inhoud){
    const char *c = inhoud.c_str();
    waddstr(popup, c);
    wrefresh(popup);
    int key;
    while ((key = wgetch(win)) != '\n')
    {
        wmove(popup, 1, 1);
        c = "                 ";
        waddstr(popup, c);
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
        wrefresh(popup);
    }
}

// verplaatsen van cursor
void SheetController::moveCursor(int x, SheetView &s)
{
    std::vector<int> vec;

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
// bijv. "=SUM(A1:B5)"
string SheetController::formule(Sheet &sheet, string cellValue, vector<CellAdress> vecCa)
{
    std::stringstream ss;
    ss.str(cellValue);
    std::string soort;
    std::getline(ss, soort, '('); //pakt het gedeeldte voor de (
    string reference;
    if (soort == "=SUM")
    {
        std::getline(ss, reference, ')');
        Range range(reference, &sheet);
        vecCa.push_back(range.getBegin());
        return berekenSom(sheet, range, vecCa);
    }
    if (soort == "=AVG")
    {
        std::getline(ss, reference, ')');
        Range range(reference, &sheet);
        return berekenAvg(sheet, range, vecCa);
    }
    if (soort == "=COUNT")
    {
        std::getline(ss, reference, ')');
        Range range(reference, &sheet);
        return berekenCount(sheet, range, vecCa);
    }
    return nullptr;
}

// berekent de som van alle cellen in een Range
// als daarin formules zitten worden die eerst opnieuw berekent
string SheetController::berekenSom(Sheet &sheet, Range range, vector<CellAdress> vecCa)
{
    RangeIterator rir = range.begin();
    RangeIterator rirEnd = range.end();
    string inh = "";
    int value = 0;
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
                    value += stoi(formule(sheet, inh, vecCa));
                }
                else
                    value += stoi(inh.c_str());
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
string SheetController::berekenAvg(Sheet &sheet, Range range, vector<CellAdress> vecCa)
{
    RangeIterator rir = range.begin();
    RangeIterator rirEnd = range.end();
    string inh = "";
    double value = 0;
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
                    value += stod(form.c_str());
                    inh = form;
                    //    CellValueBase *z = new CellValue<string>(inh);
                    //   sheet.getCell(7, 7)->setpointer(z);
                }
                else
                {
                    value += stod(inh.c_str());
                }
                bool digit = true;
                for (int i = 0; i < inh.size(); i++)
                {
                    if (!(std::isdigit(inh.at(i)) || inh.at(i) == ',' || inh.at(i) == '.'))
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
// range
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
                    if (!(std::isdigit(inh.at(i)) || inh.at(i) == ',' || inh.at(i) == '.'))
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
    std::vector<int> vec;
    string inhoud = "";
    vec = s.getCursor();
   

    prompt(sheet, s, inhoud, false);

    CellValueBase *y;
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
    // input van user naar cell en display ook pak oude en plaats
