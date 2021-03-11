
output: main.o NPuzzle.o
	g++ main.o NPuzzle.o -o output

main.o: main.cpp
	g++ -c main.cpp

NPuzzle.o: NPuzzle.cpp NPuzzle.h
	g++ -c NPuzzle.cpp

clean:
	rm *.o output
