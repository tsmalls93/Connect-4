//
//  Board.cpp
//  connect4
//
//  Created by Tyler Small on 4/10/16.
//  Copyright � 2016 Tyler Small. All rights reserved.
//

#include "Board.h"
//Set size of board
void Board::init() {
	board.resize(6);
	for (int i = 0; i<6; i++) {
		board[i].resize(7);
	}
	clear();
}
//Clear the board
void Board::clear() {
	for (int j = 0; j<6; j++) {
		for (int i = 0; i<7; i++) {
			//notice j and i order (y and x respectively)
			board[j][i] = NO_VAL;
		}
	}
}
//Print the board
void Board::print() const {
	for (int j = 0; j<6; j++) {

		for (int i = 0; i<7; i++) {
                std::cout << "(";
            if (getPlayerVal(i, j)==NO_VAL)
                std::cout << " " << ")";
            else if(getPlayerVal(i, j)==X_VAL){
                std::cout << "X" << ")";
            } else {
                std::cout << "O" << ")";
            }
		}
		std::cout << std::endl;
	}
	std::cout << " 1  2  3  4  5  6  7" << std::endl;
}
//Is the game over?
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
                if(getPlayerVal(i, j)==O_VAL&&getPlayerVal(i-1, j-1)==O_VAL&&getPlayerVal(i-2, j-2)==O_VAL&&getPlayerVal(i-3, j-3)==O_VAL){
                    return O_VAL;
                }
            }
        }
        return NO_VAL;
    }
}
//Stack values on top of each other
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
//Get the value of the board position
int Board::getPlayerVal(int x, int y) const {
	if (x<0 || x>6 || y<0 || y>5) {
		return -1;
	}
	else
		return board[y][x];
}
//Is the slot full?
bool Board::slotFull(int slot) const {
	return(board[0][slot] != NO_VAL||board[0][slot]==O_VAL||board[0][slot]==X_VAL);
}

int Board::scoreMove(){
    int whoWon = 0;
    // Horizontal one moves Player 1
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3, row) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3, row) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 0 &&getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3, row) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3, row) == 1) {
                whoWon = whoWon - 125;
            }
        }
    }

    //end
    
    //Vertical One Moves Player 1;
    for(int col=0;col<7;col++){
        int row = getHeightOfSlot(col);
        if(getPlayerVal(col,row)==1){
            whoWon -=125;
        }
    }

    //Diagonal one moves Player 1
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 125;
            }
        }
    }
    //switch slope
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3)  == 1) {
                whoWon = whoWon - 125;
            }
        }
    }
    //end
    
    // Horizontal one moves Player Two
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row)== 0 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 2 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 2) {
                whoWon = whoWon + 125;
            }
        }
    }
    //end
    //Vertical one moves Player 2
    for(int col=0;col<7;col++){
        int row = getHeightOfSlot(col);
        if(getPlayerVal(col,row)==2){
            whoWon +=125;
        }
    }
    //end
    //Diagonal one moves Player 2
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 2 && getPlayerVal(col=2,row+2) == 0 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 125;
            }
        }
    }
    //switch slope
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col-1,row+1)== 0 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 2 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3)== 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 2 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon + 125;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 125;
            }
        }
    }
    //end
    
    //Horizontal Two Moves Player One
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row)==0 &&getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3,row) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row)== 0 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    //end
    
    //Vertical Two moves Player One
    for(int col=0;col<7;col++){
        int row = getHeightOfSlot(col);
        if(getPlayerVal(col,row)==1 && getPlayerVal(col,row+1)==1){
            whoWon -=250;
        }
    }
    //end

    //Diagonal two moves Player One
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3)== 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    //switch slope
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 &&getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 1) {
                whoWon = whoWon - 250;
            }
        }
    }
    
    //end
    
    //Horizontal Two Moves Player Two
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 2 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row)== 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row)== 0) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 2 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row)  == 0 && getPlayerVal(col+3,row) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    //end
    
    //Vertical Two moves Player Two
    for(int col=0;col<7;col++){
        int row = getHeightOfSlot(col);
        if(getPlayerVal(col,row)==2 && getPlayerVal(col,row+1)==2){
            whoWon +=250;
        }
    }

    
    //Diagonal Two moves Player Two

    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 2 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 2 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    //switch slope
    
    for(int col = 0;col <7;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 2 && getPlayerVal(col-2,row+2) == 2 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1)== 0 && getPlayerVal(col-2,row+2) == 2 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 2 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 2 &&getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 250;
            }
        }
    }
    
    //end
    
    //Horizontal Three Moves Player One
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3,row) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 1 && getPlayerVal(col+3,row) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row) == 1 && getPlayerVal(col+2,row)== 0 && getPlayerVal(col+3,row) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    //end
    
    //Vertical Three Moves Player One
    
    for(int col=0;col<7;col++){
        int row = getHeightOfSlot(col);
        if(getPlayerVal(col,row)==1 && getPlayerVal(col,row+1)==1 && getPlayerVal(col,row+2)==1){
            whoWon -=1000;
        }
    }
    //end

    //Diagonal Three Moves Player One
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row)== 1 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 1 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col+1,row+1) == 1 && getPlayerVal(col+2,row+2)== 0 && getPlayerVal(col+3,row+3) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    //switch slope
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col-2,row+2) == 1 && getPlayerVal(col-3,row+3) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 1 && getPlayerVal(col-1,row+1) == 1 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 1) {
                whoWon = whoWon - 1000;
            }
        }
    }
    //end
    
    //Horizontal Three Moves Player Two
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row) == 2 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row) == 0) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row)== 2 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row) == 0 && getPlayerVal(col+2,row) == 2 && getPlayerVal(col+3,row) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row) == 2 && getPlayerVal(col+2,row) == 0 && getPlayerVal(col+3,row) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    //end
    
    //Vertical Three Moves Player Two
    for(int col=0;col<7;col++){
        int row = getHeightOfSlot(col);
        if(getPlayerVal(col,row)==2 && getPlayerVal(col,row+1)==2 && getPlayerVal(col,row+2)==2){
            whoWon +=1000;
        }
    }
    //end

    //Diagonal Three Moves Player Two
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row)== 2 && getPlayerVal(col+1,row+1) == 2 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 0) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col+1,row+1) == 2 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row+1) == 0 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col+1,row+1) == 2 && getPlayerVal(col+2,row+2) == 0 && getPlayerVal(col+3,row+3) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    //switch slope
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col-1,row+1) == 2 && getPlayerVal(col-2,row+2) == 2 && getPlayerVal(col-3,row+3) == 0) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 0 && getPlayerVal(col-1,row+1) == 2 && getPlayerVal(col-2,row+2) == 2 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col <4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col-1,row+1) == 0 && getPlayerVal(col+2,row+2) == 2 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    
    for(int col = 0;col < 4;col++) {
        for(int row = 0;row < 6;row++) {
            if(getPlayerVal(col,row) == 2 && getPlayerVal(col-1,row+1) == 2 && getPlayerVal(col-2,row+2) == 0 && getPlayerVal(col-3,row+3) == 2) {
                whoWon = whoWon + 1000;
            }
        }
    }
    //end
    return whoWon;
}
