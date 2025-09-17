/*
723. Candy Crush
https://leetcode.com/problems/candy-crush/

This question is about implementing a basic elimination algorithm for Candy Crush.

Given a 2D integer array board representing the grid of candy,
different positive integers board[i][j] represent different types of candies.
A value of board[i][j] = 0 represents that the cell at position (i, j) is empty.
The given board represents the state of the game following the player's move.
Now, you need to restore the board to a stable state by crushing candies according to the following rules:

If three or more candies of the same type are adjacent vertically or horizontally,
"crush" them all at the same time - these positions become empty.
After crushing all candies simultaneously,
if an empty space on the board has candies on top of itself,
then these candies will drop until they hit a candy or bottom at the same time.
(No new candies will drop outside the top boundary.)
After the above steps, there may exist more candies that can be crushed.
If so, you need to repeat the above steps.
If there does not exist more candies that can be crushed (ie. the board is stable),
then return the current board.
You need to perform the above rules until the board becomes stable,
then return the current board.

Example:
Input:
board =
[[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]
Output:
[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[110,0,0,0,114],[210,0,0,0,214],[310,0,0,113,314],[410,0,0,213,414],[610,211,112,313,614],[710,311,412,613,714],[810,411,512,713,1014]]
Explanation:

Note:
The length of board will be in the range [3, 50].
The length of board[i] will be in the range [3, 50].
Each board[i][j] will initially start as an integer in the range [1, 2000].
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
using namespace std;

class Solution {
private:
    bool crush(vector<vector<int>>& board, int n, int m) {
        vector<pair<int,int>> candy;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j]) {
                    int i0 = i, i1 = i, j0 = j, j1 = j;
                    while (i1 < n and i1 < i + 3 and board[i1][j] == board[i][j]) {
                        i1++;
                    }
                    while (i0 >= 0 and i0 > i - 3 and board[i0][j] == board[i][j]) {
                        i0--;
                    }
                    while (j1 < m and j1 < j + 3 and board[i][j1] == board[i][j]) {
                        j1++;
                    }
                    while (j0 >= 0 and j0 > j - 3 and board[i][j0] == board[i][j]){
                        j0--;
                    }
                    if (i1 - i0 > 3 or j1 - j0 > 3) {
                        candy.push_back({i,j});
                    }
                }
            }
        }
        if (candy.empty()) {
            return false;
        }
        for (auto p : candy) {
            board[p.first][p.second] = 0;
        }
        return true;
    }

    void drop(vector<vector<int>>& board, int n, int m) {
        for (int j = 0; j < m; ++j) {
            int t = n - 1;
            for (int i = n - 1; i >= 0; i--) {
                if (board[i][j]) {
                    swap(board[i][j], board[t][j]);
                    t--;
                }
            }
            for (int i = t; i >= 0; i--) {
                board[i][j] = 0;
            }
        }
    }
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int n = board.size();
        int m = board[0].size();
        while (crush(board, n, m)) {
            drop(board, n, m);
        }
        return board;
    }
};
