// -*- C++ -*-
/**
* @author Zach Pearson
* @file   statusmessages.cpp
* @date   29 September 2019
* @brief
*/

#include <iostream>
#include <fstream>

#include "asciiart.h"
#include "statusmessages.h"

void StatusMessages::PrintBattleship() {
	std::ifstream file_battleship_text("ascii/battleship.txt");
	std::cout << AsciiArtHandler::printFileContents(file_battleship_text) << std::endl;
}

void StatusMessages::PrintPlayerBillboard(int player) {
	StatusMessages::ClearConsole();
	if(player == 0) {
		std::ifstream file_p1_text("ascii/player1.txt");
		std::cout << AsciiArtHandler::printFileContents(file_p1_text) << std::endl;
	} else {
		std::ifstream file_p2_text("ascii/player2.txt");
		std::cout << AsciiArtHandler::printFileContents(file_p2_text) << std::endl;
	}
}

void StatusMessages::ClearConsole() {
	//A load of end lines to clear the console screen inbetween player turns so they can't cheat
	for(int i = 0; i < 200; i ++) {
		std::cout << std::endl;
	}
	system("clear");
}

void StatusMessages::PrintLetsPlay() {
	std::ifstream file_letsplay_text("ascii/letsplay.txt");
	std::cout << AsciiArtHandler::printFileContents(file_letsplay_text) << std::endl;
}

void StatusMessages::PressToContinue() {
	std::cout << "Press any letter key then hit Enter to continue..." << std::endl;
}

void StatusMessages::AskNumShips() {
	std::cout << "Enter the amount of ships both players want to use "
	          << "(Max: 5): ";
}

void StatusMessages::ErrorNumShips() {
	std::cout << "Invalid number of ships; must be between 1 and 5."
	          << "Try again.\n";
}

void StatusMessages::AskToPlaceShips(int player, int ship) {
	std::cout << "Enter the coordinates for player "
		  << ((player == 0) ? "1" : "2")
		  << "'s";
	switch(ship) {
		default: break;
		case 1: {
			std::cout << " first ship (1x1): ";
			break;
		}
		case 2: {
			std::cout << " second ship (1x2): ";
			break;
		}
		case 3: {
			std::cout << " third ship (1x3): ";
			break;
		}
		case 4: {
			std::cout << " fourth ship (1x4): ";
			break;
		}
		case 5: {
			std::cout << " fifth ship (1x5): ";
			break;
		}
	}
	std::cout << std::endl;
}

void StatusMessages::ErrorInvalidRow() {
	std::cout << "Invalid row; must be in range [1,8]. Please try again."
		  << std::endl;
}

void StatusMessages::ErrorInvalidCol() {
	std::cout << "Invalid row; must be in range [A,H]. Please try again."
		  << std::endl;
}

void StatusMessages::ShipAlreadyThere() {

}

void StatusMessages::ShipInTheWay() {

}

void StatusMessages::AlreadyShotThere() {
	std::cout << "You have already tried to attack there. "
		  << "Pick a different coordinate."
		  << std::endl;
}

void StatusMessages::ConfirmHit() {
	std::cout << "That's a HIT!" << std::endl;
}

void StatusMessages::ConfirmMiss() {
	std::cout << "That's a MISS! Better luck next time." << std::endl;
}

void StatusMessages::NextPlayer() {
	std::cout << "Next Player's Turn. Press any letter key then hit Enter "
		  << "to continue..."
		  << std::endl;
}
