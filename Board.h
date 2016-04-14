//
//  Board.hpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <iostream>
#include <vector>


const int TIE = -1;
// board values
const int NO_VAL = 0;
const int X_VAL = 1;
const int O_VAL = 2;

// Game board class
class Board {
public:
    
    // Initializes the board
    void init();
    // Clears the board
    void clear();
    // Prints the board to standard output
    void print() const;
    
    // If no player won, returns NO_VAL. Otherwise returns X_VAL, O_VAL or TIE_VAL
    int checkVictory() const;
    
    // Drop a coin in the slot
    void dropInSlot(int slot, int player);
    
    // Gets value at x,y spot
    int getPlayerVal(int x, int y) const;
    
    bool slotFull(int slot) const;
    
    int getHeightOfSlot(int slot) const{
        for (int i = 5; i >= 0; i--) {
            if (getPlayerVal(slot, i) == NO_VAL) {
                if(i-1>0)
                    return i-1;
                else
                    return 0;
            }
        }
        return 0;
    }
    
    
    void set(int x, int y, int player){
        board[y][x] = player;
    }
private:
    std::vector<std::vector<int> > board;
};

#endif /* Board_h */
