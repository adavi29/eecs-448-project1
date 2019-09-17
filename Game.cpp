//Game.cpp
#include "Game.h"
//#include "Player.h"
#include "Board.h"
#include <stdexcept>
#include <cctype> //included for isUpper function
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

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

std::string Game::convertStringToLower(string wordToConvert)
{
    char charWordToConvert=wordToConvert.at(0);
    for(int i=0; i<wordToConvert.length(); i++)
    {
        charWordToConvert=wordToConvert.at(i);
        if(isupper(charWordToConvert))
        {
            charWordToConvert=(char)tolower(charWordToConvert);
        }
        wordToConvert.at(i)=charWordToConvert;
    }
    return(wordToConvert);
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


                    if(m_currentPlayer==1)
                    {
                      if (isAvailable(m_p1ownBoard,arrRow, arrCol))
                      {
                        addShiptoArray("1", arrRow, arrCol, userDirection, 1);
                        std::cout<<"Player 1's current Board:\n";
                        printOwnBoard(m_p1ownBoard);
                      }
                    }
                    else
                    {
                      if (isAvailable(m_p2ownBoard,arrRow, arrCol))
                      {
                        addShiptoArray("1", arrRow, arrCol, userDirection, 2);
                        std::cout<<"Player 2's current Board:\n";
                        printOwnBoard(m_p2ownBoard);
                      }
                    }

                //test code
//                std::cout<<"Player 1 Board:\n";
//                printOwnBoard(m_p1ownBoard);
//                printPlayerBoards(m_p1ownBoard, m_p1oppBoard);
//                std::cout<<"Player 2 Board:\n";
//                printOwnBoard(m_p2ownBoard);
                //printPlayerBoards(m_p2ownBoard, m_p2oppBoard);
                //test code above

                break;

            case 2:
//IF THE BOARD ISN'T OPEN UP DOWN LEFT RIGHT AT COORDINATE THEY PROVIDE, DO I REASK THEM WHAT COORDINATE THEY WANT?
                for(int i=1; i<3; i++)
                {
                    std::string shipString=to_string(i);
                    int shipNum=i;
                    Board* currentPlayerBoard=nullptr;
                    if(m_currentPlayer==1)
                    {
                        currentPlayerBoard=m_p1ownBoard;
                    }
                    else
                    {
                        currentPlayerBoard=m_p2ownBoard;
                    }
                    
                    cout<<"Enter the coordinates for player "<<j<<"'s ship "<<i<<" (1x"<<i<<")\n";

                    do{
                        cout << "Row (1-8): ";
                        cin>>userRow;
                        arrRow=userRow - 1;
                        if(arrRow<0 || arrRow >7)
                        {
                            std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                        }
                        //ask in which direction want the thing to be stored; then convert all chars tolower
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
                    
                    if(i>1)
                    {
                        std::cout<<"Given your coordinates, your ship can be placed in the following directions:";
                        if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "up"))
                        {
                            std::cout<<" up ";
                        }
                        if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "down"))
                        {
                            std::cout<<" down ";
                        }
                        if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "left"))
                        {
                            std::cout<<" left ";
                        }
                        if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "right"))
                        {
                            std::cout<<" right ";
                        }
                        else
                        {
                            std::cout<<" none ";
                        }
                           
                        do
                        {
                            std::cout<<"\nIn which direction do you want the ship to be placed (up/down/left/right):";
                            std::cin>>userDirection;
                            userDirection=convertStringToLower(userDirection);
                            
                        }while(userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right");
                    }else if(i<2)
                    {
                        userDirection="none";
                    }
                    
                    if(m_currentPlayer==1)
                    {
                        if (isAvailable(m_p1ownBoard,arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
                            std::cout<<"Player 1's current Board:\n";
                            printOwnBoard(m_p1ownBoard);
                        }
                    }
                    else
                    {
                        if (isAvailable(m_p2ownBoard,arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
                            std::cout<<"Player 2's current Board:\n";
                            printOwnBoard(m_p2ownBoard);
                        }
                    }
                    

                }
                break;

            case 3:

                for(int i=1; i<4; i++)
                {
                    std::string shipString=to_string(i);
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
                    std::string shipString=to_string(i);
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
                    std::string shipString=to_string(i);
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
  cout << "Press any key then hit Enter to continue...";
  cin >> wait;



  //loop section
  bool endGame = true;

  while(endGame){

    clearConsole();

    //players 1 turn
    cout << p1Text << endl;
    cout << "Press any key then hit Enter to continue...";
    cin >> wait;
    p1Turn();


    clearConsole();

    //playes 2 turn
    cout << p2Text << endl;
    cout << "Press any key then hit Enter to continue...";
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
  if(isHit(m_p2ownBoard, p1_attack_row, p1_attack_col)){

    cout << "That's a HIT!" << endl;
    m_p1oppBoard->setEntryAtPosition("X", p1_attack_col, p1_attack_row);

  }else{

    cout << "That's a MISS! Better luck next time." << endl;
    m_p1oppBoard->setEntryAtPosition("O", p1_attack_col, p1_attack_row);
  }

  cout << "Next Players Turn. Press any key then hit Enter to continue...";
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
    if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)){
      cout << "That's a HIT!" << endl;
      m_p2oppBoard->setEntryAtPosition("H", p2_attack_col, p2_attack_row);

    }else{
      cout << "That's a MISS! Better luck next time." << endl;
      m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
    }




    cout << "Next Players Turn. Press any key then hit Enter to continue...";
    cin>> wait;
}

