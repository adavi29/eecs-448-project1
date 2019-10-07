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
#include "statusmessages.h"
#include "asciiart.h"
#include "gamelimits.h"

Game::Game() {

	m_numShips = 0;

	userRow = 0;
	userCol = "";

	arrCol = 0;
	arrRow = 0;

	m_p1oppBoard = new Board();
	m_p1ownBoard = new Board();
	m_p2oppBoard = new Board();
	m_p2ownBoard = new Board();

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

	// TODO: Is there a reason this isn't a member variable?
	Board* currentPlayerBoard = nullptr;

	std::cout << std::endl;
	StatusMessages::PrintBattleship();

	// Explicit this is good because otherwise how can you know where this came from?
	this->m_numShips = Game::AskForNumShips();

	for(int i = 0; i < 2; i++) {
		StatusMessages::PrintPlayerBillboard(i);
		// Explicit namespaces are good. Now I KNOW this function is
		// defined elsewhere in this header instead potentially under
		// some random namespace.
		Game::ContinuePause();
		switch (m_numShips) {
			case 1: {
				StatusMessages::AskToPlaceShips(i, 1);
				userRow = Game::AskForPlacementRow();
				arrRow = userRow - 1;
				//set userDirection=none because ship of size 1 is only one
				//point on the array
				userCol = Game::AskForPlacementCol();
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
				Game::SetUpShips(i, 2, currentPlayerBoard);
				break;
			}
			case 3: {
				Game::SetUpShips(i, 3, currentPlayerBoard);
				break;
			}
			case 4: {
				Game::SetUpShips(i, 4, currentPlayerBoard);
				break;
			}
			case 5: {
				Game::SetUpShips(i, 5, currentPlayerBoard);
				break;
			}
		}
		m_currentPlayer = 2;//change value of current player to 2 for second round of for loop
	}
}

int Game::run() {
	m_p1Ships = new Ships(m_numShips);
	m_p2Ships = new Ships(m_numShips);
	//start game
	system("clear");

	StatusMessages::PrintLetsPlay();
	StatusMessages::PressToContinue();
	std::cin >> wait;

	//loop section
	bool endGame = true;

	while(endGame) {

		//player 1 turn
		StatusMessages::PrintPlayerBillboard(0);
		p1Turn();

		//checks if player 1 has won
		if(m_p2Ships->allSunk()) {
			printWinner(1);
			endGame = false;
			break;
		}

		//player 2 turn
		StatusMessages::PrintPlayerBillboard(1);
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
			StatusMessages::AlreadyShotThere();
		}else{
			break;
		}
	}
	//gets good input from the user

	//checks if isHit() or not
	if(isHit(m_p2ownBoard, p1_attack_row, p1_attack_col)) {
		StatusMessages::ConfirmHit();
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
		StatusMessages::ConfirmMiss();
		m_p1oppBoard->setEntryAtPosition("M", p1_attack_col, p1_attack_row);
	}
	StatusMessages::NextPlayer();
	std::cin >> wait;
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

		if(m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "H" ||
		   m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "M")
		{
			StatusMessages::AlreadyShotThere();
		}
		else{
			break;
		}

	}

	//hit or miss,
	if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)) {
		StatusMessages::ConfirmHit();
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
		StatusMessages::ConfirmMiss();
		m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
	}

	StatusMessages::NextPlayer();
	std::cin >> wait;
}

