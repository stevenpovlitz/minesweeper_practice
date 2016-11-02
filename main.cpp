//
//  main.cpp
//  Minesweeper
//
//  Created by Steven Povlitz on 11/1/16.
//  Copyright © 2016 Steven Povlitz. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class MineSweeper {
private:
    vector<vector<int>> board; // main board of game. -1 is bomb, -2 is nothing, 0 thru 8 are reveal options
    int numUnrevealedSpaces; // when this is 0, the game is over
    
public:
    MineSweeper(int sizex, int sizey) {
        // randomly generate a board of size x, y
        
        board.resize(sizey);
        
        for (int i = 0; i < sizey; i++) {
            for (int j = 0; j < sizex; j++){
                int seed = int(rand()%4-4);
                
                if (seed == -1) {
                    board[i].push_back(seed);
                }
                else {
                    board[i].push_back(-2);
                }
            }
            
        }
        
        numUnrevealedSpaces = int(board.size());
    }
    
    void drawBoard(){
        cout << "Board: " << endl;
        cout << "  ";
        for (int i = 0; i < board[0].size(); i++){
            cout << i << " ";
        }
        cout << endl;
        
        for (int i = 0; i < board.size(); i++) {
            cout << i << " ";
            for (int j = 0; j < board[i].size(); j++){
                
                if (board[i][j] == -1) {
                    cout << "b" << " ";
                }
                else if (board[i][j] == -2) {
                    cout << "-" << " ";
                }
                else {
                    cout << board[i][j] << " ";
                }
                
            }
            cout << endl;
        }
    }
    
    int calculateSpace(int guessx, int guessy, bool ahead = true){
        // NOTE: NEED something to STOP this function from just solving entire board: check
        // adjacent vs recursive solve adjacent, based on if any neighbors have bombs
        
        if (!(guessx >= 0 && guessx < board[0].size() && guessy >= 0 && guessy < board.size())) {
            // invalid input
            return 0;
        }
        else {
            if (ahead) {
                return board[guessx][guessy] == -1;
            }
            
            if (board[guessx][guessy] == -1) {
                return 1; // this is a bomb;
            }
            
            board[guessx][guessy] = -5; // temp val
            
            int adjacentVals = calculateSpace(guessx-1, guessy-1) + calculateSpace(guessx, guessy-1) + calculateSpace(guessx+1, guessy-1) +
            calculateSpace(guessx-1, guessy) + calculateSpace(guessx+1, guessy) +
            calculateSpace(guessx-1, guessy+1) + calculateSpace(guessx, guessy+1) + calculateSpace(guessx+1, guessy+1);
            
            if (adjacentVals > 0) {
                
                board[guessx][guessy] = adjacentVals;
            }
            else {
                calculateSpace(guessx-1, guessy-1, false); calculateSpace(guessx, guessy-1, false); calculateSpace(guessx+1, guessy-1, false);
                calculateSpace(guessx-1, guessy, false); calculateSpace(guessx+1, guessy, false);
                calculateSpace(guessx-1, guessy+1, false); calculateSpace(guessx, guessy+1, false); calculateSpace(guessx+1, guessy+1, false);
                
            }
            
        }
        return 0;
        
    }
    
    void getInput() {
        cout << "enter a move in x, y format" << endl;
        int x, y;
        cin >> y >> x;
        
        if (board[x][y] == -1) {
            
            cout << "BOMB!" << endl;
            exit(1);
            
        }
        
        // have some event for clicking on a bomb
        
        calculateSpace(x, y);
    }
    
};

int main(int argc, const char * argv[]) {
    
    MineSweeper boardOne(6, 4);
    
    boardOne.drawBoard();
    boardOne.getInput();
    boardOne.drawBoard();
    
    return 0;
}


/*
 int toReturn = 0; // 0 is no spaces adjacent with bomb, 8 is all spaces near have bomb
 
 if (guessx >= 0 && guessx < board[0].size() && guessy >= 0 && guessy < board.size()) {
 if (board[guessy][guessy] == -1) {
 toReturn = -1;
 }
 else {
 toReturn += calculateSpace(guessx-1, guessy-1) + calculateSpace(guessx, guessy-1) + calculateSpace(guessx+1, guessy-1) +
 calculateSpace(guessx-1, guessy) + calculateSpace(guessx+1, guessy) +
 calculateSpace(guessx-1, guessy+1) + calculateSpace(guessx, guessy+1) + calculateSpace(guessx+1, guessy+1);
 }
 
 if (toReturn >= 0)
 board[guessx][guessy] = toReturn;
 }
 
 
 return toReturn;
*/
