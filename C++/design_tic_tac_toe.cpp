//
//  design_tic_tac_toe.cpp
//  C++
//
//  Created by Chenfu Xie on 2/27/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
using namespace std;

/*
 Design a Tic-tac-toe game that is played between two players on a n x n grid.
 
 You may assume the following rules:
 
 A move is guaranteed to be valid and is placed on an empty block.
 Once a winning condition is reached, no more moves is allowed.
 A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
 Example:
 Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.
 
 TicTacToe toe = new TicTacToe(3);
 
 toe.move(0, 0, 1); -> Returns 0 (no one wins)
 |X| | |
 | | | |    // Player 1 makes a move at (0, 0).
 | | | |
 
 toe.move(0, 2, 2); -> Returns 0 (no one wins)
 |X| |O|
 | | | |    // Player 2 makes a move at (0, 2).
 | | | |
 
 toe.move(2, 2, 1); -> Returns 0 (no one wins)
 |X| |O|
 | | | |    // Player 1 makes a move at (2, 2).
 | | |X|
 
 toe.move(1, 1, 2); -> Returns 0 (no one wins)
 |X| |O|
 | |O| |    // Player 2 makes a move at (1, 1).
 | | |X|
 
 toe.move(2, 0, 1); -> Returns 0 (no one wins)
 |X| |O|
 | |O| |    // Player 1 makes a move at (2, 0).
 |X| |X|
 
 toe.move(1, 0, 2); -> Returns 0 (no one wins)
 |X| |O|
 |O|O| |    // Player 2 makes a move at (1, 0).
 |X| |X|
 
 toe.move(2, 1, 1); -> Returns 1 (player 1 wins)
 |X| |O|
 |O|O| |    // Player 1 makes a move at (2, 1).
 |X|X|X|
 Follow up:
 Could you do better than O(n^2) per move() operation?
 */

class TicTacToe {
private:
    vector<vector<int>> rowCount;
    vector<vector<int>> colCount;
    vector<int> diagnal;
    vector<int> antiDiagnal;
    int size;
public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        rowCount.resize(2, vector<int>(n, 0));
        colCount.resize(2, vector<int>(n, 0));
        diagnal.resize(2, 0);
        antiDiagnal.resize(2, 0);
        size = n;
    }
    
    /** Player {player} makes a move at ({row}, {col}).
     @param row The row of the board.
     @param col The column of the board.
     @param player The player, can be either 1 or 2.
     @return The current winning condition, can be either:
     0: No one wins.
     1: Player 1 wins.
     2: Player 2 wins. */
    int move(int row, int col, int player) {
        rowCount[player - 1][row] += 1;
        colCount[player - 1][col] += 1;
        if (row == col) {
            diagnal[player - 1] += 1;
        }
        if (row + col == size - 1) {
            antiDiagnal[player - 1] += 1;
        }
        
        if (rowCount[player - 1][row] == size ||
            colCount[player - 1][col] == size ||
            diagnal[player - 1] == size ||
            antiDiagnal[player - 1] == size) {
            return player;
        }
        return 0;
    }
};
/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */
