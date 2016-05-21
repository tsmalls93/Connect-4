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
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define OFF_BOARD -2
#define LOOK_AHEAD 5
#define TABLE_SIZE 32000
#define TABLE_BIN_SIZE 10
class Board;

typedef struct {
    Board*** bins;
} TranspositionTable;

struct AIMove {
    int slot;
    int score;
    AIMove() {};
    AIMove(int Score) : score(Score) {}
};

typedef struct {
    Board* board;
    int player;
    int other_player;
    int turn;
    
    int alpha;
    int beta;
    
    int best_move;
    
    TranspositionTable* ht;
} GameTreeNode;

class AI {
public:
    AI();
    //Perform move given by alphaBeta
    void performMove(Board &board);
    Board* newGameState();
    int static countAt(Board board, int x, int y, int player);
    int static getIncrementForArray(int* arr, int player);
    int static getHeuristic(Board board, int player, int other_player);
    int canMove(Board board, int column);
    Board* stateForMove(Board *board, int column, int player);
    unsigned long long hashGameState(Board board);
    int isGameStateEqual(Board *board1, Board *board2);
    TranspositionTable* newTable();
    Board* lookupInTable(TranspositionTable* t, Board* k);
    void addToTable(TranspositionTable* t, Board* k);
    void freeTranspositionTable(TranspositionTable* t);
    GameTreeNode* newGameTreeNode(Board* gs, int player, int other, int turn, int alpha, int beta, TranspositionTable* ht);
    int static heuristicForState(Board* gs, int player, int other);
    int static ascComp(const void* a, const void* b);
    int static desComp(const void* a, const void* b);
    int getWeight(GameTreeNode* node, int movesLeft);
    int getBestMove(GameTreeNode* node, int movesLeft);
    int bestMoveForState(Board* gs, int player, int other_player, int look_ahead);
    int computerMove(int look_ahead, Board board);
    void retainGameState(Board* board);
    void freeGameState(Board* board);
private:
    //main game tree function (alpha-beta minimax)
    AIMove alphaBeta(Board board, int depth, int player, AIMove alpha, AIMove beta);
    int CPU;
    int HUMAN;
};
#endif /* AI_h */
