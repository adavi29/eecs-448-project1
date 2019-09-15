/*

@file main.cpp
*/
#include "Game.h"
#include "Board.h"
//#include "Player.h"


int main (){

  Game game1;
  try
  {
    //game1.setup();
    game1.run();
  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }


  //game1.printPlayerBoards(game1.getP1());



  return 0;
}
