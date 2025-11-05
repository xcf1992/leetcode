/*
1301. Number of Paths with Max Score
https://leetcode.com/problems/number-of-paths-with-max-score/

You are given a square board of characters.
You can move on the board starting at the bottom right square marked with the character 'S'.

You need to reach the top left square marked with the character 'E'.
The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'.
In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers:
the first integer is the maximum sum of numeric characters you can collect,
and the second is the number of such paths that you can take to get that maximum sum,
taken modulo 10^9 + 7.
In case there is no path, return [0, 0].

Example 1:
Input: board = ["E23","2X2","12S"]
Output: [7,1]

Example 2:
Input: board = ["E12","1X1","21S"]
Output: [4,2]

Example 3:
Input: board = ["E11","XXX","11S"]
Output: [0,0]

Constraints:
2 <= board.length == board[i].length <= 100
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string> &board) {
        int mod = 1e9 + 7;
        int len = board.size();
        vector<vector<int> > score(len + 1, vector<int>(len + 1, 0));
        vector<vector<int> > paths(len + 1, vector<int>(len + 1, 0));
        board[0][0] = board[len - 1][len - 1] = '0';
        paths[0][0] = 1;

        vector<vector<int> > dirs{{1, 0}, {0, 1}, {1, 1}};
        for (int i = 1; i <= len; ++i) {
            for (int j = 1; j <= len; ++j) {
                if (board[i - 1][j - 1] == 'X') {
                    continue;
                }

                for (vector<int> &dir: dirs) {
                    int ni = i - dir[0];
                    int nj = j - dir[1];
                    if (paths[ni][nj] > 0) {
                        int sum = score[ni][nj] + (board[i - 1][j - 1] - '0');
                        if (score[i][j] <= sum) {
                            paths[i][j] = ((score[i][j] == sum ? paths[i][j] : 0) + paths[ni][nj]) % mod;
                            score[i][j] = sum;
                        }
                    }
                }
            }
        }
        return {score[len][len], paths[len][len]};
    }
};