
#include "SheetController.h"
#include "Sheet.h"
#include "SheetView.h"
#include <curses.h>
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
        case 'n':
            for (int i = 0; i < 24; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    string cellValue = sheet.getCell(i, j)->getString();
                    if (cellValue != "" && cellValue.at(0) == '=')
                    {
                        sheet.getCell(i, j)->setpointer(formule(sheet, cellValue));
                    }
                }
            }

            break;
        case '\n':
            celbewerking(sheet, s);
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
string SheetController::formule(Sheet &sheet, string cellValue)
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
        return berekenSom(sheet, range);
    }
    if (soort == "=AVG")
    {
        std::getline(ss, reference, ')');
        Range range(reference, &sheet);
        return berekenAvg(sheet, range);
    }
    if (soort == "=COUNT"){
        std::getline(ss, reference, ')');
        Range range(reference, &sheet);
        return berekenCount(sheet, range);
    }
        return nullptr;
}
// berekent de som van alle cellen in een Range
// als daarin formules zitten worden die eerst opnieuw berekent
string SheetController::berekenSom(Sheet &sheet, Range range)
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
                    value += stoi(formule(sheet, inh));
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
string SheetController::berekenAvg(Sheet &sheet, Range range)
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
                    value += stod(formule(sheet, inh));
                else
                    value += stod(inh.c_str());
                bool digit = true;
                for (int i = 0; i < inh.size(); i++)
                {
                    if (!(std::isdigit(inh.at(i)) || inh.at(i)==',' || inh.at(i)=='.'))
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
string SheetController::berekenCount(Sheet &sheet, Range range)
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
                    inh = formule(sheet, inh);
                bool digit = true;
                for (int i = 0; i < inh.size(); i++)
                {
                    if (!(std::isdigit(inh.at(i)) || inh.at(i)==',' || inh.at(i)=='.'))
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

void SheetController::celbewerking(Sheet &sheet, SheetView &s)
{
    //methode nieuwe window
    //int x = getchar
    std::vector<int> vec;
    WINDOW *win = s.getWindow();
    vec = s.getCursor();
    WINDOW *popup = newwin(3, 19, 1, 1);
    mvwin(popup, vec.at(0), vec.at(1) * 8 + 3);
    wmove(popup, 1, 1);
    wborder(popup, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(popup);
    // input van user naar cell en display ook pak oude en plaats
    string input = "";
    Cell *d = sheet.getCell(vec.at(0), vec.at(1));
    string inhoud = d->getString();
    wmove(popup, 1, 1);
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
    sheet.getCell(vec.at(0), vec.at(1))->setpointer(inhoud);
    s.tekenheaders();
}
