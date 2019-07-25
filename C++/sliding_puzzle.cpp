/*
773. Sliding Puzzle

On a 2x3 board, there are 5 tiles represented by the integers 1 through 5,
and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1, 2, 3], [4, 5, 0]].

Given a puzzle board,
return the least number of moves required so that the state of the board is solved.
If it is impossible for the state of the board to be solved,
return -1.

Examples:

Input: board = [[1, 2, 3], [4, 0, 5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1, 2, 3], [5, 4, 0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4, 1, 2], [5, 0, 3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4, 1, 2], [5, 0, 3]]
After move 1: [[4, 1, 2], [0, 5, 3]]
After move 2: [[0, 1, 2], [4, 5, 3]]
After move 3: [[1, 0, 2], [4, 5, 3]]
After move 4: [[1, 2, 0], [4, 5, 3]]
After move 5: [[1, 2, 3], [4, 5, 0]]
Input: board = [[3, 2, 4], [1, 5, 0]]
Output: 14
Note:

board will be a 2 x 3 array as described above.
board[i][j] will be a permutation of [0,  1,  2,  3,  4,  5].
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

class Solution { // 93.57%
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_map<int, vector<int>> moves{{0, {1, 3}}, {1, {0, 2, 4}}, {2, {1, 5}}, {3, {0, 4}}, {4, {3, 5, 1}}, {5, {4, 2}}};
        string puzzle = "";
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                puzzle.push_back(board[i][j] + '0');
            }
        }
        string target = "123450";

        unordered_set<string> visited;
        queue<pair<string, int>> bfs;
        bfs.push({puzzle, puzzle.find('0')});
        int step = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                puzzle = bfs.front().first;
                int pos = bfs.front().second;
                bfs.pop();

                if (puzzle == target) {
                    return step;
                }

                for (int next : moves[pos]) {
                    string nextPuzzle = puzzle;
                    swap(nextPuzzle[pos], nextPuzzle[next]);
                    if (visited.find(nextPuzzle) == visited.end()) {
                        visited.insert(nextPuzzle);
                        bfs.push({nextPuzzle, next});
                    }
                }
            }
            step += 1;
        }
        return -1;
    }
};

class Solution1 { // 5.12% too slow
private:
    unordered_map<int, vector<int>> moves{{0, {1, 3}}, {1, {0, 2, 4}}, {2, {1, 5}}, {3, {0, 4}}, {4, {3, 5, 1}}, {5, {4, 2}}};

    void dfs(string puzzle, unordered_map<string, int>& transform, int curZero, int swapZero, int curMove, int& minMoves) {
        swap(puzzle[curZero], puzzle[swapZero]);

        if (puzzle == "123450") {
            minMoves = min(minMoves, curMove);
            return;
        }

        if (curMove >= minMoves) {
            return;
        }

        if (transform.find(puzzle) == transform.end() or transform[puzzle] > curMove) {
            transform[puzzle] = curMove;
            for (int newZero : moves[swapZero]) {
                dfs(puzzle,  transform,  swapZero,  newZero,  curMove + 1,  minMoves);
            }
        }
    }
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string puzzle = "";
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                puzzle.push_back(board[i][j] + '0');
            }
        }

        int minMoves = INT_MAX;
        unordered_map<string,  int> transform;
        dfs(puzzle, transform, puzzle.find('0'), puzzle.find('0'), 0, minMoves);
        return minMoves == INT_MAX ? -1 : minMoves;
    }
};
