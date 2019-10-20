// -*- C++ -*-
/**
 * @author Runtime Terrors:
 *             Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *             Jacob Swearingen, Chongzhi Gao
 *         git-merge:
 *             Zach Pearson
 *	       Brian Clark
 * @date 15 October 2019
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
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "game.h"
#include "board.h"
#include "statusmessages.h"
#include "gamelimits.h"

#define CHARSET_A 65
#define CHARSET_CAPS_GAP 32

Game::Game() {

	// Seed the pseudorandom number generator with the system clock
	// otherwise the "randomness" would be seeded at compile time.
	srand(time(0));

	m_numShips = 0;

	arrCol = 0;
	arrRow = 0;

	AIDifficulty = 0;
	m_p1oppBoard = new Board();
	m_p1ownBoard = new Board();
	m_p2oppBoard = new Board();
	m_p2ownBoard = new Board();
	AI_ownBoard = new Board();
	AI_oppBoard = new Board();
	player1Hits = 0;
	player1Misses = 0;
	player2Hits = 0;
	player2Misses = 0;
	AIHits = 0;
	AIMisses = 0;
	m_currentPlayer = 1;

	p1_usedBigShot = false;
	p2_usedBigShot = false;

	p1_cheatedAlready = false;
	p2_cheatedAlready = false;

#if !defined(__APPLE__) && !defined(__linux__) && !defined (_WIN32)
	wait = "";
#endif
}

Game::~Game() {
	delete m_p2ownBoard;
	delete m_p2oppBoard;
	delete m_p1ownBoard;
	delete m_p1oppBoard;
	if(m_opponentType == AI){
		delete AI_ownBoard;
		delete AI_oppBoard;
	}
	// delete AI_Ships;
	else{
		delete m_p1Ships;
		delete m_p2Ships;
	}
}

void Game::setup() {

    Game::ContinuePause();
	// TODO: Is there a reason this isn't a member variable?
	Board* currentPlayerBoard = nullptr;

	std::cout << std::endl;
	StatusMessages::PrintBattleship();

	// Explicit this is good because otherwise how can you know where this came from?
	this->m_opponentType = static_cast<OpponentType>(Game::AskPlayerType());
	this->m_numShips = Game::AskForNumShips();

	if(m_opponentType == HUMAN) {
		for(int i = 1; i < 3; i++) {
			StatusMessages::PrintPlayerBillboard(i);
			// Explicit namespaces are good. Now I KNOW this function is
			// defined elsewhere in this header instead potentially under
			// some random namespace.
			Game::ContinuePause();
			switch (m_numShips) {
				case 1: {
					StatusMessages::AskToPlaceShips(m_currentPlayer, 1);
					arrRow = Game::AskForPlacementRow() - 1;
					//set userDirection=none because ship of size 1 is only one
					//point on the array
					arrCol = Game::AskForPlacementCol();
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
					Game::SetUpShips(2, currentPlayerBoard);
					break;
				}
				case 3: {
					Game::SetUpShips(3, currentPlayerBoard);
					break;
				}
				case 4: {
					Game::SetUpShips(4, currentPlayerBoard);
					break;
				}
				case 5: {
					Game::SetUpShips(5, currentPlayerBoard);
					break;
				}
			}
			m_currentPlayer = 2; //change value of current player to 2 for second round of for loop
		}
	  }else {
        Game::ContinuePause();
		// Only print Player 1's board and only ask player 1 for their ships
		StatusMessages::PrintPlayerBillboard(0);
		Game::ContinuePause();
		for( int i = 1; i < 3; i++){
		    switch (m_numShips) {
                case 1: {
                    if ( m_currentPlayer == 1){
                        StatusMessages::AskToPlaceShips(1, i);
                        arrRow = Game::AskForPlacementRow() - 1;
                        //set userDirection=none because ship of size 1 is only one
                        //point on the array
                        arrCol = Game::AskForPlacementCol();
                        userDirection=NONE;

                        if (isAvailable(m_p1ownBoard,arrRow, arrCol)) {
                            addShiptoArray("1", arrRow, arrCol, userDirection, 1);
                            std::cout<<"Player 1's current Board:\n";
                            printOwnBoard(m_p1ownBoard);
                        }
                    } else{
                        //AI
                        arrRow = Game::AskForPlacementRow() - 1;
                        arrCol = Game::AskForPlacementCol();
                        if(isAvailable(AI_ownBoard, arrRow, arrCol)){
                            addShiptoArray("1", arrRow, arrCol, NONE, 0);
                            //the ship has been added
                        }
                    }
                    break;
                }
                case 2: {
                    Game::SetUpShips(2, currentPlayerBoard);
                    break;
                }
                case 3: {
                    Game::SetUpShips(3, currentPlayerBoard);
                    break;
                }
                case 4: {
                    Game::SetUpShips(4, currentPlayerBoard);
                    break;
                }
                case 5: {
                    Game::SetUpShips(5, currentPlayerBoard);
                    break;
                }
		    }
		m_currentPlayer = 0; // AI
        }

		// do different logic if the opponent is an AI
		// TODO: Method to ask the user how difficult they want it
		// EASY, REALISTIC, IMPOSSIBLE
		Game::displayAImenu();
	}
}

void Game::displayAImenu() {
	StatusMessages::AIMenu();
	std::cin >> AIDifficulty;
	while (std::cin.fail() ||
	       (AIDifficulty < DIFFICULTY_MIN || AIDifficulty > DIFFICULTY_MAX))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		StatusMessages::InvalidDifficulty();
		std::cin >> AIDifficulty;
	}
}

void Game::displayPlayer1Menu() {
	player1Choice = 0;
	StatusMessages::MoveMenu(1, p1_usedBigShot);
	std::cout << "Please make a selection from the menu: ";
	std::cin >> player1Choice;
	while (std::cin.fail() || player1Choice < 1 || player1Choice > 6) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please make a selection from the menu: ";
		std::cin >> player1Choice;
	}
}

void Game::displayPlayer2Menu() {
	player2Choice = 0;
	StatusMessages::MoveMenu(2, p2_usedBigShot);
	std::cout << "Please make a selection from the menu: ";
	std::cin >> player2Choice;
	while (std::cin.fail() || player2Choice < 1 || player2Choice > 6) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please make a selection from the menu: ";
		std::cin >> player2Choice;
	}
}
void Game::AIEasyShot() {
	int AIRandomRow = (rand()%8);
	int AIRandomColumn = (rand()%8);
	bool shotFired = false;
	std::string shipNum_string;
	int shipNum;
	while(!shotFired) {
		if(AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "H" ||
			AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "M") {
			shotFired = false;
		} else if(AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "1" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "2" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "3" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "4" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "5"){
			StatusMessages::ConfirmHit();
			AIHits++;
			AI_ownBoard->setEntryAtPosition("H", AIRandomColumn, AIRandomRow);

			//decreases the opponents ship on hit and announce if sunk
			shipNum_string = m_p1ownBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow);
			shipNum = std::stoi(shipNum_string);
			m_p1Ships->decreaseSize(shipNum);
			if(m_p1Ships->allSunk()) {
				return;
			}
			//puts an x on the opponnets board
			m_p1ownBoard->setEntryAtPosition("X", AIRandomColumn, AIRandomRow);
			shotFired = true;
		}else{
			StatusMessages::ConfirmMiss();
			AIMisses++;
      m_p1ownBoard->setEntryAtPosition("O", AIRandomColumn, AIRandomRow);
      AI_ownBoard->setEntryAtPosition("M", AIRandomColumn, AIRandomRow);
			shotFired = true;
		}
	}
}

void Game::AIMediumShot() {
	std::string lastShotReminder = " ";
	std::string shipNum_string;
	int shipNum;
	if(lastShotReminder != " ") {
		int row = 0;
		int col = 0;
		bool found = false;
		while(!found) {
			if(col == 7 && row == 7) {
				lastShotReminder = ' ';
				found = true;
			}
			else{
				if(m_p1ownBoard->getEntryAtPosition(col, row) == lastShotReminder) {
					shipNum_string = m_p1ownBoard->getEntryAtPosition(col, row);
					m_p1ownBoard->setEntryAtPosition("X", col, row);
					StatusMessages::ConfirmHit();
					AIHits++;
          shipNum = std::stoi(shipNum_string);
          m_p1Ships->decreaseSize(shipNum);
          if(m_p1Ships->allSunk()) {
              return;
          }
					found = true;
				}
				else{
					if(row != 7) {
						row++;
					}
					if(row == 7) {
						col++;
						row = 0;
					}
				}
			}
		}
	}
	else{
		int AIRandomRow = (rand()%8);
		int AIRandomColumn = (rand()%8);
		if(AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "1" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "2" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "3" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "4" ||
			 AI_oppBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow) == "5"){
			lastShotReminder = m_p1ownBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow);
			StatusMessages::ConfirmHit();
			AIHits++;
			shipNum_string = m_p1ownBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow);
			m_p1ownBoard->setEntryAtPosition("X", AIRandomColumn, AIRandomRow);
			shipNum = std::stoi(shipNum_string);
			m_p1Ships->decreaseSize(shipNum);
			if(m_p1Ships->allSunk()) {
				return;
			}
		}
		else{
			StatusMessages::ConfirmMiss();
			AIMisses++;
			lastShotReminder = m_p1ownBoard->getEntryAtPosition(AIRandomColumn, AIRandomRow);
			m_p1ownBoard->setEntryAtPosition("O", AIRandomColumn, AIRandomRow);
		}
	}
}

void Game::AIHardShot() {
	bool shotFired = false;
  std::string shipNum_string = " ";
  int shipNum = 0;
	while(!shotFired) {
		for(int i = 0;i < 7;i++){
			for(int j = 0;j < 7;j++){
				if(m_p1ownBoard->getEntryAtPosition(i, j) == "1" ||
				 	 m_p1ownBoard->getEntryAtPosition(i, j) == "2" ||
					 m_p1ownBoard->getEntryAtPosition(i, j) == "3" ||
					 m_p1ownBoard->getEntryAtPosition(i, j) == "4" ||
					 m_p1ownBoard->getEntryAtPosition(i, j) == "5"){
							shipNum_string = m_p1ownBoard->getEntryAtPosition(i, j);
							shipNum = std::stoi(shipNum_string);
							m_p1Ships->decreaseSize(shipNum);
							StatusMessages::ConfirmHit();
							AIHits++;
							m_p1ownBoard->setEntryAtPosition("X", i, j);
							return;
				}
			}
		}
	}
}

int Game::run() {
	m_p1Ships = new Ships(m_numShips);
    Ships* opponent_ships = nullptr;
    if (m_opponentType == HUMAN){
        m_p2Ships = new Ships(m_numShips);
        opponent_ships = m_p2Ships;
    }else{
		AI_Ships = new Ships(m_numShips);
        opponent_ships = AI_Ships;
    }
	system("clear");
	StatusMessages::PrintLetsPlay();
	Game::ContinuePause();
	//loop section
	bool endGame = true;
	while(endGame) {
		//player 1 turn
		StatusMessages::PrintPlayerBillboard(0);
        m_currentPlayer = 1;
		p1Turn();
		//checks if player 1 has won
		if(opponent_ships->allSunk()) {
			StatusMessages::PrintWinner(1);
			endGame = false;
			break;
		}
		if(m_opponentType == HUMAN) {
			//player 2 turn
			StatusMessages::PrintPlayerBillboard(1);
      m_currentPlayer = 2;
			p2Turn();
			//checks if player 2 has won
			if(m_p1Ships->allSunk()) {
				StatusMessages::PrintWinner(2);
				endGame = false;
				break;
			}
		} else {
			// TODO: AI run method -- possibly switch(difficulty)?
			//AI turn
      m_currentPlayer = 0;
			AITurn();
      if(m_p1Ships->allSunk()) {
        StatusMessages::PrintAIWinner();
      	std::cout << "The AI opponent has won!\n";
        endGame = false;
        break;
      }
		}
	}
	return 0;
}

void Game::AITurn(){
		std::cout << "It is now the AI players turn!\n";
    if(AIDifficulty == 1){
        AIEasyShot();
				printOwnBoard(m_p1ownBoard);
    }
    else if(AIDifficulty == 2){
        AIMediumShot();
				printOwnBoard(m_p1ownBoard);
    }
    else{
        AIHardShot();
				printOwnBoard(m_p1ownBoard);
    }
}
//run() helper methods
// TODO: Just have a Turn(player) method.
void Game::p1Turn() {
	int p1_attack_row = 0;
	int p1_attack_col = 0;
	std::string shipNum_string;
	int shipNum;
  Board* opponent_own_board = nullptr;
  Ships* opponent_ships = nullptr;
  double opponent_hits;
  double opponent_misses;
  // this if statement sets the opponent's own board
  //depending on whether it is human or AI
  if (m_opponentType == HUMAN){
      opponent_own_board = m_p2ownBoard;
      opponent_ships = m_p2Ships;
      opponent_hits = player2Hits;
      opponent_misses = player2Misses;
  } else {
      //AI
      opponent_own_board = AI_ownBoard;
      opponent_ships = AI_Ships;
      opponent_hits = AIHits;
      opponent_misses = AIMisses;
  }

	//print Board
	printPlayerBoardsSBS(m_p1ownBoard, m_p1oppBoard);

	std::cout << "It's time to attack!" << std::endl;

	// Get input from the user.
	while(1) {
		// TODO: Ensure the player can only do this once, even if they
		// manage to somehow screw up their shot anyway after having
		// seen the other board.
		//if(!p1_cheatedAlready) {
			//StatusMessages::Cheat();
			//std::cin >> intent_to_cheat;
		//}
		//if(!p1_usedBigShot) {
			//StatusMessages::UseBigShot();
			// TODO: Sanitize this input
			//std::cin >> intent_to_use_big_shot;
		//}
		displayPlayer1Menu();
		if(player1Choice == 1) {
			p1_attack_row = AskForPlacementRow() - 1;
			p1_attack_col = AskForPlacementCol();

		// The logic here doesn't change when the player uses the big shot. They shouldn't
		// be able to shoot it at a square that's already marked, true, but they should be
		// able to shoot it at an empty square even if there's a status marker already in
		// one of the boxes in the 3x3 area centered around the shot.
			if(m_p1oppBoard->getEntryAtPosition(p1_attack_col, p1_attack_row) == "H" ||
			 	 m_p1oppBoard->getEntryAtPosition(p1_attack_col, p1_attack_row) == "M") {
				StatusMessages::AlreadyShotThere();
			}
			/* TODO isHit not registering, going straight to the else condition */
			else if(isHit(opponent_own_board, p1_attack_row, p1_attack_col)) {
				StatusMessages::ConfirmHit();
				player1Hits++;
				m_p1oppBoard->setEntryAtPosition("H", p1_attack_col, p1_attack_row);

				//decreases the opponents ship on hit and announce if sunk
				shipNum_string = opponent_own_board->getEntryAtPosition(p1_attack_col, p1_attack_row);
				std::cout << "Ship number: " << shipNum_string << std::endl;
				shipNum = std::stoi(shipNum_string);
				opponent_ships->decreaseSize(std::stoi(shipNum_string));
				if(opponent_ships->allSunk()) {
					return;
				}
				//puts an x on the opponnets board
        opponent_own_board->setEntryAtPosition("X", p1_attack_col, p1_attack_row );
			} else {
				StatusMessages::ConfirmMiss();
				player1Misses++;
				m_p1oppBoard->setEntryAtPosition("M", p1_attack_col, p1_attack_row);
				opponent_own_board->setEntryAtPosition("O", p1_attack_col, p1_attack_row);
			}
			return;
		}
		else if(player1Choice == 2) {
			if(!(p1_usedBigShot)) {
				std::string choice;
				StatusMessages::UseBigShot();
				std::cin >> choice;
				if(choice == "y"){
					p1_attack_row = AskForPlacementRow() - 1;
					p1_attack_col = AskForPlacementCol();
					for(int i = p1_attack_row - 1; i <= p1_attack_row + 1; i++) {
						for(int j = p1_attack_col - 1; j <= p1_attack_col + 1; j++) {
							if(i >= 0 && i <= 7) {
								if(j >= 0 && j <= 7) {
									if(isHit(opponent_own_board, i, j)) {
										StatusMessages::ConfirmHit();
										m_p1oppBoard->setEntryAtPosition("H", j, i);
										//decreases the opponents ship on hit and announces if sunk
	                  shipNum_string = opponent_own_board->getEntryAtPosition(j, i);
										player1Hits++;
										shipNum = std::stoi(shipNum_string);
	                  opponent_ships->decreaseSize(shipNum);
										if(opponent_ships->allSunk()) {
											return;
										}
										//puts an x on the opponnets board
	                  opponent_own_board->setEntryAtPosition("X", j, i);

									} else {
										StatusMessages::ConfirmMiss();
										player1Misses++;
										m_p1oppBoard->setEntryAtPosition("M", j, i);
					                    opponent_own_board->setEntryAtPosition("O", j, i);
									}
								}
							}
						}
					}
					p1_usedBigShot = true;
				}
				else{
					displayPlayer1Menu();
				}
				return;
		} else {
				std::cout << "You've already used your big shot!\n";
			}
		}
		else if(player1Choice == 3) {
			//Display the opponents Board
      opponent_own_board->printBoard();
		}
		else if(player1Choice == 4) {
			if((player1Hits+player1Misses) != 0) {
				std::cout << "-------------------------------------\n";
				std::cout << "HITS: ";
				std::cout << player1Hits << "\n";
				std::cout << "MISSES: " << player1Misses << "\n";
				double hitPercent = (player1Hits/(player1Hits+player1Misses));
				std::cout << "HIT PERCENT: " <<	hitPercent << "%\n";
				std::cout << "-------------------------------------\n";
			}
			else{
				std::cout << "You have not taken a shot yet!\n";
			}
			//displayPlayer1Menu();
		}
		else if(player1Choice == 5){
			if((opponent_hits+opponent_misses) == 0){
				std::cout << "Your opponent has not fired yet!\n";
			}
			else{
				std::cout << "-------------------------------------\n";
				std::cout << "HITS: ";
				std::cout << opponent_hits << "\n";
				std::cout << "MISSES: " << opponent_misses << "\n";
				double hitPercent = (opponent_hits/(opponent_hits+opponent_misses))*100;
				std::cout << "HIT PERCENT: " <<	hitPercent << "%\n";
				std::cout << "-------------------------------------\n";
			}
		}
		else if(player1Choice == 6){
			std::cout << "Goodbye!\n";
			exit(0);
		}
	}
	StatusMessages::NextPlayer();
	Game::ContinuePause();
}

