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
        for (int i = 0; i < 6; i++) {
            if (getPlayerVal(slot, i) != NO_VAL) {
                if(i-1>=0)
                    return i;
            }
        }
        return -1;
    }
    
    void set(int x, int y, int player){
        if (x<0 || x>6 || y<0 || y>5)
            return;
        board[y][x] = player;
    }
    int scoreMove();
    int evaluateContent() {
        int evaluationTable[6][7] =
            {{3, 4, 5, 7, 5, 4, 3},
            {4, 6, 8, 10, 8, 6, 4},
            {5, 8, 11, 13, 11, 8, 5},
            {5, 8, 11, 13, 11, 8, 5},
            {4, 6, 8, 10, 8, 6, 4},
            {3, 4, 5, 7, 5, 4, 3}};
        int utility = 138;
        int sum = 0;
        for (int i = 0; i < 6; i++)
            for (int j = 0; j <7; j++)
                if (board[i][j] == 2)
                    sum += evaluationTable[i][j];
                else if (board[i][j] == 1)
                    sum -= evaluationTable[i][j];
        return utility + sum;
    }
private:
    std::vector<std::vector<int> > board;
};

#endif /* Board_h */
