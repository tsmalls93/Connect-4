//
//  AI.cpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#include "AI.h"
using namespace std;

AI::AI(){
    HUMAN = X_VAL;
    CPU = O_VAL;
}

void AI::performMove(Board &board){
    AIMove best = alphaBeta(board, 0, CPU, -INFINITY, INFINITY);
    board.dropInSlot(best.slot, CPU);
}

AIMove AI::alphaBeta(Board board, int depth, int player, int alpha, int beta){
    //Base Case check (win, loss, full board)
    int base = board.checkVictory();
    if (base == CPU)
        return AIMove(10);
    else if (base == HUMAN)
        return AIMove(-10);
    else if (base == TIE)
        return AIMove(0);
    //If max depth reached score the board
    
    
    vector<AIMove> moves; //store moves
    AIMove move;
    if (player == CPU){
        for(int i = 0; i<7; i++){
            if(!board.slotFull(i)){
                if (depth ==5){
                    break;
                }
                move.slot = i;
                board.dropInSlot(i, player); //place marker on imaginary game board
                alpha = max(alpha, alphaBeta(board, depth+1, HUMAN, alpha, beta).score);
                move.score = alpha;
                if (beta <= alpha)
                    break; // beta cut-off
            }
        }
        
        return move;
    } else {
        for(int i=0; i<7; i++){
            if(!board.slotFull(i)){
                if (depth ==5){
                    break;
                }
                move.slot = i;
                board.dropInSlot(i, player);
                beta = min(beta, alphaBeta(board, depth+1, CPU, alpha, beta).score);
                move.score = beta;
                if (beta <= alpha)
                    break; //alpha cut-off
            }
        }
        return move;
    }

}
