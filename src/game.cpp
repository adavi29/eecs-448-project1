// -*- C++ -*-
/**
 * @author Runtime Terrors:
 *             Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *             Jacob Swearingen, Chongzhi Gao
 *         git-merge:
 *             Zach Pearson
 * @date 6 October 2019
 * @file game.cpp
 * @brief implemented methods needed for game play from header file
 */

#include <stdexcept>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>

#include "game.h"
#include "board.h"
#include "statusmessages.h"
#include "gamelimits.h"

#define CHARSET_A 65
#define CHARSET_CAPS_GAP 32

Game::Game() {

	m_numShips = 0;

	userRow = 0;
	userCol = '0';

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

void Game::setup() {

	// TODO: Is there a reason this isn't a member variable?
	Board* currentPlayerBoard = nullptr;

	std::cout << std::endl;
	StatusMessages::PrintBattleship();

	// Explicit this is good because otherwise how can you know where this came from?
	this->m_opponentType = static_cast<OpponentType>(Game::AskPlayerType());
	this->m_numShips = Game::AskForNumShips();

	if(m_opponentType == HUMAN) {
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
					userDirection=NONE;
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
					//TODO: While the game logic is sound, after this point the game displays
					// "setting player 2's ship x" for both players.
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
			m_currentPlayer = 2; //change value of current player to 2 for second round of for loop
		}
	} else {
		// do different logic if the opponent is an AI
	}
}

int Game::run() {
	m_p1Ships = new Ships(m_numShips);
	m_p2Ships = new Ships(m_numShips);

	system("clear");

	StatusMessages::PrintLetsPlay();
	Game::ContinuePause();

	//loop section
	bool endGame = true;

	while(endGame) {

		//player 1 turn
		StatusMessages::PrintPlayerBillboard(0);
		p1Turn();

		//checks if player 1 has won
		if(m_p2Ships->allSunk()) {
			StatusMessages::PrintWinner(1);
			endGame = false;
			break;
		}

		if(m_opponentType == HUMAN) {
			//player 2 turn
			StatusMessages::PrintPlayerBillboard(1);
			p2Turn();

			//checks if player 2 has won
			if(m_p1Ships->allSunk()) {
				StatusMessages::PrintWinner(2);
				endGame = false;
				break;
			}
		} else {
			// For now if this is fucked up we'll just immediately end
			StatusMessages::PrintWinner(2);
			endGame = false;
			break;
		}
	}
	return 0;
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
		} else {
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
	char input;
	int input_num = 0;
	while(1) {
		std::cout << "Enter Column(A-H): ";
		std::cin >> input;
		input_num = static_cast<int>(input) - CHARSET_A;
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
	ownBoard->printBoard();
}

void Game::setEntryWrapper(int player, std::string ship, int col, int row) {
	if(player == 1) {
		m_p1ownBoard->setEntryAtPosition(ship, col, row);
	} else {
		m_p2ownBoard->setEntryAtPosition(ship, col, row);
	}
}

// TODO: Unstringify ship or add ship enum to collapse elses into a single statement
// ex. for(size_t i = 0; i < static_cast<int>(shipSize); i++) { ... }
void Game::addShiptoArray(std::string ship, int row, int col, Directions direction, int player) {
//direction=none means plastd::cing m_ship1 on the board: 1x1 size
	if(direction == NONE) {
		setEntryWrapper(player, ship, col, row);
	}
	else if(direction == UP) {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				Game::setEntryWrapper(player, ship, col, row-i);
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				Game::setEntryWrapper(player, ship, col, row-i);
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				Game::setEntryWrapper(player, ship, col, row-i);
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				Game::setEntryWrapper(player, ship, col, row-i);
			}
		}
	}
	else if(direction == DOWN) {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				Game::setEntryWrapper(player, ship, col, row+i);
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				Game::setEntryWrapper(player, ship, col, row+i);
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				Game::setEntryWrapper(player, ship, col, row+i);
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				Game::setEntryWrapper(player, ship, col, row+i);
			}
		}
	}
	else if(direction == LEFT) {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				Game::setEntryWrapper(player, ship, col-i, row);
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				Game::setEntryWrapper(player, ship, col-i, row);
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				Game::setEntryWrapper(player, ship, col-i, row);
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				Game::setEntryWrapper(player, ship, col-i, row);
			}
		}
	}
	//happens if direction is "right"
	else {
		if(ship == "2") {
			for(int i = 0; i < 2; i++) {
				Game::setEntryWrapper(player, ship, col+i, row);
			}
		}
		else if(ship == "3") {
			for(int i = 0; i < 3; i++) {
				Game::setEntryWrapper(player, ship, col+i, row);
			}
		}
		else if(ship == "4") {
			for(int i = 0; i < 4; i++) {
				Game::setEntryWrapper(player, ship, col+i, row);
			}
		}
		else if(ship == "5") {
			for(int i = 0; i < 5; i++) {
				Game::setEntryWrapper(player, ship, col+i, row);
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

bool Game::CheckDirection(Board* board, int row, int col, int shipNum, Directions direction) {
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
			arrCol = static_cast<int>(userCol) - CHARSET_A;
			if(arrCol < 0 || arrCol > 7) {
				StatusMessages::ErrorInvalidCol();
			}
		} while(arrCol < 0 || arrCol > 7);

		if(!isAvailable(currentPlayerBoard, arrRow, arrCol)) {
			std::cout<< "This coordinate has already been taken. Enter new coordinates:\n";
			keepAsking = true;
		}
		if( // TODO: checkEveryDirection which runs all of these and returns false if one is false.
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, UP))) &&
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, DOWN))) &&
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, LEFT))) &&
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, RIGHT))) &&
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

	StatusMessages::AskToPlaceShips(m_currentPlayer, i);

	printCoordinateInteraction(currentPlayerBoard, shipNum);

	if(i > 1) {
		StatusMessages::ValidDirs();
		CheckDirections(currentPlayerBoard, shipNum);
		do {
			int dirChoice = 0;
			StatusMessages::AskDirs();
			// TODO: Sanitize this input
			std::cin >> dirChoice;
			userDirection = (Directions)dirChoice;
			if(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection) == false) {
				StatusMessages::PickedInvalidDir();
			}
		} while((userDirection != UP && userDirection != DOWN &&
			 userDirection != LEFT && userDirection != RIGHT) ||
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection))));
	} else if(i < 2) {
		userDirection=NONE;
	}
}

