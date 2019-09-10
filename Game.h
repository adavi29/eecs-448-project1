//Game.h
#include "Player.h"
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

    Player p1;
    Player p2;
  public:

    Game();

    ~Game();



    void run();

    void setup();




    bool isHit();


    void updateBoard();

    void printPlayerBoards();

    void printWinner();

    void gameEnd();

    void p1Turn();

    void p2Turn();





    bool isValidPosition(int row, int col);//check if position is open

    bool checkUpDownLeftRight(int row, int col, int shipNum);//checks if up, down, left, right is available







};
