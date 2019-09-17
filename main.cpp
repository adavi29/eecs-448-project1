/*

@file main.cpp
*/
#include "Game.h"
#include <iostream>
#include <string>

int main ()
{

  Game game1;
  try
  {
    game1.setup();
    //game1.run();
    //game1.printWinner(2);
  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }

  //game1.printPlayerBoards(game1.getP1());

  return 0;
}
