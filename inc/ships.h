// -*- C++ -*-
/**
 * @author Runtime Terrors:
 *             Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *             Jacob Swearingen, Chongzhi Gao
 *         git-merge:
 *             Zach Pearson
 *	       Brian Clark
 *	       Finn Dobbs
 *	       Dalton Yoder
 * @date 06 October 2019
 * @file ships.h
 * @brief Creates the "fleet" for the game;
 *        keeps track of each ship's "size", or remaining health
 */

#ifndef SHIPS_H
#define SHIPS_H

#include <stdexcept>
#include <iostream>

enum ShipSize {
	NOSHIP,     // 0
	SUBMARINE,  // 1
	DESTROYER,  // 2
	CRUISER,    // 3
	BATTLESHIP, // 4
	CARRIER,    // 5
};

class Ships {

	public:

		/**
		 * @post initializes ships
		 * @param numShips
		 */
		Ships(int numShips);

		/**
		 * @pre Ships(int numShips) must have been called
		 * @post decreases "size" which is essentially the health of a ship
		 * @param int ship is the number of the ship, equivalent to its
		 *        original size
		 */
		void decreaseSize(int ship);

		/**
		 * @pre Ships(int numShips) must have been called
		 * @post returns true if size of given ship is 0; also couts a
		 *       sunk message
		 * @param int ship is the number of the ship, equivalent to its
		 *        original size
		 * @return true if size is 0, false if size is not 0
		 */
		bool isSunk(int ship);

		/**
		 * @pre Ships(int numShips) must have been called
		 * @post returns true if all ships are sunk and false otherwise
		 * @return true if size of all ships >= 0, false otherwise
		 */
		bool allSunk();

		/**
		 * @pre Ships(int numShips)must have been called
		 * @post couts to terminal when a ship has been sunk
		 *       and which ship it was
		 * @param int ship is the number of the ship, equivalent to its
		 *        original size
		 */
		void announce(int ship);

	private:

		int m_ship[5];

};

#endif // SHIPS_H_
