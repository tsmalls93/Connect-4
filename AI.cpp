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

Board* AI::newGameState() {
    Board* toR = (Board*) malloc(sizeof(Board));
    
    if (toR == NULL)
        return NULL;
    
    toR->weight = 0;
    toR->refs = 1;
    toR->last_move = 0;
    toR->board = *new vector<vector<int>>;
    toR->board.clear();
    
    return toR;
}


int AI::getIncrementForArray(int* arr, int player) {
    int toR = 0;
    int i;
    for (i = 0; i < 4; i++) {
        if (arr[i] == player) {
            toR = 1;
            continue;
        }
        
        if (arr[i] != player && arr[i] != NO_VAL) {
            return 0;
        }
    }
    
    return toR;
}

int AI::countAt(Board board, int x, int y, int player) {
    
    // check across
    int found = 0;
    int buf[4];
    int i;
    
    for (i = 0; i < 4; i++) {
        buf[i] = board.getPlayerVal(x+i, y);
    }
    
    found += getIncrementForArray(buf, player);
    
    // check down
    for (i = 0; i < 4; i++) {
        buf[i] = board.getPlayerVal(x, y+i);
    }
    found += getIncrementForArray(buf, player);
    
    // check diag +/+
    for (i = 0; i < 4; i++) {
        buf[i] = board.getPlayerVal(x+i, y+i);
    }
    found += getIncrementForArray(buf, player);
    
    // check diag -/+
    for (i = 0; i < 4; i++) {
        buf[i] = board.getPlayerVal(x-i, y+i);
    }
    found += getIncrementForArray(buf, player);
    
    return found;
}

int AI::getHeuristic(Board board, int player, int other_player) {
    int toR = 0;
    int x, y;
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 6; y++) {
            toR += countAt(board, x, y, player);
            toR -= countAt(board, x, y, other_player);
        }
    }
    
    return toR;
}

int AI::canMove(Board board, int column) {
    int y;
    for (y = 0; y < 6; y++) {
        if (board.getPlayerVal(column, y)==NO_VAL)
            return 1;
    }
    
    return 0;
}

Board* AI::stateForMove(Board* board, int column, int player) {
    if (board==NULL)
        return NULL;
    Board* toR = new Board();
    toR->init();
    toR->clear();
    memcpy(&toR->board, &board->board, sizeof(vector<vector<int> >));
    toR->dropInSlot(column, player);
    return toR;
}

unsigned long long AI::hashGameState(Board board) {
    unsigned long long hash = 14695981039346656037Lu;
    for (int j = 0; j< 6; j++){
        for (int i = 0; i < 7; i++) {
            hash ^= board.getPlayerVal(i, j);
            hash *= 1099511628211Lu;
        }
    }
    return hash;
}

int AI::isGameStateEqual(Board* board1, Board* board2) {
    for (int j=0; j<6; j++){
        for (int i = 0; i < 7; i++) {
            if (board1->getPlayerVal(i, j) == board2->getPlayerVal(i, j))
            continue;
            return 0;
        }
    }
    
    return 1;
}



TranspositionTable* AI::newTable() {
    int i, j;
    TranspositionTable* toR = (TranspositionTable*) malloc(sizeof(TranspositionTable));
    toR->bins = (Board***) malloc(sizeof(Board**) * TABLE_SIZE);
    for (i = 0; i < TABLE_SIZE; i++) {
        toR->bins[i] = (Board**) malloc(sizeof(Board*) * TABLE_BIN_SIZE);
        for (j = 0; j < TABLE_BIN_SIZE; j++) {
            toR->bins[i][j] = NULL;
        }
    }
    
    return toR;
}

Board* AI::lookupInTable(TranspositionTable* t, Board *k) {
    int hv = hashGameState(*k) % TABLE_SIZE;
    int i;
    Board** bin = t->bins[hv];
    for (i = 0; i < TABLE_BIN_SIZE; i++) {
        if (bin[i] == NULL) {
            return NULL;
        }
        
        if (isGameStateEqual(k, bin[i])) {
            return bin[i];
        }
    }
    return NULL;
}

void AI::addToTable(TranspositionTable* t, Board* k) {
    int hv = hashGameState(*k) % TABLE_SIZE;
    int i;
    Board** bin = t->bins[hv];
    for (i = 0; i < TABLE_BIN_SIZE; i++) {
        if (bin[i] == NULL) {
            bin[i] = k;
            retainGameState(k);
            return;
        }
    }
    
    fprintf(stderr, "Overflow in hash bin %d, won't store GameState\n", hv);
}

void AI::freeTranspositionTable(TranspositionTable* t) {
    int i, j;
    for (i = 0; i < TABLE_SIZE; i++) {
        for (j = 0; j < TABLE_BIN_SIZE; j++) {
            if (t->bins[i][j] != NULL)
                freeGameState(t->bins[i][j]);
        }
        free(t->bins[i]);
    }
    free(t->bins);
    
    free(t);
}

