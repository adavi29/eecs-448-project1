/**
 * @author Runtime Terrors:
 *             Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *             Jacob Swearingen, Chongzhi Gao
 * @date 9/19/19
 * @file Game.cpp
 * @brief implemented methods needed for game play from header file
 */

#include <stdexcept>
#include <cctype> // provides isUpper()
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "game.h"
#include "board.h"
#include "asciiart.h"

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

	m_currentPlayer = 1;

	wait = "";
}

Game::~Game() {
	delete m_p2ownBoard;
	delete m_p2oppBoard;
	delete m_p1ownBoard;
	delete m_p1oppBoard;
	delete m_p1Ships;
	delete m_p2Ships;
}

int Game::convertCol(std::string col) {
	char charCol = col.at(0);
	if(isupper(charCol)) {
		return(int(charCol)-65);
	}
	else {
		return(int(charCol)-97);
	}
}

std::string Game::convertStringToLower(std::string wordToConvert) {
	char charWordToConvert = wordToConvert.at(0);
	int wordLength = wordToConvert.length();
	for(int i = 0; i < wordLength; i++) {
		charWordToConvert = wordToConvert.at(i);
		if(isupper(charWordToConvert)) {
			charWordToConvert=(char)tolower(charWordToConvert);
		}
		wordToConvert.at(i)=charWordToConvert;
	}
	return(wordToConvert);
}

void Game::setup() {
	int numShipsChoice = 0;
	int userRowChoice = 0;
	Board* currentPlayerBoard = nullptr;
	std::cout << std::endl;
	printBattleship();
	//gets number of ships
	do {
		std::cout << "Enter the amount of ships both players want to use:"
				  << "(Max: 5): ";
		std::cin >> numShipsChoice;
		if(std::cin.fail()) {
			std::cin.clear();
			numShipsChoice = 0;
		} else {
			if((numShipsChoice < 1) || (numShipsChoice > 5)) {
				std::cout << "Invalid number of ships."
					  << "Must be 1 to 5. Try again.\n";
			}
		}
	} while((numShipsChoice < 1) || (numShipsChoice > 5));
	m_numShips = numShipsChoice;
	//test code
	//printPlayerBoards(m_p1ownBoard, m_p1oppBoard);
	//test code above
	//get number ships coordinates
	for(int j = 1; j < 3; j++) {
		if(j == 1) {
			printPlayerTurn(1);
		} else {
			printPlayerTurn(2);
		}
		switch (m_numShips) {
			case 1: {
				std::cout << "Enter the coordinates for player "
						  << j
						  << "'s ship 1 (1x1): \n";
				do {
					std::cout << "Row (1-8):  ";
					std::cin>>userRowChoice;
					if((userRowChoice < 1) || (userRowChoice > 8)) {
						std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
					}
				} while((userRowChoice < 1) || (userRowChoice > 8));
				userRow = userRowChoice;
				arrRow = userRow - 1;
				do {
					std::cout << "Col (A-H): ";
					std::cin >> userCol;
					arrCol = convertCol(userCol);
					if(arrCol < 0 || arrCol > 7) {
						std::cout << "Invalid column."
								  << "Must be A to H. Try again.\n";
					}
				} while(arrCol < 0 || arrCol > 7);
				//set userDirection=none because ship of size 1 is only one
				//point on the array
				userDirection="none";
				if(m_currentPlayer==1) {
					if (isAvailable(m_p1ownBoard,arrRow, arrCol)) {
						addShiptoArray("1", arrRow, arrCol, userDirection, 1);
						std::cout<<"Player 1's current Board:\n";
						printOwnBoard(m_p1ownBoard);
					}
				} else {
					if (isAvailable(m_p2ownBoard,arrRow, arrCol)) {
						addShiptoArray("1", arrRow, arrCol, userDirection, 2);
						std::cout<<"Player 2's current Board:\n";
						printOwnBoard(m_p2ownBoard);
					}
				}
				break;
			}
			case 2: {
				for(int i = 1; i < 3; i++) {
					std::string shipString=std::to_string(i);
					int shipNum=i;
					shipPlacementInteraction(i, j, currentPlayerBoard);
					if(m_currentPlayer==1) {
						if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
							std::cout<<"Player 1's current Board:\n";
							printOwnBoard(m_p1ownBoard);
						}
					} else {
						if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
							std::cout<<"Player 2's current Board:\n";
							printOwnBoard(m_p2ownBoard);
						}
					}
				}
				break;
			}
			case 3: {
				for(int i = 1; i < 4; i++) {
					std::string shipString=std::to_string(i);
					int shipNum=i;
					shipPlacementInteraction(i, j, currentPlayerBoard);
					if(m_currentPlayer==1) {
						if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
							std::cout<<"Player 1's current Board:\n";
							printOwnBoard(m_p1ownBoard);
						}
					} else {
						if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
							std::cout<<"Player 2's current Board:\n";
							printOwnBoard(m_p2ownBoard);
						}
					}
				}
				break;
			}
			case 4: {
				for(int i = 1; i < 5; i++) {
					std::string shipString=std::to_string(i);
					int shipNum=i;
					shipPlacementInteraction(i, j, currentPlayerBoard);
					if(m_currentPlayer==1) {
						if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
							std::cout<<"Player 1's current Board:\n";
							printOwnBoard(m_p1ownBoard);
						}
					} else {
						if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
							std::cout<<"Player 2's current Board:\n";
							printOwnBoard(m_p2ownBoard);
						}
					}
				}
				break;
			}
			case 5: {
				for(int i = 1; i < 6; i++) {
					std::string shipString=std::to_string(i);
					int shipNum=i;
					shipPlacementInteraction(i, j, currentPlayerBoard);
					if(m_currentPlayer==1) {
						if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
							std::cout<<"Player 1's current Board:\n";
							printOwnBoard(m_p1ownBoard);
						}
					} else {
						if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection)) {
							addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
							std::cout<<"Player 2's current Board:\n";
							printOwnBoard(m_p2ownBoard);
						}
					}
				}
				break;
			}
		}
		m_currentPlayer = 2;//change value of current player to 2 for second round of for loop
	}
}

