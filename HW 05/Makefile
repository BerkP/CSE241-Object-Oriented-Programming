
output: driver.o AbstractBoard.o BoardArray1D.o BoardArray2D.o BoardVector.o globalFunc.o
	g++ driver.o AbstractBoard.o BoardArray1D.o BoardArray2D.o BoardVector.o globalFunc.o -o output

driver.o: driver.cpp
	g++ -c driver.cpp

AbstractBoard.o: AbstractBoard.cpp AbstractBoard.h
	g++ -c AbstractBoard.cpp

BoardArray1D.o: BoardArray1D.cpp BoardArray1D.h
	g++ -c BoardArray1D.cpp

BoardArray2D.o: BoardArray2D.cpp BoardArray2D.h
	g++ -c BoardArray2D.cpp

BoardVector.o: BoardVector.cpp BoardVector.h
	g++ -c BoardVector.cpp

globalFunc.o: globalFunc.cpp globalFunc.h
	g++ -c globalFunc.cpp

clean:
	rm *.o output
