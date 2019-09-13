Ship(int numShips){
	if(numShips <6) {
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
}


void decreaseSize(int ship){
		  if((ship == 1)&&(isSunk(ship) != true)) {
		    m_ship1--;
				if(isSunk(ship)){
					announce(ship);
				}
		  }
			if((ship == 2)&&(isSunk(ship) != true)){
				m_ship2--;
				if(isSunk(ship)){
					announce(ship);
				}
			}
			if((ship == 3)&&(isSunk(ship) != true)){
				m_ship3--;
				if(isSunk(ship)){
					announce(ship);
				}
			}
			if((ship == 1)&&(isSunk(ship) != true)){
				m_ship4--;
				if(isSunk(ship)){
					announce(ship);
				}
			}
			if((ship == 1)&&(isSunk(ship) != true)){
				m_ship5--;
				if(isSunk(ship)){
					announce(ship);
				}
			}
		}

Bool isSunk(int ship){
		   if(ship ==1){
		     if(m_ship1 == 0){
		       return true
		     }
		   }
			 if(ship ==2){
				 if(m_ship1 == 0){
					 return true
				 }
			 }
			 if(ship ==2){
				 if(m_ship1 == 0){
					 return true
				 }
			 }
			 if(ship ==1){
				 if(m_ship1 == 0){
					 return true
				 }
			 }
			 if(ship ==1){
				 if(m_ship1 == 0){
					 return true
				 }
			 }
		 }

void announce(int ship){
	cout << "You've sunk ship " + ship + "!";
}
