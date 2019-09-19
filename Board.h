
/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date 9/16/19
 *   @file Board.h
 *   @brief lists all methods for interacting with the game board
 */

#ifndef BOARD_H
#define BOARD_H
#include<string>
#include<iostream>

using namespace std;
class Board{
    
private:
    string** m_board;

public:
    /**
     * @pre  Called to create board object
     * @post Initializes 2D array and sets all entries to a space
     */
    Board();
    /**
     * @pre  Called to delete object
     * @post Deletes the 2D array
     */
    ~Board();
    /**
     * @pre  Valid row and column number
     * @param  Integer denoting a column number
     * @param  Integer denoting a row number
     * @return String containing an entry
     */
    string getEntryAtPosition(int column, int row);
    /**
     * @pre Valid row and column number
     * @post Sets array at given position to the new entry
     * @param String entry for array
     * @param  Integer denoting a column number
     * @param  Integer denoting a row number
     */
    void setEntryAtPosition(string entry, int column, int row);
    /**
     * @pre None
     * @post Prints content of 2D board array
     */
    void printBoard();

};
#endif
