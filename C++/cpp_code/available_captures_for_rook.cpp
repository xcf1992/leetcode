/*
 999. Available Captures for Rook
 DescriptionHintsSubmissionsDiscussSolution
 On an 8 x 8 chessboard, there is one white rook.  There also may be empty squares, white bishops, and black pawns.
 These are given as characters 'R', '.', 'B', and 'p' respectively. Uppercase characters represent white pieces, and
 lowercase characters represent black pieces.

 The rook moves as in the rules of Chess: it chooses one of four cardinal directions (north, east, west, and south),
 then moves in that direction until it chooses to stop, reaches the edge of the board, or captures an opposite colored
 pawn by moving to the same square it occupies.  Also, rooks cannot move into the same square as other friendly bishops.

 Return the number of pawns the rook can capture in one move.



 Example 1:



 Input:
 [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
 Output: 3
 Explanation:
 In this example the rook is able to capture all the pawns.
 Example 2:



 Input:
 [[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
 Output: 0
 Explanation:
 Bishops are blocking the rook to capture any pawn.
 Example 3:



 Input:
 [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]
 Output: 3
 Explanation:
 The rook can capture the pawns at positions b5, d6 and f5.


 Note:

 board.length == board[i].length == 8
 board[i][j] is either 'R', '.', 'B', or 'p'
 There is exactly one cell with board[i][j] == 'R'
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        int row = -1;
        int col = -1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'R') {
                    row = i;
                    col = j;
                    break;
                }
            }
            if (row != -1) {
                break;
            }
        }

        int result = 0;
        int i = row + 1;
        while (i < m) {
            if (board[i][col] == 'p') {
                result += 1;
                break;
            }
            if (board[i][col] == 'B') {
                break;
            }
            i += 1;
        }

        i = row - 1;
        while (i >= 0) {
            if (board[i][col] == 'p') {
                result += 1;
                break;
            }
            if (board[i][col] == 'B') {
                break;
            }
            i -= 1;
        }

        int j = col + 1;
        while (j < n) {
            if (board[row][j] == 'p') {
                result += 1;
                break;
            }
            if (board[row][j] == 'B') {
                break;
            }
            j += 1;
        }

        j = col - 1;
        while (j >= 0) {
            if (board[row][j] == 'p') {
                result += 1;
                break;
            }
            if (board[row][j] == 'B') {
                break;
            }
            j -= 1;
        }
        return result;
    }
};