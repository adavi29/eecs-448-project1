/*
@file Board.cpp
*/
Board::Board(){
  m_board = new String*[8];
  for(int i=0;i<8;i++){
    m_board[i] = new String[8];
    for(int j=0;j<8;j++){
      m_board[i][j] = " ";
    }
  }
}
Board::~Board(){
  for(int i=0;i<8;i++){
    delete m_board[i];
  }
  delete m_board;
}
String Board::getEntryAtPosition(int column, int row){
  return(m_board[column][row]);
}
void Board::setEntryAtPosition(String entry, int column, int row){
  m_board[column][row] = entry;
}
void Board::printBoard(){

}
bool Board::isHit(int column, int row){

}
