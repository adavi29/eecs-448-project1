#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
//#include "Game.h"
using namespace std;

class Player{

private:
	Board m_ownBoard;
	Board m_oppBoard;

public:
	Player();
	~Player();

	Board& getOwnBoard();
//	void setOwnBoard(Board* newOwnBoard);
	Board& getOppBoard();
//	void setOppBoard(Board* newOwnBoard);


};

#endif
