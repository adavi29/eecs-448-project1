#include "Ships.h"


Ship(int numShips){
	if((numShips <6)||(numShips > 0)) {
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
			m_ship4 = 4
		}
		if(numShips>4){
			m_ship5 = 5;
		}
	}
	else{
		throw(std::runtime_error("cannot decrease length; ship is already sunk");
	}
}


void decreaseSize(int ship) {
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
		}
		else throw(std::runtime_error("cannot decrease length; ship is already sunk");
	}

Bool isSunk(int ship){
		   if(ship ==1){
		     return (m_ship2 <= 0);
		   }

			 if(ship ==2){
				 return (m_ship2 <= 0);
			 }

			 if(ship ==3){
				 return(m_ship2 <= 0);
			 }

			 if(ship ==4){
				 return(m_ship2 <= 0);
			 }

			 if(ship ==5){
				 return(m_ship2 <= 0);
			 }
		 }

void announce(int ship){
	cout << "You've sunk ship " + ship + "!";
}
