CC = g++

CompileParms = -std=c++11 -c

OBJS = Cell.o CellAdress.o CellValueBase.o Column.o Sheet.o Range.o main.o

opdr: $(OBJS)
	$(CC) -Wall $(OBJS) -o Spread

Cell.o: Cell.cc Cell.h
	$(CC) $(CompileParms) Cell.cc

CellAdress.o: CellAdress.cc CellAdress.h
	$(CC) $(CompileParms) CellAdress.cc

CellValueBase.o: CellValueBase.cc CellValueBase.h Cell.cc Cell.h
	$(CC) $(CompileParms) CellValueBase.cc

Column.o: Column.cc Column.h Cell.cc Cell.h 
	$(CC) $(CompileParms) Column.cc

Sheet.o: Sheet.cc Sheet.h Cell.cc Cell.h Column.cc Column.h
	$(CC) $(CompileParms) Sheet.cc

Range.o: Range.cc Range.h Sheet.h Sheet.cc CellAdress.h CellAdress.cc
	$(CC) $(CompileParms) Range.cc

main.o: main.cc Sheet.cc Sheet.h
	$(CC) $(CompileParms) main.cc