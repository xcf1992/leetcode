/*
794. Valid Tic-Tac-Toe State
A Tic-Tac-Toe board is given as a string array board.
Return True if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.

The board is a 3 x 3 array, and consists of characters " ", "X", and "O".
The " " character represents an empty square.

Here are the rules of Tic-Tac-Toe:

Players take turns placing characters into empty squares (" ").
The first player always places "X" characters, while the second player always places "O" characters.
"X" and "O" characters are always placed into empty squares, never filled ones.
The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
The game also ends if all squares are non-empty.
No more moves can be played if the game is over.
Example 1:
Input: board = ["O  ", "   ", "   "]
Output: false
Explanation: The first player always plays "X".

Example 2:
Input: board = ["XOX", " X ", "   "]
Output: false
Explanation: Players take turns making moves.

Example 3:
Input: board = ["XXX", "   ", "OOO"]
Output: false

Example 4:
Input: board = ["XOX", "O O", "XOX"]
Output: true
Note:

board is a length-3 array of strings, where each string board[i] has length 3.
Each board[i][j] is a character in the set {" ", "X", "O"}.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
private:
    bool windBy(char ch, vector<string>& board) {
        if (board[0][0] == ch and board[1][1] == ch and board[2][2] == ch) {
            return true;
        }
        if (board[0][2] == ch and board[1][1] == ch and board[2][0] == ch) {
            return true;
        }

        string temp = string(3, ch);
        for (string& row : board) {
            if (temp == row) {
                return true;
            }
        }

        for (int j = 0; j < 3; j++) if (board[0][j] == ch and board[1][j] == ch and board[2][j] == ch) {
            return true;
        }
        return false;
    }
public:
    bool validTicTacToe(vector<string>& board) {
        int xCount = 0;
        int oCount = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 'X') {
                    xCount += 1;
                }
                else if (board[i][j] == 'O') {
                    oCount += 1;
                }
            }
        }
        if (xCount - oCount > 1 or xCount < oCount) {
            return false;
        }

        bool xWin = windBy('X', board);
        bool oWin = windBy('O', board);
        if (xWin and oWin) {
            return false;
        }
        if (!xWin and !oWin) {
            return true;
        }
        if (xWin) {
            return xCount == oCount + 1;
        }
        return oCount == xCount;
    }
};
