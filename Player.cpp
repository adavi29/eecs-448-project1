
#include "Player.h"
#include "Board.h"
//#include "Game.h"


	Player::Player()
	{

	}



	Board& Player::getOwnBoard(){
		return(m_ownBoard);
	}

	Board& Player::getOppBoard(){
		return(m_oppBoard);
	}

	Player::~Player()
	{

	}



//experimental setter functions
//use at own risk
//probably will throw up errors?
//I made them take pointers as parameters to ensure that it's a deep copy
//without the pointer it would be a shallow copy, right?
/*
	void setOwnBoard(Board* newOwnBoard){
		m_ownBoard = newOwnBoard;
	};

	void setOppBoard(Board* newOwnBoard){
		m_oppBoard = newOwnBoard;
	};
*/
