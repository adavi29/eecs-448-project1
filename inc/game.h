// -*- C++ -*-
/**
 *   @author Runtime Terrors:
 *               Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *               Jacob Swearingen, Chongzhi Gao
 *           git-merge:
 *               Zach Pearson, Brian Clark, Finn Dobbs, Dalton Yoder
 *   @date 06 October 2019
 *   @file game.h
 *   @brief declares methods and member variables needed for game play
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "board.h"
#include "ships.h"

enum Directions {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum OpponentType {
	HUMAN,
	AI
};

enum Difficulty {
	EASY,
	REALISTIC,
	IMPOSSIBLE
};

class Game{

	private:

		int m_numShips;

		Directions userDirection;

		int arrCol;
		int arrRow;

		int AIDifficulty;

		double AIHits;
		double AIMisses;

		double player1Hits;
		double player1Misses;

		double player2Hits;
		double player2Misses;

		Ships* m_p1Ships;
		Ships* m_p2Ships;
		Ships* AI_Ships;

		Board* m_p1ownBoard;
		Board* m_p1oppBoard;
		Board* m_p2ownBoard;
		Board* m_p2oppBoard;
		Board* AI_ownBoard;
		Board* AI_oppBoard;

		int m_currentPlayer;
		OpponentType m_opponentType;

		int player1Choice;
		int player2Choice;

		bool p1_usedBigShot;
		bool p2_usedBigShot;

		bool p1_cheatedAlready;
		bool p2_cheatedAlready;

#if !defined(__APPLE__) && !defined(__linux__) && !defined (_WIN32)
		// Variable to control continue screen on unknown system types.
		std::string wait;
#endif

	public:

		/**
		 * @pre Successful initialization of program.
		 * @post a game object is created with private member variables set to 0
		 */
		Game();

		/**
		 * @pre a game object exists to delete
		 * @post the game object is deallocated
		 */
		~Game();

		/**
		 * @pre a game object exists
		 * @post game play happens in this method
		 */
		int run();

		/**
		 * @pre a game object exists
		 * @post each players' ships are placed on their respective boards
		 */
		void setup();

		/**
		 * @pre a game object exists
		 * @post boards are printed to the screen in order of opp board, then
		 *       own board
		 * @param ownBoard: a board pointer to the player's own board
		 * @param oppBoard: a board pointer to the opponent's board
		 */
		void printPlayerBoards(Board* ownBoard, Board* oppBoard);

		/**
		 * @pre a game object exists
		 * @post a player's own board is printed to terminal
		 * @param ownBoard: a board pointer to the player's own board
		 */
		void printOwnBoard(Board* ownBoard);

		/**
		 * @brief check if position is empty
		 * @pre a board object exists
		 * @post checks if a coordinate on the board is empty or not; used by
		 *       Setup method
		 * @param board: a board pointer pointing at the board you want to check
		 *               a position in
		 * @param row the row of the coordinate you want to check
		 * @param col the col of the coordinate you want to check
		 * @return true if the position on the board is empty; else false
		 */
		bool isAvailable(Board* board, int row, int col);

		/**
		 * @brief checks if up, down, left, right is available
		 * @pre a board object exists
		 * @post checks if the given ship can be placed in the spaces it needs
		 *       in the chosen direction (checks if the needed coordinates are
		 *       empty)
		 * @param board: a board pointer pointing at the board you want to check
		 *               a position in
		 * @param row: the row of the coordinate you want to check
		 * @param col: the col of the coordinate you want to chec
		 * @param shipNum: the number of the ship that will be added to the
		 *        board
		 * @param direction: the direction in which the ship will be placed.
		 * @return returns true if the ship can be placed on the board in the
		 *         specified direction; false otherwise
		 */
		bool CheckDirection(Board* board,
					  int row, int col,
					  int shipNum,
					  Directions direction);

		/**
		 * @pre board object exists
		 * @post a ship is added to the board
		 * @param ship: a std::string denoting the ship number that will be
		 *        placed on the board
		 * @param row: the user chosen initial row that the ship will be placed
		 * @param col: the user chosen initial column that the ship will be
		 *        placed
		 * @param direction: the user chosen direction in which the ship will be
		 *        placed
		 * @param player: the player who's board will be updated with a ship;
		 *        used in setup()
		 * @throw runtime error when orientation runs off the board or is full
		 */
		void addShiptoArray(std::string ship,
				    int row, int col,
				    Directions direction,
				    int player);

		/**
		 * @brief helper method for run()
		 * @pre board object exist
		 * @post prints board to the screen and handles user input when its
		 *       player AI's turn
		 * @return nothing
		 */
		void AITurn();

		/**
		 * @brief helper method for run()
		 * @pre board object exist
		 * @post prints board to the screen and handles user input when its
		 *       player 2's turn
		 * @return nothing
		 */
		void p1Turn();

		/**
		 * @post prints board to the screen and handles user input when its
		 *       player 2's turn
		 */
		void p2Turn();

		/**
		 * @brief clears the console and adds empty lines above so players
		 *        can't cheet
		 */
		void clearConsole();

		/**
		 * @pre A turn is active.
		 * @post gets good input from the user of a spefic row
		 * @return integer representing row
		 */
		int getUserRow();

		/**
		 * @pre A turn is active.
		 * @post gets good input from the user of a spefic column
		 * @return integer representing row
		 */
		int getUserCol();

		/**
		 * @pre board contains ships 1,2,3,4,5.
		 * @post checks if a coordinate on a board is a hit or miss
		 * @param Board - players board to check
		 * @param int row - row
		 * @param int col - column
		 * @return true for hit, false for miss
		 */
		bool isHit(Board* playerBoard, int row, int col);

		/**
		 * @pre a board object exists
		 * @post gets the user's coordinates to place a ship on the board and
		 *       verifies input
		 * @param currentPlayerBoard: denotes the current player
		 * @param shipNum: denotes the ship number
		 */
		void printCoordinateInteraction(Board* currentPlayerBoard, int shipNum);

		/**
		 * @pre a board object exists
		 * @post places ships on the board through the addShipToArray function
		 * @param ship: denotes ship number
		 * @param currentPlayerBoard: denotes the current player
		 */
		void shipPlacementInteraction(int ship, Board* currentPlayerBoard);

		/**
		 * @post prints to screen which player's turn it is
		 * @param player: the current player
		 */
		void printPlayerTurn(int player);

		/**
		 * @brief Prints possible directions to terminal
		 */
		void CheckDirections(Board* currentPlayerBoard, int shipNum);

		/**
		 * @brief Provides platform specific ways to pause the game withi
		 *        a plain C++ fallback if system calls are unavailable
		 *        (e.g. if we do not detect a known platform)
		 */
		void ContinuePause();

		/**
		 * @pre takes an integer and the board to be manipulated
		 * @brief Interacts with the user to set the ships
		 * @post none
		 */
		void SetUpShips(int ships, Board* currentPlayerBoard);

		/**
		* @pre none
		* @brief Asks the user for a valid row number
		* @post returns an integer
		*/
		int AskForPlacementRow();

		/**
		* @pre none
		* @brief Asks the user for a valid column letter
		* @post returns an integer
		*/
		int AskForPlacementCol();

		/**
		* @pre none
		* @brief Asks the user for a valid number of ships
		* @post returns an integer
		*/
		int AskForNumShips();

		/**
		* @pre takes an integer for the current player, the current ship, around
		*				the column and rows to place the ship
		* @brief sets the ship according to the size
		* @post none
		*/
		void setEntryWrapper(int player, std::string ship, int col, int row);

		/**
		* @pre takes the boards to be displayed
		* @brief displays the appropriate board for the current player
		* @post none
		*/
		void printPlayerBoardsSBS(Board* ownBoard, Board* oppBoard);

		/**
		* @pre none
		* @brief asks the user for the type of opponent, human or AI
		* @post returns an integer
		*/
		int AskPlayerType();

		/**
		* @pre none
		* @brief determines the difficulty of the AI
		* @post none
		*/
		void displayAImenu();

		/**
		* @pre none
		* @brief the easy shot for the AI player
		* @post none
		*/
		void AIEasyShot();

		/**
		* @pre none
		* @brief the medium shot for the AI player
		* @post none
		*/
		void AIMediumShot();

		/**
		* @pre none
		* @brief the hard shot for the AI player
		* @post none
		*/
		void AIHardShot();

		/**
		* @pre none
		* @brief displays player 1's interactive menu
		* @post none
		*/
		void displayPlayer1Menu();

		/**
		* @pre none
		* @brief displays player 1's interactive menu
		* @post none
		*/
		void displayPlayer2Menu();
};
#endif