void Game::clearConsole(){
  //A load of end lines to clear the console screen inbetween player turns so they can't cheat
  for(int i = 0; i < 200; i ++){
    cout << endl;
  }
  system("clear");
}

void Game::printWinner(int player){

  ifstream file_p1_wins ("player1wins.txt");
  ifstream file_p2_wins ("player2wins.txt");

  if(player == 1){
    cout << getFileContents (file_p1_wins) << endl;
  }else if(player == 2){
    cout << getFileContents(file_p2_wins) << endl;
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

bool Game::isHit(Board* playerBoard, int row, int col){
  //This is temporary, will add code later
  return false;
}

string Game::getFileContents (std::ifstream& File){
    std::string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
	while (File.good ())
	{
	    std::string TempLine;                  //Temp line
	    std::getline (File , TempLine);        //Get temp line
	    TempLine += "\n";                      //Add newline character

	    Lines += TempLine;                     //Add newline
	}
	return Lines;
    }
    else                           //Return error
    {
	return "ERROR File does not exist.";
    }
}


void Game::printPlayerBoards(Board* ownBoard, Board* oppBoard){

    cout<<"Opponent's Board:\n";
    oppBoard->printBoard();
  cout<<"-----------------------------------------------------\n";
    cout<<"Own Board:\n";
    ownBoard->printBoard();

}

void Game::printOwnBoard(Board* ownBoard)
{
    //cout<<"Own Board:\n";
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
        if(player==1 && ship=="2")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-1);
        }
        else if(player==2 && ship=="2")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-1);
        }
        else if(player==1 && ship=="3")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-1);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-2);
        }
        else if(player==2 && ship=="3")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-1);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-2);
        }
        else if(player==1 && ship=="4")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-1);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-2);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-3);
        }
        else if(player==2 && ship=="4")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-1);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-2);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-3);
        }
        else if(player==1 && ship=="5")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-1);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-2);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-3);
            m_p1ownBoard->setEntryAtPosition(ship, col, row-4);
        }
        else if(player==2 && ship=="5")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-1);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-2);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-3);
            m_p2ownBoard->setEntryAtPosition(ship, col, row-4);
        }
        
    }
    else if(direction=="down")
    {
        if(player==1 && ship=="2")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+1);
        }
        else if(player==2 && ship=="2")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+1);
        }
        else if(player==1 && ship=="3")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+1);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+2);
        }
        else if(player==2 && ship=="3")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+1);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+2);
        }
        else if(player==1 && ship=="4")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+1);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+2);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+3);
        }
        else if(player==2 && ship=="4")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+1);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+2);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+3);
        }
        else if(player==1 && ship=="5")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+1);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+2);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+3);
            m_p1ownBoard->setEntryAtPosition(ship, col, row+4);
        }
        else if(player==2 && ship=="5")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+1);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+2);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+3);
            m_p2ownBoard->setEntryAtPosition(ship, col, row+4);
        }
    }
    else if(direction=="left")
    {
        if(player==1 && ship=="2")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-1, row);
        }
        else if(player==2 && ship=="2")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-1, row);
        }
        else if(player==1 && ship=="3")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-1, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-2, row);
        }
        else if(player==2 && ship=="3")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-1, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-2, row);
        }
        else if(player==1 && ship=="4")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-1, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-2, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-3, row);
        }
        else if(player==2 && ship=="4")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-1, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-2, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-3, row);
        }
        else if(player==1 && ship=="5")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-1, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-2, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-3, row);
            m_p1ownBoard->setEntryAtPosition(ship, col-4, row);
        }
        else if(player==2 && ship=="5")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-1, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-2, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-3, row);
            m_p2ownBoard->setEntryAtPosition(ship, col-4, row);
        }
    }
    else//happens if direction is "right"
    {
        if(player==1 && ship=="2")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+1, row);
        }
        else if(player==2 && ship=="2")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+1, row);
        }
        else if(player==1 && ship=="3")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+1, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+2, row);
        }
        else if(player==2 && ship=="3")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+1, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+2, row);
        }
        else if(player==1 && ship=="4")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+1, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+2, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+3, row);
        }
        else if(player==2 && ship=="4")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+1, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+2, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+3, row);
        }
        else if(player==1 && ship=="5")
        {
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+1, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+2, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+3, row);
            m_p1ownBoard->setEntryAtPosition(ship, col+4, row);
        }
        else if(player==2 && ship=="5")
        {
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+1, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+2, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+3, row);
            m_p2ownBoard->setEntryAtPosition(ship, col+4, row);
        }
    }
}

