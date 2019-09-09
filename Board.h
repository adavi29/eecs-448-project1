/**
* @file Board.h
*/
using namespace std;
Class Board{
private:
  String** m_board;

public:
  Board();
  ~Board();
  String getEntryAtPosition(int column, int row);
  void setEntryAtPosition(String entry, int column, int row);
  void printBoard();
  bool isHit(int column, int row);
}
