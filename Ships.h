
/*
@file Ships.h
*/

#ifndef SHIPS_H
#define SHIPS_H

#include <stdexcept>
#include<iostream>

using namespace std;

class Ships
{

public:

	Ships(int numShips);
	void decreaseSize(int ship);
	bool isSunk(int ship);

	bool allSunk();
	void announce(int ship);

private:
	  int m_ship1;
	  int m_ship2;
	  int m_ship3;
	  int m_ship4;
	  int m_ship5;
};

#endif
