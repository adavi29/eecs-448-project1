// -*- C++ -*-
/**
 * @author Runtime Terrors:
 *             Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *             Jacob Swearingen, Chongzhi Gao
 *         git-merge:
 *             Zach Pearson
 * @date 06 October 2019
 * @file Board.cpp
 * @brief prints out game board and edits board entries
 */

#include "board.h"

Board::Board() {
	m_board = new std::string*[8];
	for(int i = 0; i < 8; i++) {
		m_board[i] = new std::string[8];
		for(int j = 0; j < 8; j++) {
			m_board[i][j] = " ";
		}
	}
}

Board::~Board() {
	for(int i = 0; i < 8; i++) {
		delete[] m_board[i];
	}
	delete[] m_board;
}

std::string Board::getEntryAtPosition(int column, int row) {
	return(m_board[row][column]);
}

void Board::setEntryAtPosition(std::string entry, int column, int row) {
	m_board[row][column] = entry;
}

void Board::printBoard() {
	int character = 0;
	char letter = 'A';
	for(int i = 0; i < 8; i++) {
		character = int(letter);
		std::cout << "     " << letter;
		character++;
		letter = (char)character;
	}
	std::cout << "\n";
	for(int i = 0; i < 8; i++) {
		std::cout << "  -------------------------------------------------\n";
		std::cout << "  |     |     |     |     |     |     |     |     |\n";
		for(int j = 0; j < 8; j++) {
			if(j == 0) {
				std::cout << i+1 << " ";
			}
			std::cout << "|  " << m_board[i][j] << "  ";
			if(j == 7) {
				std::cout<<"|\n";
			}
		}
		if(i == 7) {
			std::cout << "  -------------------------------------------------\n\n";
		}
	}
}
