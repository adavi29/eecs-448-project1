/**
* @file Board.h
*/
#ifndef BOARD_H
#define BOARD_H
<<<<<<< HEAD
=======

>>>>>>> aa5d6fc302e3e6a18d8b9042b872d4d1678ced7f
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
<<<<<<< HEAD
=======

>>>>>>> aa5d6fc302e3e6a18d8b9042b872d4d1678ced7f
#endif
