/**
* @file Board.h
*/
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
