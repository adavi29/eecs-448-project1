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

  //string variables for text in console
  string letsPlay = "\n  _          _         _____  _             _ \n | |        | |       |  __ \\| |           | |\n | |     ___| |_ ___  | |__) | | __ _ _   _| |\n | |    / _ \\ __/ __| |  ___/| |/ _` | | | | |\n | |___|  __/ |_\\__ \\ | |    | | (_| | |_| |_|\n |______\\___|\\__|___/ |_|    |_|\\__,_|\\__, (_)\n                                       __/ |  \n                                      |___/   \n";
  string p1Text = "\n  _____  _                          ____             \n |  __ \\| |                        / __ \\            \n | |__) | | __ _ _   _  ___ _ __  | |  | |_ __   ___ \n |  ___/| |/ _` | | | |/ _ \\ '__| | |  | | '_ \\ / _ \\\n | |    | | (_| | |_| |  __/ |    | |__| | | | |  __/\n |_|    |_|\\__,_|\\__, |\\___|_|     \\____/|_| |_|\\___|\n                  __/ |                              \n                 |___/                               \n";
  string p2Text = "\n  _____  _                         _______            \n |  __ \\| |                       |__   __|           \n | |__) | | __ _ _   _  ___ _ __     | |_      _____  \n |  ___/| |/ _` | | | |/ _ \\ '__|    | \\ \\ /\\ / / _ \\ \n | |    | | (_| | |_| |  __/ |       | |\\ V  V / (_) |\n |_|    |_|\\__,_|\\__, |\\___|_|       |_| \\_/\\_/ \\___/ \n                  __/ |                               \n                 |___/                                \n";
  string wait = "";


  //start game
  system("clear");

  cout << letsPlay << endl;
  cout << "Press any key to continue...";
  cin >> wait;



  //loop section
  bool endGame = true;

  while(endGame){

    clearConsole();

    //players 1 turn
    cout << p1Text << endl;
    cout << "Press any key to continue...";
    cin >> wait;
    p1Turn();


    clearConsole();

    //playes 2 turn
    cout << p2Text << endl;
    cout << "Press any key to continue...";
    cin >> wait;
    p2Turn();

  }



}


//run() helper methods
void Game::p1Turn(){



  int p1_attack_row = 0;
  int p1_attack_col = 0;
  //string p1_attack_col_string;
  string wait = "";



  //print Board
  printPlayerBoards(m_p1ownBoard, m_p1oppBoard);

  cout << "It time to attack!" << endl;

  //gets good input from the user 
  p1_attack_row = getUserRow();
  p1_attack_col = getUserCol();

  //checks if isHit() or not 



  //hit or miss, THIS IF BLOCK OF CODE IS TEMPORARY
  if(m_p2ownBoard->getEntryAtPosition(p1_attack_col,p1_attack_row) == "Ship"){
    cout << "That's a HIT!" << endl;
    m_p1oppBoard->setEntryAtPosition("X", p1_attack_col, p1_attack_row);

  }else{
    cout << "That's a MISS! Better luck next time." << endl;
    m_p1oppBoard->setEntryAtPosition("O", p1_attack_col, p1_attack_row);
  }




  cout << "Next Players Turn. Press any key to continue...";
  cin>> wait;




}

void Game::p2Turn(){

    int p2_attack_row = 0;
    int p2_attack_col = 0;
    //string p2_attack_col_string;
    string wait = "";



    //print Board
    printPlayerBoards(m_p2ownBoard, m_p2oppBoard);

    p2_attack_row = getUserRow();
    p2_attack_col = getUserCol();



    //hit or miss, THIS IF BLOCK OF CODE IS TEMPORARY
    if(m_p1ownBoard->getEntryAtPosition(p2_attack_col,p2_attack_row) == "Ship"){
      cout << "That's a HIT!" << endl;
      m_p2oppBoard->setEntryAtPosition("X", p2_attack_col, p2_attack_row);

    }else{
      cout << "That's a MISS! Better luck next time." << endl;
      m_p2oppBoard->setEntryAtPosition("O", p2_attack_col, p2_attack_row);
    }




    cout << "Next Players Turn. Press any key to continue...";
    cin>> wait;





}

void Game::clearConsole(){
  //A FUCK load of end lines to clear the console screen inbetween player turns so they can't cheat
  for(int i = 0; i < 200; i ++){
    cout << endl;
  }
  system("clear");
}

void Game::printWinner(int player){
  if(player == 1){
    cout << "PLAYER 1 WINS!" << endl;
  }else if(player == 2){
    cout << "PLAYER 2 WINS!" << endl;
  }

}

int Game::getUserRow(){
  string input;
  while(1){
    cout << "Enter Row(1-8): ";
    cin >> input;

    if(input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8"){
      return (stoi(input) - 1);
    }

  }

}

int Game::getUserCol(){
  string input;
  int input_num = 0;
  while(1){
    cout << "Enter Column(A-H): ";
    cin >> input;
    input_num = convertCol(input);
    if(input_num == 0 || input_num == 1 || input_num == 2 || input_num == 3 || input_num == 4 || input_num == 5 || input_num == 6 || input_num == 7){
      return input_num;
    }

  }
}

bool Game::isHit(){
  
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
