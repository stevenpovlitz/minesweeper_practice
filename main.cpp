//
//  main.cpp
//  Minesweeper
//
//  Created by Steven Povlitz on 11/1/16.
//  Copyright © 2016 Steven Povlitz. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class MineSweeper {
private:
    vector<vector<int>> board; // main board of game. -1 is bomb, -2 is nothing, 0 thru 8 are reveal options
    int numUnrevealedSpaces; // when this is 0, the game is over
    
public:
    MineSweeper(int sizex, int sizey) {
        // randomly generate a board of size x, y
        
        board.resize(sizey);
        
        numUnrevealedSpaces = 0;
        
        srand (time(NULL));
        
        for (int i = 0; i < sizey; i++) {
            for (int j = 0; j < sizex; j++){
                int seed = int(rand()%4-4);
                
                if (seed == -1) {
                    board[i].push_back(seed);
                    numUnrevealedSpaces--;
                }
                else {
                    board[i].push_back(-2);
                }
            }
            
        }
        numUnrevealedSpaces += int(board.size() * board[0].size());
    }
    void drawBoard(bool showAll = false){
        cout << endl << "Board: " << endl;
        cout << "  ";
        for (int i = 0; i < board[0].size(); i++){
            cout << i%10 << " ";
        }
        cout << endl;
        
        for (int i = 0; i < board.size(); i++) {
            cout << i%10 << " ";
            for (int j = 0; j < board[i].size(); j++){
                
                if (board[i][j] == -1) {
                    if (showAll)
                        cout << "b" << " ";
                    else
                        cout << "-" << " ";
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
    
    bool checkCoords(int x, int y) {
        return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
    }
    
    int adjacentBombs(int x, int y){
        int sumAdjacent = 0;
        
        // top row
        if (checkCoords(x-1, y-1)) sumAdjacent += board[x-1][y-1] == -1;
        if (checkCoords(x-1, y)) sumAdjacent += board[x-1][y] == -1;
        if (checkCoords(x-1, y+1)) sumAdjacent += board[x-1][y+1] == -1;
        
        // middle row
        if (checkCoords(x, y-1)) sumAdjacent += board[x][y-1] == -1;
        if (checkCoords(x, y+1)) sumAdjacent += board[x][y+1] == -1;
        
        // top row
        if (checkCoords(x+1, y-1)) sumAdjacent += board[x+1][y-1] == -1;
        if (checkCoords(x+1, y)) sumAdjacent += board[x+1][y] == -1;
        if (checkCoords(x+1, y+1)) sumAdjacent += board[x+1][y+1] == -1;
        
        return sumAdjacent;
    }
    
    void exitGame(){
        cout << "Space Selected is a BOMB!" << endl;
        drawBoard(true);
        exit(1);
    }
    
    int calculateSpace(int guessx, int guessy){
        // cout << "* ";
        if (!checkCoords(guessx, guessy) || board[guessx][guessy] == 0)
            return 0;
        
        if (board[guessx][guessy] == -1)
            exitGame();
        
        if (adjacentBombs(guessx, guessy) > 0)
            board[guessx][guessy] = adjacentBombs(guessx, guessy);
        else if (adjacentBombs(guessx, guessy) == 0) {
            board[guessx][guessy] = 0;
            
            // recursively call this fun on all adjacent and diagonal that aren't value zero and are real coords
            
            // top row
            if (checkCoords(guessx-1, guessy-1) && board[guessx-1][guessy-1]!=0) calculateSpace(guessx-1, guessy-1);
            if (checkCoords(guessx-1, guessy) && board[guessx-1][guessy]!=0) calculateSpace(guessx-1, guessy);
            if (checkCoords(guessx-1, guessy+1) && board[guessx-1][guessy+1]!=0) calculateSpace(guessx-1, guessy+1);
            
            // middle row
            if (checkCoords(guessx, guessy-1) && board[guessx][guessy-1]!=0) calculateSpace(guessx, guessy-1);
            if (checkCoords(guessx, guessy+1) && board[guessx][guessy+1]!=0) calculateSpace(guessx, guessy+1);
            
            // top row
            if (checkCoords(guessx+1, guessy-1) && board[guessx+1][guessy-1]!=0) calculateSpace(guessx+1, guessy-1);
            if (checkCoords(guessx+1, guessy) && board[guessx+1][guessy]!=0) calculateSpace(guessx+1, guessy);
            if (checkCoords(guessx+1, guessy+1) && board[guessx+1][guessy+1]!=0) calculateSpace(guessx+1, guessy+1);
        }
        numUnrevealedSpaces--;
        return 0;
    }
    
    void getInput() {
        if (numUnrevealedSpaces < 0){
            cout << "WINNER" << endl;
            drawBoard(true);
            // cout << numUnrevealedSpaces << endl; // debugging
            exit(3);
        }
        cout << "enter a move in x, y format" << endl;
        int x, y;
        cin >> y >> x;
        calculateSpace(x, y);
    }
    
};

int main(int argc, const char * argv[]) {
    
    MineSweeper boardOne(3, 3);
    boardOne.drawBoard(true);
    
    while (true) {
        boardOne.getInput();
        boardOne.drawBoard();
        
    }
    return 0;
}
