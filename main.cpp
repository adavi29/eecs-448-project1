/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date
 *   @file
 *   @brief
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
    game1.run();
    
  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }
  return 0;
}