void Game::printWinner(int player) {
	std::ifstream file_p1_wins ("ascii/player1wins.txt");
	std::ifstream file_p2_wins ("ascii/player2wins.txt");

	if(player == 1) {
		std::cout << AsciiArtHandler::printFileContents (file_p1_wins) << std::endl;
	}else if(player == 2) {
		std::cout << AsciiArtHandler::printFileContents(file_p2_wins) << std::endl;
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

bool Game::checkDirection(Board* board, int row, int col, int shipNum, std::string direction) {
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

bool Game::newCheckDirection(Board* board, int row, int col, int shipNum, Directions direction) {
	bool alwaysFits = true;
	if(direction == NONE) {
		alwaysFits = true;
	} else if(direction == UP) {
		if((row - (shipNum-1)) >= 0) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row-i, col) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	} else if(direction == DOWN) {
		if((row + (shipNum-1)) <= 7) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row+i, col) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	} else if(direction == LEFT) {
		if((col - (shipNum-1)) >= 0) {
			for(int i = 0; i < shipNum; i++) {
				if(isAvailable(board, row, col-i) == false) {
					alwaysFits = false;
				}
			}
		} else {
			alwaysFits = false;
		}
	} else if(direction == RIGHT) {
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

void Game::printCoordinateInteraction(Board* currentPlayerBoard, int shipNum) {
	int userRowChoice = 0;
	bool keepAsking = false;

	do {
		keepAsking = false;
		do {
			std::cout << "Row (1-8):  ";
			std::cin>>userRowChoice;
			if((userRowChoice < ROW_MIN) || (userRowChoice > ROW_MAX)) {
				StatusMessages::ErrorInvalidRow();
			}
		} while((userRowChoice < 1) || (userRowChoice > 8));
		userRow = userRowChoice;
		arrRow = userRow - 1;

		do {
			std::cout << "Col (A-H): ";
			std::cin >> userCol;
			arrCol = convertCol(userCol);
			if(arrCol < 0 || arrCol > 7) {
				StatusMessages::ErrorInvalidCol();
			}
		} while(arrCol < 0 || arrCol > 7);

		if(!isAvailable(currentPlayerBoard, arrRow, arrCol)) {
			StatusMessages::ShipAlreadyThere();
			keepAsking = true;
		}
		if( // TODO: checkEveryDirection which runs all of these and returns false if one is false.
			(!(newCheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, UP))) &&
			(!(newCheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, DOWN))) &&
			(!(newCheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, LEFT))) &&
			(!(newCheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, RIGHT))) &&
			(!keepAsking))
		{
			StatusMessages::ShipInTheWay();
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

	StatusMessages::AskToPlaceShips(m_currentPlayer, i);

	printCoordinateInteraction(currentPlayerBoard, shipNum);

	if(i > 1) {
		StatusMessages::ValidDirs();
		CheckDirections(currentPlayerBoard, shipNum);
		do {
			StatusMessages::AskDirs();
			std::cin>>userDirection;
			userDirection=convertStringToLower(userDirection);
			// TODO Convert input to enum
			if(checkDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection) == false) {
				StatusMessages::PickedInvalidDir();
			}
		} while((userDirection!="up" &&
			 userDirection!="down" &&
			 userDirection!="left" &&
			 // TODO: Convert this to use the enum
			 userDirection!="right") || (!(checkDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection))));
	} else if(i < 2) {
		userDirection="none";
	}
}

void Game::CheckDirections(Board* currentPlayerBoard, int shipNum) {
	std::string directions[5] = {"none", "up", "down", "left", "right"};
	for(int i = 1; i <= 4; i++) {
	        if(newCheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, static_cast<Directions>(i))) {
	                std::cout << " " << directions[i] << " ";
	        };
	}
}

void Game::ContinuePause() {
#ifdef _WIN32
	system("pause");
#elif defined __linux__ //|| defined __APPLE__
	system("wait");
#else
#warning "Unknown platform, falling back to C++ workarounds."
	StatusMessages::PressToContinue();
	std::cin >> wait;
#endif
}

void Game::SetUpShips(int player, int ships, Board* currentPlayerBoard) {
	for(int i = 0; i < ships; i++) {
		std::string shipString=std::to_string(i+1);
		int shipNum=i+1;
		shipPlacementInteraction(i+1, player, currentPlayerBoard);
		if(m_currentPlayer==1) {
			if (isAvailable(m_p1ownBoard, arrRow, arrCol) &&
			    // TODO: Convert this to use the enum
			    checkDirection(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
				addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
				std::cout<<"Player 1's current Board:\n";
				printOwnBoard(m_p1ownBoard);
			}
		} else {
			if (isAvailable(m_p2ownBoard, arrRow, arrCol) &&
			    // TODO: Convert this to use the enum
			    checkDirection(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection)) {
				addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
				std::cout<<"Player 2's current Board:\n";
				printOwnBoard(m_p2ownBoard);
			}
		}
	}
}

int Game::AskForPlacementRow() {
	int userRowChoice = 0;
	do {
		std::cout << "Row (1-8):  ";
		std::cin >> userRowChoice;
		if((userRowChoice < ROW_MIN) || (userRowChoice > ROW_MAX)) {
			StatusMessages::ErrorInvalidRow();
		}
	} while((userRowChoice < ROW_MIN) || (userRowChoice > ROW_MAX));
	return userRowChoice;
}

std::string Game::AskForPlacementCol() {
	std::string userCol;
	do {
		std::cout << "Col (A-H): ";
		std::cin >> userCol;
		arrCol = convertCol(userCol);
		if(arrCol < 0 || arrCol > 7) {
			StatusMessages::ErrorInvalidCol();
		}
	} while(arrCol < 0 || arrCol > 7);
	return userCol;
}

int Game::AskForNumShips() {
	int numShipsChoice = 0;
	do {
		StatusMessages::AskNumShips();
		std::cin >> numShipsChoice;
		if(std::cin.fail()) {
			std::cin.clear();
			numShipsChoice = 0;
		} else {
			if((numShipsChoice < SHIPS_MIN) || (numShipsChoice > SHIPS_MAX)) {
				StatusMessages::ErrorNumShips();
			}
		}
	} while((numShipsChoice < SHIPS_MIN) || (numShipsChoice > SHIPS_MAX));
	return numShipsChoice;
}
