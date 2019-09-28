// -*- C++ -*-
/**
* @author Zach Pearson
* @file   asciiart.h
* @date   28 September 2019
* @brief
*/

#ifndef ASCIIART_H
#define ASCIIART_H

#include <fstream>

class AsciiArtHandler {


    public:

	/**
	 * @pre a file exist the contains text
	 * @post reads a txt file and prints the ascii art to the console
	 * @param ifsteram& File - file to print
	 * @return a std::string of the the ascii art
	 */
	static std::string printFileContents(std::ifstream& File);

	private:

};

#endif // ASCIIART_H_
