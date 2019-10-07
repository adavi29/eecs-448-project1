// -*- C++ -*-
/**
 * @author git-merge:
 *             Zach Pearson
 * @file   asciiart.cpp
 * @date   28 September 2019
 * @brief  Provides methods for ascii art file handler specified in inc/asciiart.h
 */

#include <fstream>

#include "asciiart.h"

std::string AsciiArtHandler::printFileContents(std::ifstream& File) {
    //All lines
    std::string Lines = "";
    //Check if everything is good
    if (File) {
	while (File.good ()) {
	    std::string TempLine;           //Temp line
	    std::getline (File , TempLine); //Get temp line
	    TempLine += "\n";               //Add newline character
	    Lines += TempLine;              //Add newline
	}
	return Lines;
    }
    //Return error
    else {
	return "ERROR File does not exist.";
    }
}
