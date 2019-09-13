//Game.h

#ifndef GAME_H
#define GAME_H

#include "Board.h"
//#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

class Game{
    
  private:
    int m_numShips;

    int userRow;
    string userCol;

    int arrCol;
    int arrRow;
    
    Board* m_p1ownBoard;
    Board* m_p1oppBoard;
    Board* m_p2ownBoard;
    Board* m_p2oppBoard;
    
    //Player p1;
    //Player p2;

  public:

    Game();

    ~Game();

    //Player getP1();
    //Player getP2();



    void run();

    void setup();




    bool isHit();


    void updateBoard();

    void printPlayerBoards(Board* ownBoard, Board* oppBoard);

    void printWinner();

    void gameEnd();

    //void p1Turn();

    //void p2Turn();

    int convertCol(string c);


//functions below will be used for adding ships to the board in setup()
    bool isAvailable(int row, int col);//check if position is empty

    bool checkUpDownLeftRight(int row, int col, int shipNum, string direction);//checks if up, down, left, right is available

    void addShiptoArray(int ship, string direction);//throws runtime error when orientation runs off the board or is full

    // use isAvailable() --will tell if position is open
    //if position is open, ask if user wants to place it up/down/left/right
    //then call checkUpDownLeftRight--checks if it will run off the board and if so, is false
    //if checkUpDownLeftRight returns false then tell user that direction is not possible
    //if true, addShiptoArray
    
    //if cant put in any direction: what do you do???




};
#endif