void Game::p2Turn() {
	int p2_attack_row = 0;
	int p2_attack_col = 0;

	std::string shipNum_string;
	int shipNum;

	//print Board
	printPlayerBoardsSBS(m_p2ownBoard, m_p2oppBoard);

	while(1) {
		// TODO: Ensure the player can only do this once, even if they
		// manage to somehow screw up their shot anyway after having
		// seen the other board.
		displayPlayer2Menu();
		if(player2Choice == 1) {
			p2_attack_row = AskForPlacementRow() - 1;
			p2_attack_col = AskForPlacementCol();
		// The logic here doesn't change when the player uses the big shot. They shouldn't
		// be able to shoot it at a square that's already marked, true, but they should be
		// able to shoot it at an empty square even if there's a status marker already in
		// one of the boxes in the 3x3 area centered around the shot.
			if(m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "H" ||
				 m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "M") {
				StatusMessages::AlreadyShotThere();
			}
			else if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)) {
				StatusMessages::ConfirmHit();
				m_p2oppBoard->setEntryAtPosition("H", p2_attack_col, p2_attack_row);
				player2Hits++;
				//decreases the opponents ship on hit and announces if sunk
				shipNum_string = m_p1ownBoard->getEntryAtPosition(p2_attack_col, p2_attack_row);
				shipNum = std::stoi(shipNum_string);
				m_p1Ships->decreaseSize(shipNum);
				if(m_p1Ships->allSunk()) {
					return;
				}

				//puts an x on the opponnets board
				m_p1ownBoard->setEntryAtPosition("X", p2_attack_col, p2_attack_row );
			} else {
				StatusMessages::ConfirmMiss();
				player2Misses++;
				m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
				m_p1ownBoard->setEntryAtPosition("O", p2_attack_col, p2_attack_row);
			}
			return;
		}
		else if(player2Choice == 2) {
			if(!p2_usedBigShot) {
				StatusMessages::UseBigShot();
				p2_attack_row = AskForPlacementRow();
				p2_attack_col = AskForPlacementCol();
				/* First test fired at 3B
				   |A|B|C|D|
				   -|-|-|-|-|-
				   1| | | | | ...
		                   -|-|-|-|-|-
				   2|M| | | | ...
		                   -|-|-|-|-|-
				   3|M| | | | ...
		                   -|-|-|-|-|-
				   4| | | | |
				   -|-|-|-|-|-
				   So we are missing 7 shots
				*/
				for(int i = p2_attack_row - 1; i <= p2_attack_row + 1; i++) {
	 				for(int j = p2_attack_col - 1; j <= p2_attack_col + 1; j++) {
	 					if(i >= 0 && i <= 7) {
	 						if(j >= 0 && j <= 7) {
	 							if(isHit(m_p1ownBoard, i, j)) {
	 								StatusMessages::ConfirmHit();
	 								m_p2oppBoard->setEntryAtPosition("H", j, i);
									player2Hits++;
	 								//decreases the opponents ship on hit and announces if sunk
	 								shipNum_string = m_p1ownBoard->getEntryAtPosition(j, i);
	 								shipNum = std::stoi(shipNum_string);
	 								m_p1Ships->decreaseSize(shipNum);
	 								if(m_p1Ships->allSunk()) {
	 									return;
	 								}

	 								//puts an x on the opponnets board
	 								m_p1ownBoard->setEntryAtPosition("X", j, i);
	 							} else {
	 								StatusMessages::ConfirmMiss();
									player2Misses++;
	 								m_p2oppBoard->setEntryAtPosition("M", j, i);
	 								m_p1ownBoard->setEntryAtPosition("O", j, i);
	 							}
	 						}
	 					}
	 				}
	 			}
	 			p2_usedBigShot = true;
				return;
			} else {
				std::cout << "You've already used your big shot!\n";
			}
		}
		else if(player2Choice == 3) {
			//Display the opponents Board
			m_p1ownBoard->printBoard();
			//displayPlayer2Menu();
		}
		else if(player2Choice == 4) {
			if((player2Hits+player2Misses) != 0) {
				std::cout << "-------------------------------------\n";
				std::cout << "HITS: ";
				std::cout << player2Hits << "\n";
				std::cout << "MISSES: " << player2Misses << "\n";
				double hitPercent = (player2Hits/(player2Hits+player2Misses));
				std::cout << "HIT PERCENT: " <<	hitPercent << "%\n";
				std::cout << "-------------------------------------\n";
			}
			else{
				std::cout << "You have not taken a shot yet!\n";
			}
		}
		else if(player2Choice == 5){
			if((player1Hits+player1Misses) != 0){
				std::cout << "-------------------------------------\n";
				std::cout << "HITS: ";
				std::cout << player1Hits << "\n";
				std::cout << "MISSES: " << player1Misses << "\n";
				double hitPercent = (player1Hits/(player1Hits+player1Misses));
				std::cout << "HIT PERCENT: " <<	hitPercent << "%\n";
				std::cout << "-------------------------------------\n";
			}
			else{
				std::cout << "Your opponent has not fired yet!\n";
			}
		}
		else{
			std::cout << "Goodbye!\n";
			exit(0);
		}
	}
	StatusMessages::NextPlayer();
	Game::ContinuePause();
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

