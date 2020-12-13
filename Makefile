all: michelin test

michelin: json.o michelin.o fdijkstra.o
	g++ -o michelin json.o michelin.o fdijkstra.o

json.o: json.c
	g++ -o json.o -c json.c -W -Wall -ansi -pedantic -std=c++11

michelin.o: michelin.cpp json.h fdijkstra.h
	g++ -o michelin.o -c michelin.cpp -W -Wall -ansi -pedantic -std=c++11

fdijkstra.o: fdijkstra.cpp
	g++ -o fdijkstra.o -c fdijkstra.cpp -W -Wall -ansi -pedantic -std=c++11
	
test: json.o test.o fdijkstra.o
	g++ -o test json.o test.o fdijkstra.o

test.o: test.cpp json.h
	g++ -o test.o -c test.cpp -W -Wall -ansi -pedantic -std=c++11
