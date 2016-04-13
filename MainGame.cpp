//
//  MainGame.cpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright © 2016 Tyler Small. All rights reserved.
//

#include "MainGame.h"

void MainGame::run(){
    init();
    while (gameState != GameState::EXIT){
        connect4.print();
        // Say which player is playing
        if (currentPlayer == X_VAL) {
            printf("Human's turn!\n\n");
            playerMove(X_VAL);
        } else {
            printf("Computer's turn!\n\n");
            aiMove();
        }
        int end = connect4.checkVictory();
        if (end!=NO_VAL){
            endGame(end == TIE);
        } else {
            changePlayer();
            // clear screen
            for (int i = 0; i < 5; i++) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
        }
    }
}

void MainGame::init(){
    gameState = GameState::PLAYING;
    connect4.init();
    currentPlayer = X_VAL;
    std::cout << "Welcome to Connect 4" << std::endl;
}

void MainGame::playerMove(int player){
    int slot;
    std::cout << "Enter slot number: ";
    std::cin >> slot;
    if (!std::cin){
        while(!std::cin){
            std::cin.clear();
            std::cin.ignore(255, '\n');
            std::cout << "Invalid input, try again: ";
            std::cin >> slot;
        }
    } else if (connect4.slotFull(slot-1)){
        while(connect4.slotFull(slot-1)){
            std::cout << "Slot full or invalid! Try again: ";
            std::cin.clear();
            std::cin.ignore(255, '\n');
            std::cin >> slot;
        }
    }
    connect4.dropInSlot(slot-1, player);
}

void MainGame::aiMove(){
    ai.performMove(connect4);
}

void MainGame::changePlayer(){
    if (currentPlayer == X_VAL) {
        currentPlayer = O_VAL;
    } else {
        currentPlayer = X_VAL;
    }
}

void MainGame::endGame(bool wasTie){
    
    connect4.print();
    
    if (wasTie) {
        std::cout << "Tie game! Enter any key to play again, or E to exit: " << std::endl;;
    } else {
        if (currentPlayer == X_VAL) {
            std::cout << "Human wins! Enter any key to play again, or E to exit: " << std::endl;
        } else {
            std::cout << "Computer wins! Enter any key to play again, or E to exit: " << std::endl;
        }
    }
    
    char input;
    std::cin >> input;
    if (input == 'E' || input == 'e') {
        gameState = GameState::EXIT;
    } else {
        // Re init the game
        init();
    }
}


