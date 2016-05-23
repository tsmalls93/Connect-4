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
    //constructor
    AI();
    //Evaluation function passes coordinates, board, player, returns int (score)
    int static countAt(Board* board, int x, int y, int player);
    //finds the amount of connected pieces for a given player in an array, used in countAt
    int static getIncrementForArray(int* arr, int player);
    //performs the evaluation function given the board and the players for the current move
    int static getHeuristic(Board board, int player, int other_player);
    //copies the board and returns said board after a given move
    Board* stateForMove(Board *board, int column, int player);
    //creates a hash value for the board
    unsigned long long hashBoard(Board board);
    //checks to see if two boards are equal
    int isBoardEqual(Board *board1, Board *board2);
    //create new hash table
    TranspositionTable* newTable();
    //find a board in the table
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
    int CPU;
    int HUMAN;
};
#endif /* AI_h */