void Game::run() {
	m_p1Ships = new Ships(m_numShips);
	m_p2Ships = new Ships(m_numShips);
	//start game
	system("clear");

	// TODO: Change this to print the ASCII file
	std::cout << letsPlay << std::endl;
	std::cout << "Press any letter key then hit Enter to continue...";
	std::cin >> wait;

	//loop section
	bool endGame = true;

	while(endGame) {

		//player 1 turn
		printPlayerTurn(1);
		p1Turn();

		//checks if player 1 has won
		if(m_p2Ships->allSunk()) {
			printWinner(1);
			endGame = false;
			break;
		}

		//player 2 turn
		printPlayerTurn(2);
		p2Turn();

		//checks if player 2 has won
		if(m_p1Ships->allSunk()) {
			printWinner(2);
			endGame = false;
			break;
		}
	}
}

//run() helper methods
void Game::p1Turn() {

	int p1_attack_row = 0;
	int p1_attack_col = 0;
	//string p1_attack_col_string;
	std::string wait = "";

	std::string shipNum_string;
	int shipNum;

	//print Board
	printPlayerBoards(m_p1ownBoard, m_p1oppBoard);

	std::cout << "It's time to attack!" << std::endl;

	while(1) {
		p1_attack_row = getUserRow();
		p1_attack_col = getUserCol();

		if(m_p1oppBoard->getEntryAtPosition(p1_attack_col, p1_attack_row) == "H" || m_p1oppBoard->getEntryAtPosition(p1_attack_col, p1_attack_row) == "M") {
			std::cout<< "You have already tried to attack there. Pick a different coordinate." << std::endl;
		}else{
			break;
		}
	}
	//gets good input from the user

	//checks if isHit() or not
	if(isHit(m_p2ownBoard, p1_attack_row, p1_attack_col)) {
		std::cout << "That's a HIT!" << std::endl;
		m_p1oppBoard->setEntryAtPosition("H", p1_attack_col, p1_attack_row);

		//decreases the opponents ship on hit and announce if sunk
		shipNum_string = m_p2ownBoard->getEntryAtPosition(p1_attack_col, p1_attack_row);
		shipNum = stoi(shipNum_string);
		m_p2Ships->decreaseSize(shipNum);
		if(m_p2Ships->allSunk()) {
			return;
		}

		//puts an x on the opponnets board
		m_p2ownBoard->setEntryAtPosition("X", p1_attack_col, p1_attack_row );
	}else{
		std::cout << "That's a MISS! Better luck next time." << std::endl;
		m_p1oppBoard->setEntryAtPosition("M", p1_attack_col, p1_attack_row);
	}
	std::cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
	std::cin>> wait;
}

