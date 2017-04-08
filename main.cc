#include "Sheet.h"
#include <iostream>
#include <sstream>
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
 

}
