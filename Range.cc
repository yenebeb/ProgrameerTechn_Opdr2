#include "Range.h"

Range::Range(){

}

Range::Range(CellAdress ca1, CellAdress ca2, Sheet *sh){
    BeginCellAdress = ca1;
    EndCellAdress = ca2;
    sheet = sh;
}