void Game::p2Turn() {

	int p2_attack_row = 0;
	int p2_attack_col = 0;
	//string p2_attack_col_string;
	std::string wait = "";

	std::string shipNum_string;
	int shipNum;

	//print Board
	printPlayerBoards(m_p2ownBoard, m_p2oppBoard);

	while(1) {
		p2_attack_row = getUserRow();
		p2_attack_col = getUserCol();

		if(m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "H" || m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "M") {
			std::cout<< "You have already tried to attack there. Pick a different coordinate." << std::endl;
		}else{
			break;
		}

	}

	//hit or miss,
	if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)) {
		std::cout << "That's a HIT!" << std::endl;
		m_p2oppBoard->setEntryAtPosition("H", p2_attack_col, p2_attack_row);

		//decreases the opponents ship on hit and announces if sunk
		shipNum_string = m_p1ownBoard->getEntryAtPosition(p2_attack_col, p2_attack_row);
		shipNum = stoi(shipNum_string);
		m_p1Ships->decreaseSize(shipNum);
		if(m_p1Ships->allSunk()) {
			return;
		}

		//puts an x on the opponnets board
		m_p1ownBoard->setEntryAtPosition("X", p2_attack_col, p2_attack_row );
	}else{
		std::cout << "That's a MISS! Better luck next time." << std::endl;
		m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
	}

	std::cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
	std::cin>> wait;
}

void Game::clearConsole() {
	//A load of end lines to clear the console screen inbetween player turns so they can't cheat
	for(int i = 0; i < 200; i ++) {
		std::cout << std::endl;
	}
	system("clear");
}

void Game::printWinner(int player) {
	std::ifstream file_p1_wins ("ascii/player1wins.txt");
	std::ifstream file_p2_wins ("ascii/player2wins.txt");

	if(player == 1) {
		std::cout << getFileContents (file_p1_wins) << std::endl;
	}else if(player == 2) {
		std::cout << getFileContents(file_p2_wins) << std::endl;
	}
	// TODO: Close fstream
}

int Game::getUserRow() {
	int input;
	while(1) {
		std::cout << "Enter Row(1-8): ";
		std::cin >> input;
		if((input >= 1) || (input <= 8)) {
			return (input - 1);
		}
	}
}

int Game::getUserCol() {
	std::string input;
	int input_num = 0;
	while(1) {
		std::cout << "Enter Column(A-H): ";
		std::cin >> input;
		input_num = convertCol(input);
		if((input_num >= 0) || (input_num <= 7)) {
			return input_num;
		}
	}
}

bool Game::isHit(Board* playerBoard, int row, int col) {
	if(playerBoard->getEntryAtPosition(col, row) == " ") {
		return false;
	}
	return true;
}

std::string Game::getFileContents (std::ifstream& File) {
    //All lines
    std::string Lines = "";
    //Check if everything is good
    if (File) {
	while (File.good ()) {
	    std::string TempLine;				   //Temp line
	    std::getline (File , TempLine);		   //Get temp line
	    TempLine += "\n";					   //Add newline character
	    Lines += TempLine;					   //Add newline
	}
	return Lines;
    }
    //Return error
    else {
	return "ERROR File does not exist.";
    }
}

void Game::printPlayerBoards(Board* ownBoard, Board* oppBoard) {

	std::cout<<"Opponent's Board:\n";
	oppBoard->printBoard();
	std::cout<<"-----------------------------------------------------\n";
	std::cout<<"Own Board:\n";
	ownBoard->printBoard();
}

void Game::printOwnBoard(Board* ownBoard) {
	//std::cout<<"Own Board:\n";
	ownBoard->printBoard();
}

void Game::addShiptoArray(std::string ship, int row, int col, std::string direction, int player) {
//direction=none means plastd::cing m_ship1 on the board: 1x1 size
	if(direction == "none") {
		if(player == 1) {
			m_p1ownBoard->setEntryAtPosition(ship, col, row);
		}
		else{
			m_p2ownBoard->setEntryAtPosition(ship, col, row);
		}
	}
	else if(direction == "up") {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
				}
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
				}
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
				}
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
				}
			}
		}
	}
	else if(direction == "down") {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
				}
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				if(player==1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
				}
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
				}
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
				}
			}
		}
	}
	else if(direction == "left") {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
				}
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
				}
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
				}
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
				}
			}
		}
	}
	//happens if direction is "right"
	else {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
				}
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
				}
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
				}
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				if(player == 1) {
					m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
				} else {
					m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
				}
			}
		}
	}
}