void Game::printPlayerBoardsSBS(Board* ownBoard, Board* oppBoard) {
	std:: cout << "---------------------YOUR-BOARD--------------------- | "
		   << "--------------------THEIR-BOARD---------------------\n";
	for(int i = -1; i < 8; ++i) {
		ownBoard->printBoard(i);
		std::cout << "  | ";
		oppBoard->printBoard(i);
		std::cout << std::endl;
		std::cout << "  -------------------------------------------------";
		std::cout << "  | ";
		std::cout << "  -------------------------------------------------\n";
		if(i < 7) {
			std::cout << "  |     |     |     |     |     |     |     |     |";
			std::cout << "  | ";
			std::cout << "  |     |     |     |     |     |     |     |     |\n";
		}
	}
}

void Game::printOwnBoard(Board* ownBoard) {
	ownBoard->printBoard();
}

void Game::setEntryWrapper(int player, std::string ship, int col, int row) {
	if(player == 1) {
		m_p1ownBoard->setEntryAtPosition(ship, col, row);
	}
	else if(player == 2)	{
		m_p2ownBoard->setEntryAtPosition(ship, col, row);
	}
	else{
		//AI
		AI_ownBoard->setEntryAtPosition(ship, col, row);
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
	bool keepAsking = false;
	do {
		keepAsking = false;
		arrRow = Game::AskForPlacementRow() - 1;
		arrCol = Game::AskForPlacementCol();
		if(!isAvailable(currentPlayerBoard, arrRow, arrCol)) {
			std::cout<< "This coordinate has already been taken. Enter new coordinates:\n";
			keepAsking = true;
		}
		if( // TODO: checkEveryDirection which runs all of these and returns false if one is false.
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, UP))) &&
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, DOWN))) &&
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, LEFT))) &&
			(!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, RIGHT))) &&
			(!keepAsking)){
			std::cout<< "Ship cannot be placed here because it will not fit on the board due to other ships.\n";
			keepAsking = true;
		}
	} while(keepAsking == true);
}

