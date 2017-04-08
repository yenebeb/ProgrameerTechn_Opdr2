#include "Sheet.h"
#include <iostream>
int main(){
   Sheet sheet(5,5);
   std::string x = "5";
   Cell y = sheet.getCell(0,0);
   y.setpointer(x);
   unique_ptr<CellValueBase> test = move(y.readpointer());
   cout << test->stringValue();

}
