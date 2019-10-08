/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @author git-merge (Dalton Yoder)
 *   @date 2019 09 20
 *   @file Ships.cpp
 *   @brief implements methods in ships.h
 */

#include "ships.h"

Ships::Ships(int numShips) {

	//initialize ship variables in case they are not assigned a value below
	//TODO: Don't declare ships until they are needed.
	//10/8: Temporary workaround until we can figure this out. -Dalton
	for(int s = 0 ; s < 5 ; s++) { m_ship[s] = -1;}

	if((numShips < 6) && (numShips > 0)) {
		for(int i = 1; i <= numShips ; i++) {
			m_ship[i-1] = i;
		}
	}
}

void Ships::decreaseSize(int ship) {
	if(isSunk(ship) != true) {
		m_ship[ship-1] = m_ship[ship-1] - 1;
		if(isSunk(ship)) {
			announce(ship);
		}
	} else {
		throw(std::runtime_error("Cannot decrease length; ship already sunk."));
	}
}

bool Ships::isSunk(int ship) {
	return (m_ship[ship-1] <= 0);
}

bool Ships::allSunk() {
	int loop = 1;
	while(loop <= 5) {
		if(m_ship[loop-1]>0){
			return false;
		}
		loop++;
	}
	return true;
}

void Ships::announce(int ship) {
	if(ship == 1) {
		std::cout<<"You've sunken the Submarine!\n";
	} else if(ship == 2) {
		std::cout<<"You've sunken the Destroyer!\n";
	} else if(ship == 3) {
		std::cout<<"You've sunken the Cruiser!\n";
	} else if(ship == 4) {
		std::cout<<"You've sunken the Battleship!\n";
	} else {
		//ship == 5
		std::cout<<"You've sunken the Carrier!\n";
	}

}
