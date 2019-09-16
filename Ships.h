/*
@file Ships.h
*/
#ifndef SHIPS_H
#define SHIPS_H

#include <stdexcept>

using namespace std;

class Ships
{

public:

	Ship(int numShips);
	void decreaseSize(int ship);
	bool isSunk(int ship);
	void announce(int ship);

private:
	  int m_ship1=-1;
	  int m_ship2=-1;
	  int m_ship3=-1;
	  int m_ship4=-1;
	  int m_ship5=-1;
};

#endif
