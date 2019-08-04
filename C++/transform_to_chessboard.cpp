/*
 782. Transform to Chessboard
 An N x N board contains only 0s and 1s.
 In each move, you can swap any 2 rows with each other, or any 2 columns with each other.

 What is the minimum number of moves to transform the board into a "chessboard" -
 a board where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.

 Examples:
 Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
 Output: 2
 Explanation:
 One potential sequence of moves is shown below, from left to right:

 0110     1010     1010
 0110 --> 1010 --> 0101
 1001     0101     1010
 1001     0101     0101

 The first move swaps the first and second column.
 The second move swaps the second and third row.


 Input: board = [[0, 1], [1, 0]]
 Output: 0
 Explanation:
 Also note that the board with 0 in the top left corner,
 01
 10

 is also a valid chessboard.

 Input: board = [[1, 0], [1, 0]]
 Output: -1
 Explanation:
 No matter what sequence of moves you make, you cannot end with a valid chessboard.
 Note:

 board will have the same number of rows and columns, a number in the range [2, 30].
 board[i][j] will be only 0s or 1s.
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;
/*
 Property:
 1. To tranform columns, you must exchange rows and vice versa

 2. The valid beginning board contains only two different kinds of rows(columns), and the two kinds are 0/1 reversed
 This is correct because after a swap of rows,
 columns that are the same remains the same,
 different remains the different and final board has only two kinds of rows(columns),
 so the beginning must be the same as well

 As for why they are 0/1 reversed, prove by contradiction.
 If there are two different rows like these: [0, ....., 1] and [0, ....., 0]
 Then no matter how you swap rows and columns,
 there must be a rectangular whose four corners are 0,1,0,1,
 it cannot be a chessboard!!!

 3.A row swap followed by a column swap is the same as the opposite.
 So we can swap rows first, then columns
 If the minimum swaps consists of a sequence like RCCR....(R for row swap, C for column swap)

 4. If this chessboard can be tranformed (We can check that first),
 then if the first row and column is legal, the whole will also be legal.
 To check, verify the property 2.
 If we first perform row swaps and make the first column legal,
 then according to 2(two different columns remain 0/1 reversed after row swaps),
 every column is equal to the first or 0/1 reversal, then all columns are legal,
 then we can perform column swaps and make the first row legal.

 So we can write code like this:
 1) verify property 2
 2) swap columns and swap rows
 count the number num of displaced 0/1, the number of swap is num/2
 3) add column swaps and row swaps
 ================================== - ===============================
 Two conditions to help solve this problem:

 In a valid chess board, there are 2 and only 2 kinds of rows and one is inverse to the other.
 For example if there is a row 01010011 in the board, any other row must be either 01010011 or 10101100.
 The same for columns
 A corollary is that,
 any rectangle inside the board with corners top left, top right, bottom left, bottom right
 must be 4 ones or 2 ones 2 zeros or 4 zeros.

 Another important property is that every row and column has half ones. Assume the board is N * N:
 If N = 2*K, every row and every column has K ones and K zeros.
 If N = 2*K + 1, every row and every column has K ones and K + 1 zeros or K + 1 ones and K zeros.

 Since the swap process does not break this property, for a given board to be valid, this property must hold.
 These two conditions are necessary and sufficient condition for a valid chessboard.

 Once we know it is a valid cheese board, we start to count swaps.
 Basic on the property above, when we arange the first row, we are actually moving all columns.

 I try to arrange one row into 01010 and 10101 and I count the number of swaps.
 In case of N even, I take the minimum swaps, because both are possible.
 In case of N odd, I take the even swaps.
 Because when we make a swap, we move 2 columns or 2 rows at the same time.
 So col swaps and row swaps should be same here.
 */
class Solution {
private:
    int N = 0;
    bool isValid(vector<vector<int>>& board) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) if (board[0][0] ^ board[0][j] ^ board[i][0] ^ board[i][j] == 1) {
                return false;
            }
        }
        return true;
    }
public:
    int movesToChessboard(vector<vector<int>>& board) {
        N = board.size();
        if (!isValid(board)) {
            return -1;
        }

        int rowSum = 0;
        int rowSwap = 0; // the numebr of swaps needed to make row become 1010101... or 01010101....
        int colSum = 0;
        int colSwap = 0;
        for (int i = 0; i < N; i++) { // Check the first row and first col, how many matches 01010101...
            rowSum += board[0][i];
            rowSwap += board[i][0] == i % 2;
            colSum += board[i][0];
            colSwap += board[0][i] == i % 2;
        }

        if (N / 2 > rowSum or rowSum > (N + 1) / 2 or N / 2 > colSum or colSum > (N + 1) / 2) {
            return -1;
        }

        if (N % 2 == 1) {
            if (colSwap % 2 == 1) {
                colSwap = N - colSwap;
            }
            if (rowSwap % 2 == 1) {
                rowSwap = N - rowSwap;
            }
        }
        else {
            rowSwap = min(rowSwap, N - rowSwap);
            colSwap = min(colSwap, N - colSwap);
        }
        /*
        * One swap can change 2 numbers.
        * For example, you want to swap [000111] into [010101].
        * It only takes 1 swap to fix 2 misplaced numbers.
        *
        * row + col are the number we need to change.
        * By every swap, we can change 2 cols or 2 rows.
        * Does it make more sense?
        */
        return (rowSwap + colSwap) / 2;
    }
};
