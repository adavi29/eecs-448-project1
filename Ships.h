/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date
 *   @file
 *   @brief 
 */
#ifndef SHIPS_H
#define SHIPS_H

#include <stdexcept>
#include<iostream>
using namespace std;

class Ships
{

public:
    /**
     * @pre
     * @post
     * @param
     * @return
     */
	Ships(int numShips);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
	void decreaseSize(int ship);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
	bool isSunk(int ship);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
	bool allSunk();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
	void announce(int ship);

private:
	  int m_ship1;
	  int m_ship2;
	  int m_ship3;
	  int m_ship4;
	  int m_ship5;
};

#endif
