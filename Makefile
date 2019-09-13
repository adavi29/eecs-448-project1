battleship: main.o Board.o Game.o Ship.o
	g++ -std=c++11 -g -Wall main.o Board.o Game.o Ship.o -o battleship

main.o: main.cpp Game.h
	g++ -std=c++11 -g -Wall -c main.cpp

Game.o: Game.cpp Game.h Board.h Ship.h
	g++ -std=c++11 -g -Wall -c Game.cpp

Board.o: Board.cpp Board.h
	g++ -std=c++11 -g -Wall -c Board.cpp

Ship.o: Ship.cpp Ship.h
	g++ -std=c++11 -g -Wall -c Ship.cpp

clean:
	rm *.o battleship
