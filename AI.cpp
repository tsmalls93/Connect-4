//
//  AI.cpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//
//

#include "AI.h"
using namespace std;

//Yes I know this is a global, trust me I know what I'm doing
GameTreeNode* g_node = NULL;

AI::AI(){
    HUMAN = X_VAL;
    CPU = O_VAL;
}

int AI::getIncrementForArray(int* arr, int player) {
    int inc = 0;
    int i;
    //count the connected coins for the player in the given array
    for (i = 0; i < 4; i++) {
        if (arr[i] == player) {
            inc = 1;
            continue;
        }
        //other player coin is in the way of a 4 in a row
        if (arr[i] != player && arr[i] != NO_VAL) {
            return 0;
        }
    }
    
    return inc;
}

int AI::countAt(Board* board, int x, int y, int player) {
    //count up all of the connected pieces
    
    // check across
    int found = 0;
    int buf[4];
    int i;
    
    for (i = 0; i < 4; i++) {
        buf[i] = board->getPlayerVal(x+i, y);
    }
    
    found += getIncrementForArray(buf, player);
    
    // check down
    for (i = 0; i < 4; i++) {
        buf[i] = board->getPlayerVal(x, y+i);
    }
    found += getIncrementForArray(buf, player);
    
    // check diag +/+
    for (i = 0; i < 4; i++) {
        buf[i] = board->getPlayerVal(x+i, y+i);
    }
    found += getIncrementForArray(buf, player);
    
    // check diag -/+
    for (i = 0; i < 4; i++) {
        buf[i] = board->getPlayerVal(x-i, y+i);
    }
    found += getIncrementForArray(buf, player);
    
    return found;
}

int AI::getHeuristic(Board board, int player, int other_player) {
    //what is the state of the board?
    int count = 0;
    int x, y;
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 6; y++) {
            count += countAt(&board, x, y, player);
            count -= countAt(&board, x, y, other_player);
        }
    }
    
    return count;
}

Board* AI::stateForMove(Board* board, int column, int player) {
    //drop a coin in a copy of the board
    if (board==NULL || board->board == NULL)
        return NULL;
    Board* temp = new Board();
    temp->init();
    if(temp == NULL)
        return NULL;
    memcpy(temp->board, board->board, sizeof(int*)*7*6);
    temp->dropInSlot(column, player);
    return temp;
}

unsigned long long AI::hashBoard(Board board) {
    //create a hash number for the board
    unsigned long long hash = 14695981039346656037Lu;
    for (int j = 0; j< 6; j++){
        for (int i = 0; i < 7; i++) {
            hash ^= board.getPlayerVal(i, j);
            hash *= 1099511628211Lu;
        }
    }
    return hash;
}

int AI::isBoardEqual(Board* board1, Board* board2) {
    //compare two boards to see if they're equal
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
    //create a new Transposition Table
    //Sorry C++ I want to use malloc not new, no hard feelings
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
    //find the board in the Transposition Table
    int hv = hashBoard(*k) % TABLE_SIZE;
    int i;
    Board** bin = t->bins[hv];
    for (i = 0; i < TABLE_BIN_SIZE; i++) {
        if (bin[i] == NULL) {
            return NULL;
        }
        
        if (isBoardEqual(k, bin[i])) {
            return bin[i];
        }
    }
    return NULL;
}

void AI::addToTable(TranspositionTable* t, Board* k) {
    //add the board to the Transposition Table, the table is for Dynamic Programming
    int hv = hashBoard(*k) % TABLE_SIZE;
    Board** bin = t->bins[hv];
    for (int i = 0; i < TABLE_BIN_SIZE; i++) {
        if (bin[i] == NULL) {
            bin[i] = k;
            retainGameState(k);
            return;
        }
    }
    
    fprintf(stderr, "Overflow in hash bin %d, won't store Board\n", hv);
}

void AI::freeTranspositionTable(TranspositionTable* t) {
    //free up the table
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
    //allocate and setup a new GameTreeNode
    GameTreeNode* node = (GameTreeNode*) malloc(sizeof(GameTreeNode));
    node->board = gs;
    node->player = player;
    node->other_player = other;
    node->turn = turn;
    node->alpha = alpha;
    node->beta = beta;
    node->best_move = -1;
    node->ht = ht;
    return node;
}

int AI::heuristicForBoard(Board* board, int player, int other) {
    //See if there is a winner or just get a general score for the board
    if (board->checkVictory()==TIE)
        return 0;
    
    int term_stat = board->checkVictory();
    if (term_stat == player)
        return 1000;
    
    else if (term_stat == other)
        return -1000;
    
    
    return getHeuristic(*board, player, other);
    
}

int AI::ascComp(const void* a, const void* b) {
    GameTreeNode* node = g_node;
    return heuristicForBoard(*(Board**) a, node->player, node->other_player) -heuristicForBoard(*(Board**) b, node->player, node->other_player);
    
}