GameTreeNode* AI::newGameTreeNode(Board* gs, int player, int other, int turn, int alpha, int beta, TranspositionTable* ht) {
    GameTreeNode* toR = (GameTreeNode*) malloc(sizeof(GameTreeNode));
    toR->board = gs;
    toR->player = player;
    toR->other_player = other;
    toR->turn = turn;
    toR->alpha = alpha;
    toR->beta = beta;
    toR->best_move = -1;
    toR->ht = ht;
    return toR;
}

int AI::heuristicForState(Board* board, int player, int other) {
    if (board->checkVictory()==TIE)
        return 0;
    
    int term_stat = board->checkVictory();
    if (term_stat == player)
        return 1000;
    
    if (term_stat)
        return -1000;
    
    
    return getHeuristic(*board, player, other);
    
}


// using a global instead of qsort_r because of emscripten support

GameTreeNode* g_node = NULL;


int AI::ascComp(const void* a, const void* b) {
    GameTreeNode* node = g_node;
    return heuristicForState(*(Board**) a, node->player, node->other_player) -
    heuristicForState(*(Board**) b, node->player, node->other_player);
    
}

int AI::desComp(const void* a, const void* b) {
    GameTreeNode* node = g_node;
    return heuristicForState(*(Board**) b, node->player, node->other_player) -
    heuristicForState(*(Board**) a, node->player, node->other_player);
    
}

int AI::getWeight(GameTreeNode* node, int movesLeft) {
    int toR, move, best_weight;
    if (node->board->checkVictory()!=NO_VAL || movesLeft == 0)
        return heuristicForState(node->board, node->player, node->other_player);
    
    Board** possibleMoves = (Board**) malloc(sizeof(Board*) * 7);
    int validMoves = 0;
    for (int possibleMove = 0; possibleMove < 7; possibleMove++) {
        if (!canMove(*node->board, possibleMove)) {
            continue;
        }
        
        possibleMoves[validMoves] = stateForMove(node->board, possibleMove, (node->turn ? node->player : node->other_player));
        validMoves++;
    }
    
    // order possibleMoves by the heuristic
    g_node = node;
    if (node->turn) {
        // qsort_r is apparently non-standard, and won't work with emscripten. So we'll need to use a global.
        std::qsort(possibleMoves, validMoves, sizeof(Board*), ascComp);
    } else {
        std::qsort(possibleMoves, validMoves, sizeof(Board*), desComp);
    }
    
    best_weight = (node->turn ? INT_MIN : INT_MAX);
    
    for (move = 0; move < validMoves; move++) {
        // see if the game state is already in the hash table
        Board* inTable = lookupInTable(node->ht, possibleMoves[move]);
        int child_weight;
        int child_last_move;
        if (inTable != NULL) {
            child_weight = inTable->weight;
            child_last_move = possibleMoves[move]->last_move;
            
        } else {
            GameTreeNode* child = newGameTreeNode(possibleMoves[move], node->player, node->other_player, !(node->turn),
                                                  node->alpha, node->beta, node->ht);
            child_weight = getWeight(child, movesLeft - 1);
            child_last_move = child->board->last_move;
            free(child);
        }
        
        
        
        possibleMoves[move]->weight = child_weight;
        addToTable(node->ht, possibleMoves[move]);
        
        if (movesLeft == LOOK_AHEAD)
            printf("Move %d has weight %d\n", child_last_move, child_weight);
        
        // alpha-beta pruning
        if (!node->turn) {
            // min node
            if (child_weight <= node->alpha) {
                // MAX ensures we will never go here
                toR = child_weight;
                goto done;
            }
            node->beta = (node->beta < child_weight ? node->beta : child_weight);
        } else {
            // max node
            if (child_weight >= node->beta) {
                // MIN ensures we will never go here
                toR = child_weight;
                goto done;
            }
            node->alpha = (node->alpha > child_weight ? node->alpha : child_weight);
        }
        
        if (!(node->turn)) {
            // min node
            if (best_weight > child_weight) {
                best_weight = child_weight;
                node->best_move = child_last_move;
            }
        } else {
            // max node
            if (best_weight < child_weight) {
                best_weight = child_weight;
                node->best_move = child_last_move;
            }
        }
        
        
    }
    toR = best_weight;
done:
    for (int i = 0; i < validMoves; i++) {
        freeGameState(possibleMoves[i]);
    }
    
    free(possibleMoves);
    return toR;
}

int AI::getBestMove(GameTreeNode* node, int movesLeft) {
    getWeight(node, movesLeft);
    return node->best_move;
}



int AI::bestMoveForState(Board* gs, int player, int other_player, int look_ahead) {
    TranspositionTable* t1 = newTable();
    GameTreeNode* n = newGameTreeNode(gs, player, other_player, 1, INT_MIN, INT_MAX, t1);
    int move = getBestMove(n, look_ahead);
    free(n);
    freeTranspositionTable(t1);
    return move;
}

int AI::computerMove(int look_ahead, Board board) {
    return bestMoveForState(&board, CPU, HUMAN, look_ahead);
}

void AI::freeGameState(Board* board) {
    board->refs--;
    if(board->refs <=0)
        board->init();
}

void AI::retainGameState(Board* board) {
    board->refs++;
}
