#include "Sheet.h"
#include <iostream>
#include <sstream>
#include "Range.h"
int main(){

   Sheet sheet(5,5);

   for(int i = 0; i < 5; i++){
   		for(int j = 0; j < 5; j++){
   			    Cell* y = sheet.getCell(i,j);
				std::stringstream ss;
    			ss << i;
    			std::string s(ss.str());
   				std::string x = std::string(s);
   			   	
   			   	sheet.getCell(i,j)->setpointer(x);
   			   

   		}
   }
  

   for(int i = 0; i < 5; i++){
   		for(int j = 0; j < 5; j++){
   				Cell* z = sheet.getCell(i,j);
   			  	vector<Column*>::iterator l = sheet.begin();
   				unique_ptr<CellValueBase> test = move(z->readpointer());
			   	cout << test->stringValue() << " <<<< ";

   		}
   		cout << std::endl;
   }
   cout << std::endl;

   Range range(CellAdress('B',2),CellAdress('C',3), &sheet);
   char kolom = range.getBegin().getKolomnummer();
   int rij = range.getBegin().getRijnummer();

   cout << (int) kolom << rij << endl;
   Cell* z = range.getSheet()->getCell((int) kolom, rij);
   unique_ptr<CellValueBase> test = move(z->readpointer());
   cout << test->stringValue() << " <<<< ";


}
