//Game.cpp
#include "Game.h"
//#include "Player.h"
#include "Board.h"
#include <stdexcept>
#include <cctype> //included for isUpper function

using namespace std;
Game::Game() {
  m_numShips = 0;

  userRow = 0;
  userCol = "";

  arrCol = 0;
  arrRow = 0;

  m_p1oppBoard=new Board();
  m_p1ownBoard=new Board();
  m_p2oppBoard=new Board();
  m_p2ownBoard=new Board();

    m_currentPlayer=1;

}

Game::~Game()
{
    delete m_p2ownBoard;
    delete m_p2oppBoard;
    delete m_p1ownBoard;
    delete m_p1oppBoard;
}


int Game::convertCol(string col){

    char charCol=col.at(0);
    if(isupper(charCol))
    {
        return(int(charCol)-65);
    }
    else
    {
        return(int(charCol)-97);
    }

}

void Game::setup(){

  //gets number of ships
  do{
    cout << "Enter the amount of ships both players want to use (Max: 5):  ";
    cin >> m_numShips;
      if(m_numShips < 1 || m_numShips > 5)
      {
          std::cout<<"Invalid number of ships. Must be 1 to 5. Try again.\n";
      }
  }while(m_numShips<1 || m_numShips>5);

    //test code
    //printPlayerBoards(m_p1ownBoard, m_p1oppBoard);
    //test code above

  //get number ships coordinates
    for(int j=1; j<3; j++)
    {
        switch (m_numShips) {
            case 1:
                cout << "Enter the coordinates for player "<<j<<"'s ship 1 (1x1): \n";

                do{
                    cout << "Row (1-8):  ";
                    cin >> userRow;
                    arrRow = userRow - 1;
                    if(arrRow<0 || arrRow >7)
                    {
                        std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                    }
                }while(arrRow < 0 || arrRow > 7);

                do{

                    cout << "Col (A-H): ";
                    cin >> userCol;
                    arrCol = convertCol(userCol);
                    if(arrCol < 0 || arrCol > 7)
                    {
                        std::cout<<"Invalid column. Must be A to H. Try again.\n";
                    }

                }while(arrCol < 0 || arrCol > 7);

                userDirection="none";//set userDirection=none because ship of size 1 is only one point on the array

                if (isAvailable(arrRow, arrCol))
                {
                    if(m_currentPlayer==1)
                    {
                        addShiptoArray("1", arrRow, arrCol, userDirection, 1);
                    }
                    else
                    {
                        addShiptoArray("1", arrRow, arrCol, userDirection, 2);
                    }
                }

                //test code NOTE: WHEN TESTED B 5, PUTS IT IN 4 E
                printPlayerBoards(m_p1ownBoard, m_p1oppBoard);
                printPlayerBoards(m_p2ownBoard, m_p2oppBoard);
                //test code above

                break;

            case 2:

                for(int i=1; i<3; i++)
                {
                    cout<<"Enter the coordinates for player "<<j<<"'s ship "<<i<<" (1x"<<i<<")\n";

                    do{
                        cout << "Row (1-8): ";
                        cin>>userRow;
                        arrRow=userRow - 1;
                        if(arrRow<0 || arrRow >7)
                        {
                            std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                        }
                    }while(arrRow < 0 || arrRow > 7);

                    do{

                        cout << "Col (A-H): ";
                        cin >> userCol;
                        arrCol = convertCol(userCol);
                        if(arrCol < 0 || arrCol > 7)
                        {
                            std::cout<<"Invalid column. Must be A to H. Try again.\n";
                        }

                    }while(arrCol < 0 || arrCol > 7);

                }
                break;

            case 3:

                for(int i=1; i<4; i++)
                {
                    cout<<"Enter the coordinates for player "<<j<<"'s ship "<<i<<" (1x"<<i<<")\n";

                    do{
                        cout << "Row (1-8): ";
                        cin>>userRow;
                        arrRow=userRow - 1;
                        if(arrRow<0 || arrRow >7)
                        {
                            std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                        }

                    }while(arrRow < 0 || arrRow > 7);

                    do{

                        cout << "Col (A-H): ";
                        cin >> userCol;
                        arrCol = convertCol(userCol);
                        if(arrCol < 0 || arrCol > 7)
                        {
                            std::cout<<"Invalid column. Must be A to H. Try again.\n";
                        }
                    }while(arrCol < 0 || arrCol > 7);

                }

                break;

            case 4:

                for(int i=1; i<5; i++)
                {
                    cout<<"Enter the coordinates for player "<<j<<"'s ship "<<i<<" (1x"<<i<<")\n";

                    do{
                        cout << "Row (1-8): ";
                        cin>>userRow;
                        arrRow=userRow - 1;
                        if(arrRow<0 || arrRow >7)
                        {
                            std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                        }
                    }while(arrRow < 0 || arrRow > 7);

                    do{

                        cout << "Col (A-H): ";
                        cin >> userCol;
                        arrCol = convertCol(userCol);
                        if(arrCol < 0 || arrCol > 7)
                        {
                            std::cout<<"Invalid column. Must be A to H. Try again.\n";
                        }
                    }while(arrCol < 0 || arrCol > 7);

                }

                break;

            case 5:

                for(int i=1; i<6; i++)
                {
                    cout<<"Enter the coordinates for player "<<j<<"'s ship "<<i<<" (1x"<<i<<")\n";

                    do{
                        cout << "Row (1-8): ";
                        cin>>userRow;
                        arrRow=userRow - 1;
                        if(arrRow<0 || arrRow >7)
                        {
                            std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                        }
                    }while(arrRow < 0 || arrRow > 7);

                    do{

                        cout << "Col (A-H): ";
                        cin >> userCol;
                        arrCol = convertCol(userCol);
                        if(arrCol < 0 || arrCol > 7)
                        {
                            std::cout<<"Invalid column. Must be A to H. Try again.\n";
                        }
                    }while(arrCol < 0 || arrCol > 7);

                }

                break;
        }
        m_currentPlayer=2;//change value of current player to 2 for second round of for loop
    }


  //cout << "Player 1,



}


