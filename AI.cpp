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
//Main AI algorithm alphaBeta creates a tree by recursive function calls
//Uses minimax algorithm as well but prunes when beta becomes less than alpha
//At which point it decides that move is no good
AIMove AI::alphaBeta(Board board, int depth, int player, int alpha, int beta){
//    //Base Case check (win, loss, full board)
//    int base = board.checkVictory();
//    if (base == CPU)
//        return AIMove(10);
//    else if (base == HUMAN)
//        return AIMove(-10);
//    else if (base == TIE)
//        return AIMove(0);
    //If max depth reached score the board

    
    vector<AIMove> moves; //store moves
    AIMove move;
    if (player == CPU){
        move.score = -99999999;
        for(int i = 0; i<7; i++){
            if(!board.slotFull(i)){
                move.slot = i;
                board.dropInSlot(i, player); //place marker on imaginary game board
                board.dropInSlot(i, player);
                int base = board.checkVictory();
                if (base == CPU){
                    move.score = 10;
                    return move;
                }
                else if (base == HUMAN){
                    move.score = -10;
                    return move;
                }
                else if (base == TIE){
                    move.score = 0;
                    return move;
                }else if(depth == 6){
                    vector<AIMove> moves;
                    for(int i=0; i<7; i++){
                        if(!board.slotFull(i)){
                            moves.push_back(scoreMove(board, i));
                        } else {
                            AIMove no;
                            no.score = -1000;
                            no.slot = i;
                        }
                    }
                    AIMove best;
                    best.score = 0;
                    for(int i=0;i<7;i++){
                        if(moves[i].score>best.score){
                            best.score = moves[i].score;
                            best.slot = moves[i].slot;
                        }
                    }
                    return best;
                }
                move.score = max(alpha, alphaBeta(board, depth+1, HUMAN, alpha, beta).score);
                alpha = max(alpha, move.score);
                if (beta <= alpha)
                    break; // beta cut-off
            }
            int j = board.getHeightOfSlot(i);
            board.set(i, j, 0);
        }
        move.score = alpha;
        return move;
    } else {
        move.score = 99999999;
        for(int i=0; i<7; i++){
            if(!board.slotFull(i)){
                move.slot = i;
                board.dropInSlot(i, player);
                int base = board.checkVictory();
                if (base == CPU){
                    move.score = 10;
                    return move;
                }
                else if (base == HUMAN){
                    move.score = -10;
                    return move;
                }
                else if (base == TIE){
                    move.score = 0;
                    return move;
                }
                move.score = min(beta, alphaBeta(board, depth+1, CPU, alpha, beta).score);
                beta = min(beta, move.score);
                if (beta <= alpha)
                    break; //alpha cut-off
            }
            int j = board.getHeightOfSlot(i);
            board.set(i, j, 0);
        }
        move.score = beta;
        return move;
    }

}
//When the computer reaches the depth score the move and return move
AIMove AI::scoreMove(Board &board, int slot){
    AIMove move;
    move.slot = slot;
    int j = board.getHeightOfSlot(slot);
    //Ranked top to bottom
    //Check slot position using int Board::getHeightOfSlot(int slot)
    //Or you could see what would happen when you drop it in the slot
    //Basically scan for what a move in this slot would do
    //Look for three in a row to win
    //horizontal
    if((board.getPlayerVal(slot+1, j)==CPU&&board.getPlayerVal(slot+2, j)==CPU&&board.getPlayerVal(slot+3, j)==CPU)
       ||(board.getPlayerVal(slot-1, j)==CPU&&board.getPlayerVal(slot-2, j)==CPU&&board.getPlayerVal(slot-3, j)==CPU)){
        move.score = 10;
        return move;
    }
    //horizontal disjoint  x xx and xx x
    if((board.getPlayerVal(slot-1, j)==CPU&&board.getPlayerVal(slot+1, j)==CPU&&board.getPlayerVal(slot+2, j)==CPU)
       ||(board.getPlayerVal(slot-1, j)==CPU&&board.getPlayerVal(slot-2, j)==CPU&&board.getPlayerVal(slot+1, j)==CPU)){
        move.score = 10;
        return move;
    }
    
    //vertical
    if((board.getPlayerVal(slot, j+1)==CPU&&board.getPlayerVal(slot, j+2)==CPU&&board.getPlayerVal(slot, j+3)==CPU)){
            move.score = 10;
            return move;
        }
    //diagonal
    if((board.getPlayerVal(slot+1, j-1)==CPU&&board.getPlayerVal(slot+2, j-2)==CPU&&board.getPlayerVal(slot+3, j-3)==CPU)){
        move.score = 10;
        return move;
    }
    if((board.getPlayerVal(slot-1, j-1)==CPU&&board.getPlayerVal(slot-2, j-2)==CPU&&board.getPlayerVal(slot-3, j-3)==CPU)){
        move.score = 10;
        return move;
    }
    //diagonal disjoint case 1 xx x
    if((board.getPlayerVal(slot-1, j+1)==CPU)&&board.getPlayerVal(slot-2, j+2)==CPU&&board.getPlayerVal(slot+1, j-1)==CPU){
        move.score = 10;
        return move;
    }
    if((board.getPlayerVal(slot+1, j+1)==CPU)&&board.getPlayerVal(slot+2, j+2)==CPU&&board.getPlayerVal(slot-1, j-1)==CPU){
        move.score = 10;
        return move;
    }
    //diagonal disjoint case 2 x xx
    if((board.getPlayerVal(slot-1, j+1)==CPU)&&board.getPlayerVal(slot+1, j-1)==CPU&&board.getPlayerVal(slot+2, j-2)==CPU){
        move.score = 10;
        return move;
    }
    if((board.getPlayerVal(slot+1, j+1)==CPU)&&board.getPlayerVal(slot-1, j-1)==CPU&&board.getPlayerVal(slot-2, j-2)==CPU){
        move.score = 10;
        return move;
    }
    //
    //Now the enemy three in a row to block
    //horizontal
    if((board.getPlayerVal(slot+1, j)==HUMAN&&board.getPlayerVal(slot+2, j)==HUMAN&&board.getPlayerVal(slot+3, j)==HUMAN)
       ||(board.getPlayerVal(slot-1, j)==HUMAN&&board.getPlayerVal(slot-2, j)==HUMAN&&board.getPlayerVal(slot-3, j)==HUMAN)){
        move.score = 9;
        return move;
    }
    //horizontal disjoint  x xx and xx x
    if((board.getPlayerVal(slot-1, j)==HUMAN&&board.getPlayerVal(slot+1, j)==HUMAN&&board.getPlayerVal(slot+2, j)==HUMAN)
       ||(board.getPlayerVal(slot-1, j)==HUMAN&&board.getPlayerVal(slot-2, j)==HUMAN&&board.getPlayerVal(slot+1, j)==HUMAN)){
        move.score = 9;
        return move;
    }
    
    //vertical
    if((board.getPlayerVal(slot, j+1)==HUMAN&&board.getPlayerVal(slot, j+2)==HUMAN&&board.getPlayerVal(slot, j+3)==HUMAN)){
        move.score = 9;
        return move;
    }
    //diagonal
    if((board.getPlayerVal(slot+1, j-1)==HUMAN&&board.getPlayerVal(slot+2, j-2)==HUMAN&&board.getPlayerVal(slot+3, j-3)==HUMAN)){
        move.score = 9;
        return move;
    }
    if((board.getPlayerVal(slot-1, j-1)==HUMAN&&board.getPlayerVal(slot-2, j-2)==HUMAN&&board.getPlayerVal(slot-3, j-3)==HUMAN)){
        move.score = 9;
        return move;
    }
    //diagonal disjoint case 1
    if((board.getPlayerVal(slot-1, j-1)==HUMAN)&&board.getPlayerVal(slot-2, j-2)==HUMAN&&board.getPlayerVal(slot+1, j-1)==CPU){
        move.score = 9;
        return move;
    }
    if((board.getPlayerVal(slot+1, j-1)==HUMAN)&&board.getPlayerVal(slot+2, j-2)==HUMAN&&board.getPlayerVal(slot-1, j-1)==CPU){
        move.score = 9;
        return move;
    }
    //diagonal disjoint case 2
    if((board.getPlayerVal(slot-1, j-1)==HUMAN)&&board.getPlayerVal(slot+1, j-1)==HUMAN&&board.getPlayerVal(slot+2, j-2)==HUMAN){
        move.score = 9;
        return move;
    }
    if((board.getPlayerVal(slot+1, j-1)==HUMAN)&&board.getPlayerVal(slot-1, j-1)==HUMAN&&board.getPlayerVal(slot-2, j-2)==HUMAN){
        move.score = 9;
        return move;
    }
    //
    //two in a row to make three
    //horizontal
    if((board.getPlayerVal(slot+1, j)==CPU&&board.getPlayerVal(slot+2, j)==CPU
        )||(board.getPlayerVal(slot-1, j)==CPU&&board.getPlayerVal(slot-2, j)==CPU)){
        move.score = 8;
        return move;
    }
    //horizontal disjoint x x
    if(board.getPlayerVal(slot-1, j)==CPU&&board.getPlayerVal(slot+1, j)){
        move.score = 8;
        return move;
    }
    //vertical
    if(board.getPlayerVal(slot,j+1) == CPU&&board.getPlayerVal(slot,j+2)==CPU){
        move.score = 8;
        return move;
    }
    //diagonal
    if((board.getPlayerVal(slot+1, j-1)==CPU&&board.getPlayerVal(slot+2, j-2)==CPU)){
        move.score = 8;
        return move;
    }
    if((board.getPlayerVal(slot-1, j-1)==CPU&&board.getPlayerVal(slot-2, j-2)==CPU)){
        move.score = 8;
        return move;
    }
    //diagonal disjoint
    if((board.getPlayerVal(slot+1, j-1)==CPU&&board.getPlayerVal(slot-1, j+1)==CPU)){
        move.score = 8;
        return move;
    }
    
    //
    //enemy two in a row to block enemy three
    //horizontal
    if((board.getPlayerVal(slot+1, j)==HUMAN&&board.getPlayerVal(slot+2, j)==HUMAN
        )||(board.getPlayerVal(slot-1, j)==HUMAN&&board.getPlayerVal(slot-2, j)==HUMAN)){
        move.score = 7;
        return move;
    }
    //horizontal disjoint x x
    if(board.getPlayerVal(slot-1, j)==HUMAN&&board.getPlayerVal(slot+1, j)==HUMAN){
        move.score = 7;
        return move;
    }
    //vertical
    if(board.getPlayerVal(slot,j+1) == HUMAN&&board.getPlayerVal(slot,j+2)==HUMAN){
        move.score = 7;
        return move;
    }
    //diagonal
    if((board.getPlayerVal(slot+1, j-1)==HUMAN&&board.getPlayerVal(slot+2, j-2)==HUMAN)){
        move.score = 7;
        return move;
    }
    if((board.getPlayerVal(slot-1, j-1)==HUMAN&&board.getPlayerVal(slot-2, j-2)==HUMAN)){
        move.score = 7;
        return move;
    }
    //diagonal disjoint
    if((board.getPlayerVal(slot+1, j-1)==HUMAN&&board.getPlayerVal(slot-1, j+1)==HUMAN)){
        move.score = 7;
        return move;
    }
    
    //
    //one to make two
    //horizontal
    if((board.getPlayerVal(slot+1, j)==CPU)||(board.getPlayerVal(slot-1, j)==CPU)){
        move.score = 6;
        return move;
    }
    //vertical
    if((board.getPlayerVal(slot, j+1)==CPU)){
        move.score = 6;
        return move;
    }
    //diagonal
    if((board.getPlayerVal(slot-1, j+1)==CPU)||(board.getPlayerVal(slot+1,j+1)==CPU)){
        move.score = 6;
        return move;
    }
    //enemy one to block enemy two
    //horizontal
    if((board.getPlayerVal(slot+1, j)==HUMAN)||(board.getPlayerVal(slot-1, j)==HUMAN)){
        move.score = 5;
        return move;
    }
    //vertical
    if((board.getPlayerVal(slot, j+1)==HUMAN)){
        move.score = 5;
        return move;
    }
    //diagonal
    if((board.getPlayerVal(slot-1, j+1)==HUMAN)||(board.getPlayerVal(slot+1,j+1)==HUMAN)){
        move.score = 5;
        return move;
    }
    //
    //center available?
    
    //
    //corner available?
    
    //Score enemy (negative)
    if (CPU==X_VAL){
        move.score=-move.score;
    }
    return move;
}
