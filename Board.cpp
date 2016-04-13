//
//  Board.cpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright � 2016 Tyler Small. All rights reserved.
//

#include "Board.h"

void Board::init() {
	board.resize(6);
	for (int i = 0; i<6; i++) {
		board[i].resize(7);
	}
	clear();
}

void Board::clear() {
	for (int j = 0; j<6; j++) {
		for (int i = 0; i<7; i++) {
			//notice j and i order (y and x respectively)
			board[j][i] = NO_VAL;
		}
	}
}

void Board::print() const {
	for (int j = 0; j<6; j++) {
		for (int i = 0; i<7; i++) {
			std::cout << board[j][i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "1 2 3 4 5 6 7" << std::endl;
}

int Board::checkVictory() const {
	bool isTie = true;
    for (int i = 0; i<7; i++) {
        if (!slotFull(i))
            isTie = false;
    }
    if (isTie == true)
        return TIE;
    else{
        
        //Human victory
        //loop through entire board, skip NO_VAL's, and O_VAL's
        //check diagonals, horizontal, and vertical
        //if four X_VAL's in a row, return X_VAL
        
        //horizontal
        for (int j = 5; j >= 0; j--) {
            int count = 0;
            for (int i = 0; i<7; i++) {
                if (getPlayerVal(i, j) == X_VAL) {
                    count++;
                    if (count == 4)
                        break;
                }
                else
                    count = 0;
            }
            if (count >= 4)
                return X_VAL;
        }
        //vertical
        for (int i = 0; i<7; i++) {
            for (int j = 5; j >= 0; j--) {
                if (getPlayerVal(i, j) == X_VAL && getPlayerVal(i, j+1) == X_VAL&& getPlayerVal(i, j+2) == X_VAL&& getPlayerVal(i, j+3) == X_VAL) {
                    return X_VAL;
                }
            }
        }
        //diagonal
        for (int j = 0; j<6; j++){
            for (int i = 0; i<7; i++) {
                if(getPlayerVal(i, j)==X_VAL&&getPlayerVal(i+1, j-1)==X_VAL&&getPlayerVal(i+2, j-2)==X_VAL&&getPlayerVal(i+3, j-3)==X_VAL){
                    return X_VAL;
                }
            }
        }
        for(int j=0; j<6; j++){
            for(int i=0; i<7; i++){
                if(getPlayerVal(i, j)==X_VAL&&getPlayerVal(i-1, j-1)==X_VAL&&getPlayerVal(i-2, j-2)==X_VAL&&getPlayerVal(i-3, j-3)==X_VAL){
                    return X_VAL;
                }
            }
        }

        //Computer victory
        //horizontal
        for (int j = 5; j >= 0; j--) {
            int count = 0;
            for (int i = 0; i<7; i++) {
                if (getPlayerVal(i, j) == O_VAL) {
                    count++;
                    if (count == 4)
                        break;
                }
                else
                    count = 0;
            }
            if (count >= 4)
                return O_VAL;
        }
        //vertical
        for (int i = 0; i<7; i++) {
            for (int j = 5; j >= 0; j--) {
                if (getPlayerVal(i, j) == O_VAL && getPlayerVal(i, j+1) == O_VAL&& getPlayerVal(i, j+2) == O_VAL&& getPlayerVal(i, j+3) == O_VAL) {
                    return O_VAL;
                }
            }
        }
        //diagonal
        for (int j = 0; j<6; j++){
            for (int i = 0; i<7; i++) {
                if(getPlayerVal(i, j)==O_VAL&&getPlayerVal(i+1, j-1)==O_VAL&&getPlayerVal(i+2, j-2)==O_VAL&&getPlayerVal(i+3, j-3)==O_VAL){
                    return O_VAL;
                }
            }
        }
        for(int j=0; j<6; j++){
            for(int i=0; i<7; i++){
                if(getPlayerVal(i, j)==X_VAL&&getPlayerVal(i-1, j-1)==O_VAL&&getPlayerVal(i-2, j-2)==O_VAL&&getPlayerVal(i-3, j-3)==O_VAL){
                    return O_VAL;
                }
            }
        }
        return NO_VAL;
    }
}

void Board::dropInSlot(int slot, int player) {
	if (player == X_VAL) {
		//loop through the rows of the slot
		for (int i = 5; i >= 0; i--) {
			if (getPlayerVal(slot, i) == NO_VAL) {
				board[i][slot] = X_VAL;
				break;
			}
		}
	}
	else {
		for (int i = 5; i >= 0; i--) {
			if (getPlayerVal(slot, i) == NO_VAL) {
				board[i][slot] = O_VAL;
				break;
			}
		}
	}
}

int Board::getPlayerVal(int x, int y) const {
	if (x<0 || x>6 || y<0 || y>5) {
		return NO_VAL;
	}
	else
		return board[y][x];
}

bool Board::slotFull(int slot) const {
	return(board[0][slot] != NO_VAL||board[0][slot]==O_VAL||board[0][slot]==X_VAL);
}