bool Game::isAvailable(Board* board, int row, int col) {
	if(board->getEntryAtPosition(col,row) == " ") {
		return true;
	} else {
		return false;
	}
}

bool Game::checkUpDownLeftRight(Board* board, int row, int col, int shipNum, std::string direction) {
	bool alwaysFits = true;
	if(direction == "none") {
		alwaysFits = true;
	} else if(direction == "up") {
		if((row - (shipNum-1)) >= 0) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row-i, col) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	} else if(direction == "down") {
		if((row + (shipNum-1)) <= 7) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row+i, col) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	} else if(direction == "left") {
		if((col - (shipNum-1)) >= 0) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row, col-i) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	} else if(direction == "right") {
		if((col +(shipNum - 1)) <= 7) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row, col+i) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	}
	return(alwaysFits);
}

void Game::printBattleship() {
    std::ifstream file_battleship_text("ascii/battleship.txt");
    std::cout << AsciiArtHandler::printFileContents(file_battleship_text) << std::endl;
}

void Game::printCoordinateInteraction(Board* currentPlayerBoard, int shipNum) {
	int userRowChoice = 0;
	bool keepAsking = false;

	do {
		keepAsking = false;
		do {
			std::cout << "Row (1-8):  ";
			std::cin>>userRowChoice;
			if((userRowChoice < 1) || (userRowChoice > 8)) {
				std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
			}
		} while((userRowChoice < 1) || (userRowChoice > 8));
		userRow = userRowChoice;
		arrRow = userRow - 1;

		do {
			std::cout << "Col (A-H): ";
			std::cin >> userCol;
			arrCol = convertCol(userCol);
			if(arrCol < 0 || arrCol > 7) {
				std::cout<<"Invalid column. Must be A to H. Try again.\n";
			}
		} while(arrCol < 0 || arrCol > 7);

		if(!isAvailable(currentPlayerBoard, arrRow, arrCol)) {
			std::cout<< "This coordinate has already been taken. Enter new coordinates:\n";
			keepAsking = true;
		}
		if( // TODO: checkEveryDirection which runs all of these and returns false if one is false.
			(!(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "up"))) &&
			(!(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "down"))) &&
			(!(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "left"))) &&
			(!(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "right"))) &&
			(!keepAsking))
		{
			std::cout<< "Ship cannot be placed here because it will not fit on the board due to other ships.\n";
			keepAsking = true;
		}

	} while(keepAsking == true);
}

void Game::shipPlacementInteraction(int i, int j, Board* currentPlayerBoard) {
	int shipNum = i;

	if(m_currentPlayer == 1) {
		currentPlayerBoard=m_p1ownBoard;
	} else {
		currentPlayerBoard=m_p2ownBoard;
	}

	std::cout << "Enter the coordinates for player " << j << "'s ship " << i << " (1x" << i << ")\n";

	printCoordinateInteraction(currentPlayerBoard, shipNum);

	if(i > 1) {
		std::cout<<"Given your coordinates, your ship can be placed in the following directions:";
		if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "up")) {
			std::cout<<" up ";
		}
		if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "down")) {
			std::cout<<" down ";
		}
		if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "left")) {
			std::cout<<" left ";
		}
		if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "right")) {
			std::cout<<" right ";
		}

		do {
			std::cout<<"\nIn which direction do you want the ship to be placed (up/down/left/right):";
			std::cin>>userDirection;
			userDirection=convertStringToLower(userDirection);
			if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection) == false) {
				std::cout << "The direction you chose is not open.\n";
			}
		} while((userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right") || (!(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection))));
	} else if(i < 2) {
		userDirection="none";
	}
}

void Game::printPlayerTurn(int player) {
	clearConsole();

	if(player==1) {
	    std::ifstream file_p1_text("ascii/player1.txt");
	    std::cout << getFileContents (file_p1_text) << std::endl;
	} else {
		std::ifstream file_p2_text("ascii/player2.txt");
		std::cout << getFileContents (file_p2_text) << std::endl;
	}
	std::cout << "Press any letter key then hit Enter to continue...";
	std::cin >> wait;
}
