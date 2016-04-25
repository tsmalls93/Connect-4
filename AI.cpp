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
    AIMove alpha, beta;
    alpha.score = INT_MIN;
    alpha.slot = 0;
    beta.score = INT_MAX;
    beta.slot = 0;
    AIMove best = alphaBeta(board, 0, CPU, alpha, beta);
    board.dropInSlot(best.slot, CPU);
}
//Main AI algorithm alphaBeta creates a tree by recursive function calls
//Uses minimax algorithm as well but prunes when beta becomes less than alpha
//At which point it decides that move is no good
AIMove AI::alphaBeta(Board board, int depth, int player, AIMove alpha, AIMove beta){
    AIMove move = *new AIMove();
    if (player == CPU){
        move.score = INT_MIN;
        for(int i = 0; i<7; i++){
            if(!board.slotFull(i)){
                move.slot = i;
                board.dropInSlot(i, CPU); //place marker on imaginary game board
                int base = board.checkVictory();
                if (base == CPU){
                    move.score = INT_MAX;
                    return move;
                }
                else if (base == HUMAN){
                    move.score = INT_MIN;
                    return move;
                }
                else if (base == TIE){
                    move.score = 0;
                    return move;
                }else if(depth == 8){
                    move.score= board.scoreMove();
                    return move;
                }
                AIMove tmp = alphaBeta(board, depth+1, CPU, alpha, beta);
                if (tmp.score > alpha.score){
                    alpha = tmp;
                }
                if (beta.score <= alpha.score)
                    return alpha; // beta cut-off
            }
            
            int j = board.getHeightOfSlot(i);
            board.set(i, j+1, 0);
        }
        return alpha;
    } else {
        move.score = INT_MAX;
        for(int i=0; i<7; i++){
            if(!board.slotFull(i)){
                move.slot = i;
                board.dropInSlot(i, HUMAN);
                int base = board.checkVictory();
                if (base == CPU){
                    move.score = INT_MAX;
                    return move;
                }
                else if (base == HUMAN){
                    move.score = INT_MIN;
                    return move;
                }
                else if (base == TIE){
                    move.score = 0;
                    return move;
                }
                AIMove tmp = alphaBeta(board, depth+1, CPU, alpha, beta);
                if (tmp.score < beta.score)
                    beta = tmp;
                if (beta.score <= alpha.score)
                    return beta; //alpha cut-off
            }
            int j = board.getHeightOfSlot(i);
            board.set(i, j+1, 0);
        }
        return beta;
    }
}