void Game::run(){

  //lets Begin
  string letsPlay = "\n  _          _         _____  _             _ \n | |        | |       |  __ \\| |           | |\n | |     ___| |_ ___  | |__) | | __ _ _   _| |\n | |    / _ \\ __/ __| |  ___/| |/ _` | | | | |\n | |___|  __/ |_\\__ \\ | |    | | (_| | |_| |_|\n |______\\___|\\__|___/ |_|    |_|\\__,_|\\__, (_)\n                                       __/ |  \n                                      |___/   \n";
  string p1Text = "\n  _____  _                          ____             \n |  __ \\| |                        / __ \\            \n | |__) | | __ _ _   _  ___ _ __  | |  | |_ __   ___ \n |  ___/| |/ _` | | | |/ _ \\ '__| | |  | | '_ \\ / _ \\\n | |    | | (_| | |_| |  __/ |    | |__| | | | |  __/\n |_|    |_|\\__,_|\\__, |\\___|_|     \\____/|_| |_|\\___|\n                  __/ |                              \n                 |___/                               \n";
  string p2Text = "\n  _____  _                         _______            \n |  __ \\| |                       |__   __|           \n | |__) | | __ _ _   _  ___ _ __     | |_      _____  \n |  ___/| |/ _` | | | |/ _ \\ '__|    | \\ \\ /\\ / / _ \\ \n | |    | | (_| | |_| |  __/ |       | |\\ V  V / (_) |\n |_|    |_|\\__,_|\\__, |\\___|_|       |_| \\_/\\_/ \\___/ \n                  __/ |                               \n                 |___/                                \n";
  //string p2Text =



  cout << letsPlay << endl;
  cout << p1Text << endl;
  cout << p2Text << endl;


  //p1Turn();
  //p2Turn();

}

void Game::p1Turn(){
  //print Board
  printPlayerBoards(m_p1ownBoard, m_p2oppBoard);

}

void Game::p2Turn(){

}


/*void Game::getCoordinates(){

}*/





void Game::printPlayerBoards(Board* ownBoard, Board* oppBoard){

    cout<<"Opponent's Board:\n";
    oppBoard->printBoard();
  cout<<"-----------------------------------------------------\n";
    cout<<"Own Board:\n";
    ownBoard->printBoard();

}


void Game::addShiptoArray(string ship, int row, int col, std::string direction, int player)
{
    if(direction=="none")//direction=none means placing m_ship1 on the board: 1x1 size
    {
        if(player==1)
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
        }
        else
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
        }
    }
    else if(direction=="up")
    {

    }
    else if(direction=="down")
    {

    }
    else if(direction=="left")
    {

    }
    else//happens if direction is "right"
    {

    }
}

bool Game::isAvailable(int row, int col)
{
    return(true);//THIS WON'T BE HERE LATER--CODE JUST TO LET IT COMPILE
}

bool Game::checkUpDownLeftRight(int row, int col, int shipNum, string direction)
{
    return(false);//THIS WON'T BE HERE LATER--CODE JUST TO LET IT COMPILE
}
