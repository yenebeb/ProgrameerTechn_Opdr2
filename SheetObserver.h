#ifndef SHEETOBSERVER_H
#define SHEETOBSERVER_H

#include "Cell.h"
class Cell;
class SheetObserver {
public:
	virtual void cellChanged(const Cell &cell)
	{};

private:

};
#endif //SheetObser
