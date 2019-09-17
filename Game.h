//Game.h

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

    //Player p1;
    //Player p2;

  public:

    Game();
    ~Game();
    void run();
    void setup();

    void printPlayerBoards(Board* ownBoard, Board* oppBoard);
    void printOwnBoard(Board* ownBoard);
    int convertCol(string col);
    std::string convertStringToLower(string wordToConvert);

//functions below will be used for adding ships to the board in setup()
    bool isAvailable(Board* board, int row, int col);//check if position is empty

    bool checkUpDownLeftRight(int row, int col, int shipNum, string direction);//checks if up, down, left, right is available

    void addShiptoArray(string ship, int row, int col, std::string direction, int player);//throws runtime error when orientation runs off the board or is full

    // use isAvailable() --will tell if position is open
    //if position is open, ask if user wants to place it up/down/left/right
    //then call checkUpDownLeftRight--checks if it will run off the board and if so, is false
    //if checkUpDownLeftRight returns false then tell user that direction is not possible
    //if true, addShiptoArray
    //if cant put in any direction: what do you do???

    void printBattleship();

    //helper method for run()
    void p1Turn();
    void p2Turn();
    void clearConsole();
    int getUserRow();
    int getUserCol();
    bool isHit(Board* playerBoard, int row, int col);
    void printWinner(int player);
    string getFileContents(ifstream& File);


};
#endif