void Game::CheckDirections(Board* currentPlayerBoard, int shipNum) {
	std::string directions[5] = {"none", "up", "down", "left", "right"};
	for(int i = 1; i <= 4; i++) {
	        if(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, static_cast<Directions>(i))) {
	                std::cout << " " << directions[i] << " ";
	        };
	}
}

void Game::ContinuePause() {
	// Portable implementation of "Press any key to continue..." that
	// changes to adapt to different platforms.
#ifdef _WIN32
	system("pause");
#elif defined __linux__ || defined __APPLE__
	// -s silent don't echo chars -n # chars to read before return
	StatusMessages::PressAnyContinue();
	system("read -sn 1");
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
			    CheckDirection(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
				addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
				std::cout<<"Player 1's current Board:\n";
				printOwnBoard(m_p1ownBoard);
			}
		} else {
			if (isAvailable(m_p2ownBoard, arrRow, arrCol) &&
			    CheckDirection(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection)) {
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
		// TODO: Sanitize this input
		std::cin >> userRowChoice;
		if(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			StatusMessages::ErrorInvalidRow();
			std::cin >> userRowChoice;
		}
		if((userRowChoice < ROW_MIN) || (userRowChoice > ROW_MAX)) {
			StatusMessages::ErrorInvalidRow();
		}
	} while((userRowChoice < ROW_MIN) || (userRowChoice > ROW_MAX));
	return userRowChoice;
}

char Game::AskForPlacementCol() {
	char userCol;
	do {
		std::cout << "Col (A-H): ";
		// TODO:: Sanitize this input
		std::cin >> userCol;
		arrCol = static_cast<int>(userCol) - CHARSET_A;
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
		// TODO: Sanitize this input
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

int Game::AskPlayerType() {
	char playerChoice = '\0';
	StatusMessages::HumanOrAI();
	do {
		std::cin >> playerChoice;
		if(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			StatusMessages::HumanOrAI();
			std::cin >> playerChoice;
		}
		// hacky version of toLower()
		if(playerChoice < 97) {
			playerChoice = static_cast<char>(static_cast<int>(playerChoice) + CHARSET_CAPS_GAP);
		}
	} while(playerChoice != 'h' && playerChoice != 'a');
	if(playerChoice == 'h') {
		return 0;
	} else {
		return 1;
	}
}
