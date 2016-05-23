//
//  MainGame.hpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#ifndef MainGame_h
#define MainGame_h

#include <stdio.h>
#include <iostream>
#include "AI.h"
#include "Board.h"

enum class State { PLAYING, EXIT };
class MainGame {
public:
    // Runs the main loop
    void run();
    
private:
    // Initializes the game
    void init();
    // Performs a human controlled move
    void playerMove(int player);
    // Performs an AI move
    void aiMove();
    // Changes players
    void changePlayer();
    // Ends a game and prompts for quit or re-try
    void endGame(bool wasTie);
    
    // Member Variables
    Board connect4 = *(Board*) malloc(sizeof(Board)); ///< The connect 4 board
    int currentPlayer; ///< The index of the current player
    State gameState; ///< The state of the game
    AI ai; ///< The AI player
};

#endif /* MainGame_h */
