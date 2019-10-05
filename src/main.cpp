/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke,
 *           Jacob Swearingen, Chongzhi Gao)
 *   @date 9/20/19
 *   @file main.cpp
 *   @brief calls game setup and run
 */

#include "game.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	if(argc > 2) {
		std::cout << "There are no command-line args. Ignoring input..."
			  << std::endl;
	}
	Game the_game; // Gotcha, sucka!
	try {
		the_game.setup();
		//TODO: Return the_game.run() 1 if bad exit 0 if good.
		return the_game.run();
	}
	catch(std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
