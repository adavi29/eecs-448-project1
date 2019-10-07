// -*- C++ -*-
/**
 *   @author Runtime Terrors:
 *               Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *               Jacob Swearingen, Chongzhi Gao
 *   @date 9/16/19
 *   @file Board.h
 *   @brief lists all methods for interacting with the game board
 */

#ifndef BOARD_H
#define BOARD_H

#include<string>
#include<iostream>

class Board {

	private:

		std::string** m_board;

	public:

		/**
		 * @pre  Called to create board object
		 * @post Initializes 2D array and sets all entries to a space
		 */
		Board();

		/**
		 * @pre  Called to delete object
		 * @post Deletes the 2D array
		 */
		~Board();

		/**
		 * @pre  Valid row and column number
		 * @param  integer denoting a column number
		 * @param  integer denoting a row number
		 * @return Std::String containing an entry
		 */
		std::string getEntryAtPosition(int column, int row);

		/**
		 * @pre Valid row and column number
		 * @post Sets array at given position to the new entry
		 * @param std::string entry for array
		 * @param  integer denoting a column number
		 * @param  integer denoting a row number
		 */
		void setEntryAtPosition(std::string entry, int column, int row);

		/**
		 * @post Prints content of 2D board array
		 */
		void printBoard();

};

#endif // BOARD_H_
