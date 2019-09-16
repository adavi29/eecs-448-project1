/*

@file main.cpp
*/
#include "Game.h"
<<<<<<< HEAD
#include <iostream>
#include <string>
int main()
{
  
=======
#include "Board.h"
//#include "Player.h"


int main (){

  Game game1;
  try
  {
    game1.setup();
    game1.run();
    //game1.printWinner(2);
  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }

  //game1.printPlayerBoards(game1.getP1());



>>>>>>> aa5d6fc302e3e6a18d8b9042b872d4d1678ced7f
  return 0;
}
