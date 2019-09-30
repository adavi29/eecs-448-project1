/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date 2019 09 20
 *   @file Ships.cpp
 *   @brief implements methods in Ships.h
 */
#include "ships.h"

Ships::Ships(int numShips){
	m_ship1=-1;//initialize ship variables in case they are not assigned a value below
	m_ship2=-1;
	m_ship3=-1;
	m_ship4=-1;
	m_ship5=-1;

	if((numShips <6)&&(numShips >0)){
		if(numShips>0) {
			m_ship1 = 1;
		}
		if(numShips>1) {
			m_ship2 = 2;
		}
		if(numShips>2) {
			m_ship3 = 3;
		}
		if(numShips>3) {
            m_ship4 = 4;
		}
		if(numShips>4){
			m_ship5 = 5;
		}
	}
}

void Ships::decreaseSize(int ship) {
	if(isSunk(ship) != true) {
		  if(ship == 1) {
		    m_ship1--;
		  }
			if(ship == 2) {
				m_ship2--;
			}
			if(ship == 3) {
				m_ship3--;
			}
			if(ship == 4) {
				m_ship4--;
			}
			if(ship == 5) {
				m_ship5--;
			}

			if(isSunk(ship)){
				announce(ship);
			}
	} else {
     throw(std::runtime_error("cannot decrease length; ship is already sunk"));
	}
}

bool Ships::isSunk(int ship){
		   if(ship ==1){
		     return (m_ship1 <= 0);
		   }

			 else if(ship ==2){
				 return (m_ship2 <= 0);
			 }

			 else if(ship ==3){
				 return(m_ship3 <= 0);
			 }

			 else if(ship ==4){
				 return(m_ship4 <= 0);
			 }

			 else{//if ship = 5
				 return(m_ship5 <= 0);
			 }
}

bool Ships::allSunk()
{
	if ((m_ship1 <= 0) && (m_ship2 <= 0) && (m_ship3 <= 0) && (m_ship4 <= 0) && (m_ship5 <= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Ships::announce(int ship){
	cout << "You've sunk ship "<<ship<<"!\n";
}