bool Game::isAvailable(Board* board, int row, int col)
{
      if(board->getEntryAtPosition(row,col) == " ")
      {
        return true;
      }
      else
      {
        return false;
      }
}

bool Game::checkUpDownLeftRight(Board* board, int row, int col, int shipNum, string direction)
{
	bool alwaysFits = true;
        if(direction=="none")
        {
            alwaysFits=true;
        }
		else if(direction == "up") {
			if(row-(shipNum-1) >= 0) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row-i, col) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}

		else if(direction == "down") {
			if(row+(shipNum-1) <= 7) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row+i, col) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}

		else if(direction == "left") {
			if(col-(shipNum-1) >= 0) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row, col-i) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}

		else if(direction == "right") {
			if(col+(shipNum-1) <= 7) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row, col+i) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}

		return(alwaysFits);
}

void Game::printBattleship(){
  cout<<"\n*********        *******    ************  ************  **            ***********      *********    **          **  ***********   ********\n";
  cout<<"**       **    **       **       **            **       **            **             **             **          **       **       **      ** \n";
  cout<<"**        **  **         **      **            **       **            **            **              **          **       **       **       ** \n";
  cout<<"**        **  **         **      **            **       **            **            **              **          **       **       **       ** \n";
  cout<<"**       **   **         **      **            **       **            **             **             **          **       **       **      ** \n";
  cout<<"*********     *************      **            **       **            *****           *********     **************       **       ********\n";
  cout<<"**       **   **         **      **            **       **            **                       **   **          **       **       ** \n";
  cout<<"**        **  **         **      **            **       **            **                        **  **          **       **       ** \n";
  cout<<"**        **  **         **      **            **       **            **                        **  **          **       **       ** \n";
  cout<<"**       **   **         **      **            **       **            **                       **   **          **       **       ** \n";
  cout<<"*********     **         **      **            **       ***********   ***********     *********     **          **  ***********   ** \n\n\n";
}
