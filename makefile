# Project1 Makefile Runtime Terrors
prog: main.o Board.o Game.o Ships.o
	g++ -std=c++11 -g -Wall main.o Board.o Game.o Ships.o -o prog

main.o: main.cpp Board.h Game.h Ships.h
	g++ -std=c++11 -g -Wall -c main.cpp

Board.o: Board.h Board.cpp
	g++ -std=c++11 -g -Wall -c Board.cpp

Game.o: Game.h Game.cpp
	g++ -std=c++11 -g -Wall -c Game.cpp

Ships.o: Ships.h Ships.cpp
	g++ -std=c++11 -g -Wall -c Ships.cpp

clean:
	rm *.o prog
