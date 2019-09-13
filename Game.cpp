//Game.cpp
#include "Game.h"
//#include "Player.h"
#include "Board.h"
#include <stdexcept>

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

}

Game::~Game()
{
    delete m_p2ownBoard;
    delete m_p2oppBoard;
    delete m_p1ownBoard;
    delete m_p2oppBoard;
}


int Game::convertCol(string c){

  if(c=="A" || c == "a")
  {
    return(0);
  }
  else if(c=="B"|| c == "b")
  {
    return(1);
  }
  else if(c=="C"|| c == "c")
  {
    return(2);
  }
  else if(c=="D"|| c == "d")
  {
    return(3);
  }
  else if(c=="E"|| c == "e")
  {
    return(4);
  }
  else if(c=="F"|| c == "f")
  {
    return(5);
  }
  else if(c=="G"|| c == "g")
  {
    return(6);
  }
  else if(c=="H" || c== "h")
  {
    return(7);
  }
  else
  {
    throw(std::runtime_error("Invalid entry (use A-H only): "));
  }

}

void Game::setup(){

  //gets number of ships
  do{
    cout << "Enter the amount of ships both players want to use (Max: 5):  ";
    cin >> m_numShips;
  }while(m_numShips<1 || m_numShips>5);

    //test code
    //printPlayerBoards(m_p1ownBoard, m_p1oppBoard);
    //test code above

  //get number ships coordinates
  switch (m_numShips) {
    case 1:
      cout << "Enter the coordinates for ship 1 (1x1): \n";

      do{
        cout << "Row (1-8):  ";
        cin >> userRow;
        arrRow = userRow - 1;
      }while(arrRow < 0 || arrRow > 7);

      do{

        cout << "Col (A-H): ";
        cin >> userCol;
        arrCol = convertCol(userCol);

      }while(arrCol < 0 || arrCol > 7);


    //case 2:

    //case 3:

    //case 4:

    //case 5:
  }

  //cout << "Player 1,



}


void Game::run(){

}


/*void Game::getCoordinates(){

}*/





void Game::printPlayerBoards(Board* ownBoard, Board* oppBoard){

    ownBoard->printBoard();
  cout<<"\n-----------------------------------------------------\n";
    oppBoard->printBoard();

}


