/**
* @file Board.h
*/
using namespace std;
Class Board{
private:
  String m_board[][];

public:
  Board();
  ~Board();
  String getEntryAtPosition();
  void setEntryAtPosition(String entry, int column, int row);
  void printBoard();
}
