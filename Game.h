/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date 9/19/19
 *   @file Game.h
 *   @brief declares methods and member variables needed for game play
 */
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Ships.h"
#include <string>
#include <iostream>
using namespace std;

class Game{

  private:
    int m_numShips;

    int userRow;
    string userCol;
    string userDirection;

    int arrCol;
    int arrRow;

    Ships* m_p1Ships;
    Ships* m_p2Ships;


    Board* m_p1ownBoard;
    Board* m_p1oppBoard;
    Board* m_p2ownBoard;
    Board* m_p2oppBoard;

    int m_currentPlayer;

    string letsPlay;
    string p1Text;
    string p2Text;
    string wait;

  public:

    /**
     * @pre none
     * @post a game object is created with private member variables set to 0.
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
    void run();
    /**
     * @pre a game object exists
     * @post each players' ships are placed on their respective boards
     */
    void setup();
    /**
     * @pre a game object exists
     * @post boards are printed to the screen in order of opp board, then own board
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
     * @pre the user inputs a column letter
     * @post converts the user's inputted column letter (A-H) to a number that will correspond to the board array column
     * @param col: the letter the user inputs for the board column
     * @return returns the number that will correspond to the board array column
     */
    int convertCol(string col);
    /**
     * @pre a string is passed in
     * @post a word that is passed in is converted to all lowercase
     * @param wordToConvert: the word that will be converted to all lowercase
     * @return returns the parameter as a lowercase string
     */
    std::string convertStringToLower(string wordToConvert);
    /**
     * @pre a board object exists
     * @post checks if a coordinate on the board is empty or not; used by Setup method
     * @param board: a board pointer pointing at the board you want to check a position in
     * @param row: the row of the coordinate you want to check
     * @param col: the col of the coordinate you want to check
     * @return returns true if the position on the board is empty; false otherwise
     */
    bool isAvailable(Board* board, int row, int col);//check if position is empty
    /**
     * @pre a board object exists
     * @post checks if the given ship can be placed in the spaces it needs in the chosen direction (checks if the needed coordinates are empty)
     * @param board: a board pointer pointing at the board you want to check a position in
     * @param row: the row of the coordinate you want to check
     * @param col: the col of the coordinate you want to chec
     * @param shipNum: the number of the ship that will be added to the board
     * @param direction: the direction in which the ship will be placed.
     * @return returns true if the ship can be placed on the board in the specified direction; false otherwise
     */
    bool checkUpDownLeftRight(Board* board, int row, int col, int shipNum, string direction);//checks if up, down, left, right is available
    /**
     * @pre board object exists
     * @post a ship is added to the board
     * @param ship: a string denoting the ship number that will be placed on the board
     * @param row: the user chosen initial row that the ship will be placed
     * @param col: the user chosen initial column that the ship will be placed
     * @param direction: the user chosen direction in which the ship will be placed
     * @param player: the player who's board will be updated with a ship; used in setup()
     */
    void addShiptoArray(string ship, int row, int col, std::string direction, int player);//throws runtime error when orientation runs off the board or is full
    /**
     * @post prints the word battleship to the terminal screen
     */
    void printBattleship();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    //helper method for run()
    void p1Turn();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void p2Turn();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void clearConsole();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    int getUserRow();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    int getUserCol();
    /**
     * @pre
     * @post
     * @param
     * @param
     * @return
     */
    bool isHit(Board* playerBoard, int row, int col);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void printWinner(int player);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    string getFileContents(ifstream& File);
    /**
     * @pre a board object exists
     * @post gets the user's coordinates to place a ship on the board and verifies input
     * @param currentPlayerBoard: denotes the current player
     * @param shipNum: denotes the ship number
     * @return
     */
    void printCoordinateInteraction(Board* currentPlayerBoard, int shipNum);
    /**
     * @pre a board object exists
     * @post places ships on the board through the addShipToArray function
     * @param i: denotes ship number
     * @param j: denotes player number
     * @param currentPlayerBoard: denotes the current player
     */
    void shipPlacementInteraction(int i, int j, Board* currentPlayerBoard);
    /**
     * @post prints to screen which player's turn it is
     * @param player: the current player
     */
    void printPlayerTurn(int player);



};
#endif
