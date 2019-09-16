<<<<<<< HEAD
=======
/*
@file Ships.h
*/
>>>>>>> aa5d6fc302e3e6a18d8b9042b872d4d1678ced7f
#ifndef SHIPS_H
#define SHIPS_H

#include <stdexcept>
<<<<<<< HEAD
#include<iostream>
=======
>>>>>>> aa5d6fc302e3e6a18d8b9042b872d4d1678ced7f

using namespace std;

class Ships
{

public:

	Ships(int numShips);
	void decreaseSize(int ship);
	bool isSunk(int ship);
<<<<<<< HEAD
	bool allSunk();
=======
>>>>>>> aa5d6fc302e3e6a18d8b9042b872d4d1678ced7f
	void announce(int ship);

private:
	  int m_ship1;
	  int m_ship2;
	  int m_ship3;
	  int m_ship4;
	  int m_ship5;
};

#endif
