//Game.cpp
#include "Game.h"

using namespace std;
Game::Game() {
  m_numShips = 0;

  userRow = 0;
  userCol = "";

  arrCol = 0;
  arrRow = 0;

}

Game::Setup(){
  do{
    cout << "Enter the amount of ships both player want to use: (Max: 5) ";
    cin >> m_numShips;
  }while(m_numShips < 0 || m_numShips > 5);

  switch (m_numShips) {
    case 1:
      cout << "Enter the coordinates for ship 1: (1x1)";

      do{
        cout << "Row: (1-8) ";
        cin >> userRow;
        arrRow = userRow - 1;
      }while(arrRow < 0 || arrRow > 7)

      do{

        cout << "Col: (A-H)";
        cin >> userCol;


        switch (userCol) {
          case "A":
            arrCol = 0;

          case "B":
            arrCol = 1;

          case "C":
              arrCol = 2;

          case "D":
            arrCol = 3;

          case "E":
            arrCol = 4;

          case "F":
            arrCol = 5;

          case "G":
            arrCol = 6;

          case "H":
            arrCol = 7;

        }

      }while(arrCol < 0 || userCol > 7)


    case 2:

    case 3:

    case 4:

    case 5:
  }

  cout << "Player 1,



}


Game::Run(){

}


Game::getCoordinates(){

}