void Game::shipPlacementInteraction(int ship, Board* currentPlayerBoard) {
	int shipNum = ship;
        if (m_currentPlayer){
            if(m_currentPlayer == 1) {
                currentPlayerBoard=m_p1ownBoard;
            } else if (m_currentPlayer == 2) {
                currentPlayerBoard=m_p2ownBoard;
            }
            StatusMessages::AskToPlaceShips(m_currentPlayer, shipNum);
            printCoordinateInteraction(currentPlayerBoard, shipNum);
            if(shipNum > 1) {
                StatusMessages::ValidDirs();
                CheckDirections(currentPlayerBoard, shipNum);
								int dirChoice = 0;
								StatusMessages::AskDirs();
								std::cin >> dirChoice;
                do {
                    // TODO: Sanitize this input
                    userDirection = (Directions)dirChoice;
                    if(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection) == false) {
                        StatusMessages::PickedInvalidDir();
												StatusMessages::AskDirs();
												std::cin >> dirChoice;
                    }
                } while((userDirection != UP && userDirection != DOWN &&
                     userDirection != LEFT && userDirection != RIGHT) ||
                            (!(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection))));
            } else if(shipNum < 2) {
            userDirection=NONE;
            }
        } else{
            //when AI opponent
            currentPlayerBoard=AI_ownBoard;
            printCoordinateInteraction(currentPlayerBoard, shipNum);
            if (shipNum > 1){
                for (int i = 1; i <= 4; i++){
                    userDirection = (Directions)i;
                    if(CheckDirection(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)) {
                        break;
                    }
                }
	    }else{
            userDirection=NONE;
            }
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
	// TODO: BSD?
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

void Game::SetUpShips(int ships, Board* currentPlayerBoard) {
	for(int i = 0; i < ships; i++) {
		std::string shipString=std::to_string(i+1);
		int shipNum=i+1;
		shipPlacementInteraction(i+1, currentPlayerBoard);
		if(m_currentPlayer==1) {
			if (isAvailable(m_p1ownBoard, arrRow, arrCol) &&
			    CheckDirection(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection)) {
				addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
				std::cout<<"Player 1's current Board:\n";
				printOwnBoard(m_p1ownBoard);
			}
		} else if (m_currentPlayer == 2) {
			if (isAvailable(m_p2ownBoard, arrRow, arrCol) &&
			  CheckDirection(m_p2ownBoard, arrRow, arrCol, shipNum, userDirection)) {
					addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
					std::cout<<"Player 2's current Board:\n";
					printOwnBoard(m_p2ownBoard);
				}
		} else{
			//AI
			if(isAvailable(AI_ownBoard, arrRow, arrCol) &&
			  CheckDirection(AI_ownBoard, arrRow, arrCol, shipNum, userDirection)){
				addShiptoArray(shipString, arrRow, arrCol, userDirection, 0);
			}
		}
	}
}

int Game::AskForPlacementRow() {
	int userRowChoice = 0;
	if (m_currentPlayer == 1 or m_currentPlayer == 2){
	    std::cout << "Enter a row number(1-8):  ";
	    std::cin >> userRowChoice;
        while (std::cin.fail() || userRowChoice > ROW_MAX || userRowChoice < ROW_MIN) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            StatusMessages::ErrorInvalidRow();
            std::cin >> userRowChoice;
        }
	}
	else{
	    //current player is AI
	    userRowChoice = (rand()%8)+1;
	}
	return userRowChoice;
}

