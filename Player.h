#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
using namespace std;

class Player
{
public:
	Board& getOwnBoard();
//	void setOwnBoard(Board* newOwnBoard);
	Board& getOppBoard();
//	void setOppBoard(Board* newOwnBoard);

private:
	Board m_ownBoard;
	Board m_oppBoard;
};

#include "Player.hpp"
#endif
