/*
@file Board.cpp
*/
#include "Board.h"
Board::Board(){
  m_board = new string*[8];
  for(int i=0;i<8;i++){
    m_board[i] = new string[8];
    for(int j=0;j<8;j++){
      m_board[i][j] = " ";
    }
  }
}

Board::~Board(){
  for(int i=0;i<8;i++){
    delete[] m_board[i];
  }
  delete[] m_board;
}

string Board::getEntryAtPosition(int column, int row){
  return(m_board[row][column]);
}

void Board::setEntryAtPosition(string entry, int column, int row){
  m_board[row][column] = entry;
}

void Board::printBoard(){
  int character = 0;
  char letter = 'A';
  for(int i=0;i<8;i++){
    character = int(letter);
    cout<<"     "<<letter;
    character++;
    letter = char(character);
  }
  cout<<"\n";
  for(int i=0;i<8;i++){
    cout<<"  -------------------------------------------------\n";
    cout<<"  |     |     |     |     |     |     |     |     |\n";
    for(int j=0;j<8;j++){
      if(j==0){
        cout<<i+1<<" ";
      }
      cout<<"|  "<<m_board[i][j]<<"  ";
      if(j==7){
        cout<<"|\n";
      }
    }
    cout<<"  |     |     |     |     |     |     |     |     |\n";
    if(i==7){
      cout<<"  -------------------------------------------------\n\n";
    }
  }
}