int AI::desComp(const void* a, const void* b) {
    GameTreeNode* node = g_node;
    return heuristicForBoard(*(Board**) b, node->player, node->other_player) -
    heuristicForBoard(*(Board**) a, node->player, node->other_player);
    
}

int AI::getWeight(GameTreeNode* node, int movesLeft) {
    //this function is just an alpha-beta algorithm, reference Wikipedia or this will make no sense
    int weight=0, move, best_weight;
    bool breakflag = false;
    if (node->board->checkVictory()!=NO_VAL || movesLeft == 0)
        return heuristicForBoard(node->board, node->player, node->other_player);
    //we have at most 7 possible moves
    Board** possibleMoves = (Board**) malloc(sizeof(Board*) * 7);
    int validMoves = 0;
    //try all of the moves available and store them
    for (int possibleMove = 0; possibleMove < 7; possibleMove++) {
        //ignore full slots
        if (node->board->slotFull(possibleMove)) {
            continue;
        }
        
        possibleMoves[validMoves] = stateForMove(node->board, possibleMove, (node->turn ? node->player : node->other_player));
        validMoves++;
    }
    
    // order possibleMoves by the heuristic (quality)
    g_node = node;
    if (node->turn) { //our turn
        qsort(possibleMoves, validMoves, sizeof(Board*), ascComp);
    } else { //opponent turn
        qsort(possibleMoves, validMoves, sizeof(Board*), desComp);
    }
    //best possible weight is infinity if it is my turn
    //we make it negative infinity for the opposing player
    best_weight = (node->turn ? INT_MIN : INT_MAX);
    
    for (move = 0; move < validMoves; move++) {
        // see if the board is already in the hash table to speed things up otherwise we will have to create a new node
        Board* inTable = lookupInTable(node->ht, possibleMoves[move]);
        int child_weight;
        int child_last_move;
        if (inTable != NULL) {
            //found it in the table, yay for dynamic programming
            child_weight = inTable->weight;
            child_last_move = possibleMoves[move]->last_move;
            
        } else {
            //this board is new, let's allocate a new GameTreeNode and start the recursion
            GameTreeNode* child = newGameTreeNode(possibleMoves[move], node->player, node->other_player, !(node->turn), node->alpha, node->beta, node->ht);
            child_weight = getWeight(child, movesLeft - 1);
            child_last_move = child->board->last_move;
            free(child);
        }
        
        possibleMoves[move]->weight = child_weight;
        addToTable(node->ht, possibleMoves[move]);
        
        //go ahead and print out the weights, so we can see what the computer sees
        if (movesLeft == LOOK_AHEAD){
            printf("Move %d has weight %d\n", child_last_move+1, child_weight);

        }
        // alpha-beta pruning, again go to Wikipedia
        if (!node->turn) {
            // min node
            if (child_weight <= node->alpha) {
                // MAX ensures we will never go here
                weight = child_weight;
                breakflag = true;
                break;
            }
            node->beta = (node->beta < child_weight ? node->beta : child_weight);
        } else {
            // max node
            if (child_weight >= node->beta) {
                // MIN ensures we will never go here
                weight = child_weight;
                breakflag = true;
                break;
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
    //did we break out during the pruning?
    if(!breakflag)
        weight = best_weight;
    
    //cleanup
    for (int i = 0; i < validMoves; i++) {
        freeGameState(possibleMoves[i]);
    }
    
    free(possibleMoves);
    return weight;
}

int AI::getBestMove(GameTreeNode* node, int movesLeft) {
    //check if winning move is available before going into recursion
    Board* temp = new Board();
    temp->init();
    memcpy(temp->board, node->board->board, sizeof(int*)*7*6);
    for (int i = 0; i < 7; i++){
        if (temp->slotFull(i)){
            continue;
        }
        temp->dropInSlot(i, node->player);
        if (temp->checkVictory() == node->player){
            std::cout << "Dropping in slot " << i+1 << " will win the game." << std::endl;
            return i;
        }
        temp->init();
        memcpy(temp->board, node->board->board, sizeof(int*)*7*6);
    }
    //call our alpha-beta algorithm to look into the future based on movesLeft
    getWeight(node, movesLeft);
    return node->best_move;
}



int AI::bestMove(Board* gs, int player, int other_player, int look_ahead) {
    //get the best column to drop our coin in
    TranspositionTable* t1 = newTable();
    GameTreeNode* n = newGameTreeNode(gs, player, other_player, player, INT_MIN, INT_MAX, t1);
    int move = getBestMove(n, look_ahead);
    free(n);
    freeTranspositionTable(t1);
    return move;
}

int AI::computerMove(int look_ahead, Board board) {
    //call our function that allows the computer to cheat the game
    return bestMove(&board, CPU, HUMAN, look_ahead);
}

void AI::freeGameState(Board* board) {
    //decrement the refs and free the given board
    board->refs--;
    if(board->refs <=0){;
        free(board->board);
        free(board);
    }
}

void AI::retainGameState(Board* board) {
    //increment the refs
    board->refs++;
}
