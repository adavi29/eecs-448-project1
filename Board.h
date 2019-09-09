/*
@file Board.h
*/

Class Board{
private:
  String m_board[][];

public:
  gameBoard();
  ~gameBoard();
  String getEntryAtPosition();
  void setEntryAtPosition(String entry, String coordinate);
  printBoard();
}
