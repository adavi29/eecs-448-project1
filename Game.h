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

    void p1Turn();

    void p2Turn();

    int convertCol(string c);



    bool isValidPosition(int row, int col);//check if position is open

    bool checkUpDownLeftRight(int row, int col, int shipNum);//checks if up, down, left, right is available







};
#endif
