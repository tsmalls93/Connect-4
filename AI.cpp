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
    AIMove move;
    if (player == CPU){
        move.score = -99999999;
        for(int i = 0; i<7; i++){
            if(!board.slotFull(i)){
                move.slot = i;
                board.dropInSlot(i, CPU); //place marker on imaginary game board
                board.dropInSlot(i, CPU);
                int base = board.checkVictory();
                if (base == CPU){
                    move.score = 99999999;
                    return move;
                }
                else if (base == HUMAN){
                    move.score = -99999999;
                    return move;
                }
                else if (base == TIE){
                    move.score = 0;
                    return move;
                }else if(depth == 10){
                    return board.scoreMove();
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
        move.score = 99999999;
        for(int i=0; i<7; i++){
            if(!board.slotFull(i)){
                move.slot = i;
                board.dropInSlot(i, HUMAN);
                board.dropInSlot(i, HUMAN);
                int base = board.checkVictory();
                if (base == CPU){
                    move.score = 99999999;
                    return move;
                }
                else if (base == HUMAN){
                    move.score = -99999999;
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

//When the computer reaches the depth score the move and return move
    
    
//    int score = 0;
//    //horizontal
//    for (int j = 5; j >= 0; j--) {
//        int count = 0;
//        int spaces = 0;
//        for (int i = 0; i<7; i++) {
//            for (int p=0; p<4; p++){
//                if (board.getPlayerVal(i+p, j) == X_VAL)
//                    count++;
//                if (board.getPlayerVal(i+p, j) == NO_VAL)
//                    spaces++;
//                if (spaces>1)
//                    break;
//                if (board.getPlayerVal(i+p, j)==O_VAL)
//                    break;
//                }
//        }
//        score += 5*count;
//    }
//    //vertical
//    for (int i = 0; i<7; i++) {
//        int count=0;
//        for (int j = 5; j >= 0; j--) {
//            for(int p=0; p<4; p++){
//                if (board.getPlayerVal(i, j+p)==X_VAL)
//                    count++;
//                else
//                    break;
//            }
//        }
//        score += 5*count;
//    }
//    //diagonal
//    for (int j = 0; j<6; j++){
//        int count = 0;
//        int spaces = 0;
//        for (int i = 0; i<7; i++) {
//            for (int p=0; p<4; p++){
//                if(board.getPlayerVal(i+p, j-p)==X_VAL)
//                   count++;
//                if(board.getPlayerVal(i+p, j-p))
//                    spaces++;
//                if(spaces>1)
//                    break;
//            }
//        }
//    score += 5* count;
//    }
//    for (int j = 0; j<6; j++){
//        int count = 0;
//        int spaces = 0;
//        for (int i = 0; i<7; i++) {
//            for (int p=0; p<4; p++){
//                if(board.getPlayerVal(i-p, j-p)==X_VAL)
//                    count++;
//                if(board.getPlayerVal(i-p, j-p))
//                    spaces++;
//                if(spaces>1)
//                    break;
//            }
//        }
//        score += 5* count;
//    }
//    
//    //Enemy
//    //horizontal
//    for (int j = 5; j >= 0; j--) {
//        int count = 0;
//        int spaces = 0;
//        for (int i = 0; i<7; i++) {
//            for (int p=0; p<4; p++){
//                if (board.getPlayerVal(i+p, j) == O_VAL)
//                    count++;
//                if (board.getPlayerVal(i+p, j) == NO_VAL)
//                    spaces++;
//                if (spaces>1)
//                    break;
//                if (board.getPlayerVal(i+p, j)==X_VAL)
//                    break;
//                }
//            }
//            score -= 5*count;
//        }
//        //vertical
//        for (int i = 0; i<7; i++) {
//            int count=0;
//            for (int j = 5; j >= 0; j--) {
//                for(int p=0; p<4; p++){
//                    if (board.getPlayerVal(i, j+p)==O_VAL)
//                        count++;
//                    else
//                        break;
//                }
//            }
//            score -= 5*count;
//        }
//        //diagonal
//        for (int j = 0; j<6; j++){
//            int count = 0;
//            int spaces = 0;
//            for (int i = 0; i<7; i++) {
//                for (int p=0; p<4; p++){
//                    if(board.getPlayerVal(i+p, j-p)==O_VAL)
//                        count++;
//                    if(board.getPlayerVal(i+p, j-p)==NO_VAL)
//                        spaces++;
//                    if(spaces>1)
//                        break;
//                    if(board.getPlayerVal(i+p, j-p)==X_VAL)
//                        break;
//                }
//            }
//            score -= 5* count;
//        }
//        for (int j = 0; j<6; j++){
//            int count = 0;
//            int spaces = 0;
//            for (int i = 0; i<7; i++) {
//                for (int p=0; p<4; p++){
//                    if(board.getPlayerVal(i-p, j-p)==O_VAL)
//                        count++;
//                    if(board.getPlayerVal(i-p, j-p))
//                        spaces++;
//                    if(spaces>1)
//                        break;
//                    if(board.getPlayerVal(i-p, j-p)==X_VAL)
//                        break;
//                }
//            }
//            score -= 5* count;
//        }
//
//    return score;
//}
