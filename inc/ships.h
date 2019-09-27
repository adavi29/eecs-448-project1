/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date 2019 09 20
 *   @file Ships.h
 *   @brief Creates the "fleet" for the game and keeps track of each ships "size", or remaining health
 */

#ifndef SHIPS_H
#define SHIPS_H

#include <stdexcept>
#include <iostream>

class Ships {

	public:

		/**
		 * @pre none
		 * @post initializes ships
		 * @param numShips
		 * @return none
		 */
		Ships(int numShips);

		/**
		 * @pre Ships(int numShips) must have been called
		 * @post decreases "size" which is essentially the health of a ship
		 * @param int ship is the number of the ship, equivalent to its original size
		 * @return none
		 */
		void decreaseSize(int ship);

		/**
		 * @pre Ships(int numShips) must have been called
		 * @post returns true if size of given ship is 0; also couts a sunk message
		 * @param int ship is the number of the ship, equivalent to its original size
		 * @return true if size is 0, false if size is not 0
		 */
		bool isSunk(int ship);

		/**
		 * @pre Ships(int numShips) must have been called
		 * @post returns true if all ships are sunk and false otherwise
		 * @param none
		 * @return true if size of all ships >= 0, false otherwise
		 */
		bool allSunk();

		/**
		 * @pre Ships(int numShips)must have been called
		 * @post couts to terminal when a ship has been sunk, and which ship it was
		 * @param int ship is the number of the ship, equivalent to its original size
		 * @return none
		 */
		void announce(int ship);

	private:

		int m_ship1;
		int m_ship2;
		int m_ship3;
		int m_ship4;
		int m_ship5;

};

#endif // SHIPS_H_
