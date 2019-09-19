/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date
 *   @file
 *   @brief
 */
#ifndef GAME_H
#define GAME_H

#include "Board.h"
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
     * @pre
     * @post
     * @param
     * @return
     */
    Game();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    ~Game();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void run();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void setup();
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void printPlayerBoards(Board* ownBoard, Board* oppBoard);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void printOwnBoard(Board* ownBoard);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    int convertCol(string col);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    std::string convertStringToLower(string wordToConvert);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    //functions below will be used for adding ships to the board in setup()
    bool isAvailable(Board* board, int row, int col);//check if position is empty
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    bool checkUpDownLeftRight(Board* board, int row, int col, int shipNum, string direction);//checks if up, down, left, right is available
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void addShiptoArray(string ship, int row, int col, std::string direction, int player);//throws runtime error when orientation runs off the board or is full
    /**
     * @pre
     * @post
     * @param
     * @return
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
     * @pre
     * @post
     * @param
     * @return
     */
    void printCoordinateInteraction(Board* currentPlayerBoard, int shipNum);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void shipPlacementInteraction(int i, int j, Board* currentPlayerBoard);
    /**
     * @pre
     * @post
     * @param
     * @return
     */
    void printPlayerTurn(int player);
};
#endif
