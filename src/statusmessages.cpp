// -*- C++ -*-
/**
 * @author git-merge:
 *             Zach Pearson
 * @file   statusmessages.cpp
 * @date   29 September 2019
 * @brief
 */

#include <iostream>
#include <fstream>

#include "asciiart.h"
#include "statusmessages.h"
#include "gamelimits.h"

void StatusMessages::PrintBattleship() {
	std::ifstream file_battleship_text("ascii/battleship.txt");
	std::cout << AsciiArtHandler::printFileContents(file_battleship_text) << std::endl;
}

void StatusMessages::PrintAIWinner() {
	std::ifstream file_AIWins_text("ascii/AIWins.txt");
	std::cout << AsciiArtHandler::printFileContents(file_AIWins_text) << std::endl;
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

void StatusMessages::PressAnyContinue() {
	std::cout << "Press any key to continue..." << std::endl;
}

void StatusMessages::ErrorNumShips() {
	std::cout << "Invalid number of ships; must be between 1 and 5."
	          << "Try again.\n";
}

void StatusMessages::AskToPlaceShips(int player, int ship) {
	std::cout << "Enter the coordinates for player "
		  << ((player == 1) ? "1" : "2")
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
	std::cout << "Invalid column; must be in range [A,H]. Please try again."
		  << std::endl;
}

void StatusMessages::ShipAlreadyThere() {
	std::cout<< "This coordinate has already been taken. Enter new coordinates:\n";
}

void StatusMessages::ShipInTheWay() {
	std::cout<< "Ship cannot be placed here because it will not fit on the board due to other ships.\n";
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

void StatusMessages::ValidDirs() {
	std::cout << "Given your coordinates, your ship can be placed in the following directions: ";
}

void StatusMessages::AskDirs() {
	std::cout<<"\nIn which direction do you want the ship to be placed (1 - up/2 - down/3 - left/4 - right):";
}

void StatusMessages::PickedInvalidDir() {
	std::cout << "The direction you chose is not open.\n";
}

void StatusMessages::HumanOrAI() {
	std::cout << "Are you playing against a human, or would you like an AI opponent?\n"
		  << "Enter '1' for a human opponent, or '2' for AI: ";
}

void StatusMessages::AskNumShips() {
	std::cout << "Enter a number of ships in range ["
		  << SHIPS_MIN
		  << ","
		  << SHIPS_MAX
		  << "]: ";
}

void StatusMessages::PrintWinner(int player) {
	std::ifstream file_p1_wins ("ascii/player1wins.txt");
	std::ifstream file_p2_wins ("ascii/player2wins.txt");

	if(player == 1) {
		std::cout << AsciiArtHandler::printFileContents (file_p1_wins) << std::endl;
	} else if(player == 2) {
		std::cout << AsciiArtHandler::printFileContents(file_p2_wins) << std::endl;
	}
}

void StatusMessages::UseBigShot() {
	std::cout << "Use 3x3 Big Shot? (y/N): ";
}

void StatusMessages::Cheat() {
	std::cout << "Use your one opportunity to view opponent's board? (y/N): ";
}

void StatusMessages::AIMenu() {
	std::cout << "Please select a level of difficulty for the AI opponent: \n"
		  << "1. Easy (the AI shoots randomly every turn)\n"
		  << "2. Realistic (the AI fires randomly until a ship is found)\n"
		  << "3. Impossible (the AI never misses a shot!)\n";
}

void StatusMessages::InvalidDifficulty() {
	std::cout << "Invalid difficulty level selected; please try again.\n";
}

void StatusMessages::MoveMenu(int player, bool bigShot) {
	std::cout << (player == 1 ? "\nPlayer 1\n" : "\nPlayer 2\n")
		  << "Please select from the following options: \n"
		  << "1. Take a shot\n"
		  << "2. Take a BIG (3x3) shot (";
	if(player == 1) {
		if(!bigShot) {
			std::cout << "1 remaining)\n";
		}
		else{
			std::cout << "0 remaining)\n";
		}
	} else {
		if(!bigShot) {
			std::cout << "1 remaining)\n";
		}
		else{
			std::cout << "0 remaining)\n";
		}
	}
	std::cout << "3. View opponents board\n"
		  << "4. View your scoreboard\n"
		  << "5. View opponent's scoreboard.\n"
		  << "6. Exit the game.\n"
}
