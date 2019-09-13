#ifndef SHIPS_H
#define SHIPS_H

#include "Board.h"
#include "Ships.cpp"

using namespace std;

class Ships
{

public:

	Ship(int numShips);
	void decreaseSize(int ship);
	Bool isSunk(int ship);
	void announce(int ship);

private:
	  int m_ship1=0;
	  int m_ship2=0;
	  int m_ship3=0;
	  int m_ship4=0;
	  int m_ship5=0;
};

#endif
