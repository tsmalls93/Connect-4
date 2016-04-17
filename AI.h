//
//  AI.hpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#ifndef AI_h
#define AI_h

#include <stdio.h>
#include <cmath>
#include <algorithm>
#include "Board.h"
struct AIMove {
    int slot;
    int score;
    AIMove() {};
    AIMove(int Score) : score(Score) {}
};

class AI {
public:
    //Perform move given by alphaBeta
    AI();
    void performMove(Board &board);
    
private:
    //main game tree function (alpha-beta minimax)
    AIMove alphaBeta(Board board, int depth, int player, int alpha, int beta);
    AIMove scoreMove(Board board, int slot, int player);
    int CPU;
    int HUMAN;
};
#endif /* AI_h */
