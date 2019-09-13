/**
* @file Board.h
*/
#ifndef BOARD_H
#define BOARD_H

#include<string>
#include<iostream>

using namespace std;
class Board{
private:
  string** m_board;

public:
  Board();
  ~Board();
  string getEntryAtPosition(int column, int row);
  void setEntryAtPosition(string entry, int column, int row);
  void printBoard();
};

#endif