int Game::AskForPlacementCol() {
	char userColChoice;
	int input_col = -1;
	if(m_currentPlayer == 1 or m_currentPlayer == 2){
	do{
		std::cout << "Enter a column letter (A-H): ";
		std::cin >> userColChoice;
		if(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			StatusMessages::ErrorInvalidCol();
			std::cin >> userColChoice;
		}
		input_col = static_cast<int>(userColChoice) - CHARSET_A;
	    } while(input_col < COL_MIN || input_col > COL_MAX);
	}
	else{
	    //current player is AI
	    input_col = (rand()%8);
  }
	return input_col;
}

int Game::AskForNumShips() {
	int numShipsChoice = 0;
	StatusMessages::AskNumShips();
	std::cin >> numShipsChoice;
	while(std::cin.fail() || numShipsChoice < SHIPS_MIN || numShipsChoice > SHIPS_MAX) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		StatusMessages::ErrorNumShips();
		std::cin >> numShipsChoice;
	}
	return numShipsChoice;
}

int Game::AskPlayerType() {
	int playerChoice = 0;
	StatusMessages::HumanOrAI();
	std::cin >> playerChoice;
	while (std::cin.fail() || (playerChoice > 2 || playerChoice < 1)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		StatusMessages::HumanOrAI();
		std::cin >> playerChoice;
	}
	return playerChoice - 1;
}
