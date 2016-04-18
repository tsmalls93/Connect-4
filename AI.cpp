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
    AIMove best = alphaBeta(board, 0, CPU, -999999999, 999999999);
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
    if(depth == 6){
        vector<AIMove> moves;
        for(int i=0; i<7; i++){
            moves.push_back(scoreMove(board, i, player));
        }
        AIMove best;
        best.score = 0;
        if(player==CPU){
            for(int i=0;i<7;i++){
                if(moves[i].score>best.score){
                    best.score = moves[i].score;
                    best.slot = moves[i].slot;
                }
            }
        } else {
            for(int i=0;i<7;i++){
                if(moves[i].score<best.score){
                    best.score = moves[i].score;
                    best.slot = moves[i].slot;
                }
            }
        }
        return best;
    }
    
    vector<AIMove> moves; //store moves
    AIMove move;
    if (player == CPU){
        for(int i = 0; i<7; i++){
            if(!board.slotFull(i)){
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
AIMove AI::scoreMove(Board Board, int slot, int player){
    AIMove move;
    //Ranked top to bottom
    //Check slot position using int Board::getHeightOfSlot(int slot)
    //Or you could see what would happen when you drop it in the slot
    //Basically scan for what a move in this slot would do
    //Look for three in a row to win
    //horizontal
    
    //horizontal disjoint case 1 x xx
    
    //horizontal disjoint case 2 xx x
    
    //vetical
    
    //vertical disjoint case 1
    
    //vertical disjoint case 2
    
    //diagonal
    
    //diagonal disjoint case 1
    
    //diagonal disjoint case 2
    
    
    //
    //Now the enemy three in a row to block
    //horizontal
    
    //horizontal disjoint case 1 x xx
    
    //horizontal disjoint case 2 xx x
    
    //vertical
    
    //vertical disjoint case 1
    
    //vertical disjoint case 2
    
    //diagonal
    
    //diagonal disjoint case 1
    
    //diagonal disjoint case 2
    
    
    //
    //two in a row to make three
    //horizontal
    
    //horizontal disjoint x x
    
    //vertical
    
    //vertical disjoint
    
    //diagonal
    
    //diagonal disjoint
    
    
    //
    //enemy two in a row to block enemy three
    //horizontal
    
    //horizontal disjoint x x
    
    //vertical
    
    //vertical disjoint
    
    //diagonal
    
    //diagonal disjoint
    
    
    //
    //one to make two
    //horizontal
    
    //vertical
    
    //diagonal
    
    //enemy one to block enemy two
    //horizontal
    
    //vertical
    
    //diagonal
    
    //
    //center available?
    
    
    //
    //corner available?
    
    
    
    //Score enemy (negative)
    if (player==X_VAL){
        move.score=-move.score;
    }
    return move;
}
