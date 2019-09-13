battleship: main.o Board.o
	g++ -std=c++11 -g -Wall main.o Board.o -o battleship

main.o: main.cpp Board.cpp Board.h
	g++ -std=c++11 -g -Wall -c main.cpp


Board.o: Board.cpp Board.h
	g++ -std=c++11 -g -Wall -c Board.cpp

clean:
	rm *.o battleship
