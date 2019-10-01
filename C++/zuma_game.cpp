/*
488. Zuma Game

Think about Zuma Game.
You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W).
You also have several balls in your hand.

Each time, you may choose a ball in your hand,
and insert it into the row (including the leftmost place and rightmost place).
Then, if there is a group of 3 or more balls in the same color touching,
remove these balls. Keep doing this until no more balls can be removed.

Find the minimal balls you have to insert to remove all the balls on the table.
If you cannot remove all the balls, output -1.

Examples:
Input: "WRRBBW", "RB"
Output: -1
Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW

Input: "WWRRBBWW", "WRBRW"
Output: 2
Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

Input:"G", "GGGGG"
Output: 2
Explanation: G -> G[G] -> GG[G] -> empty

Input: "RBYYBBRRB", "YRBGB"
Output: 3
Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty

Note:
You may assume that the initial row of balls on the table won’t have any 3 or more consecutive balls with the same color.
The number of balls on the table won't exceed 20, and the string represents these balls is called "board" in the input.
The number of balls in your hand won't exceed 5, and the string represents these balls is called "hand" in the input.
Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.
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

class Solution {
private:
    unordered_map<char, int> c2i = {{'R', 0}, {'Y', 1}, {'B', 2}, {'G', 3}, {'W', 4}};

    void collapse(string& board) {
        if (board.empty()) {
            return;
        }

        bool removed = true;
        while (removed) {
            removed = false;
            for (int pos = 0; pos < board.size(); ++pos) {
                int end = pos;
                while (end < board.size() and board[end] == board[pos]) {
                    end += 1;
                }
                if (end - pos >= 3) {
                    board.erase(pos, end - pos);
                    removed = true;
                    break;
                }
            }
        }
    }
public:
    int findMinStep(string board, string hand) {
        collapse(board);
        if (board.empty()) {
            return 0;
        }

        vector<int> inHand(5, 0);
        for (char c : hand) {
            inHand[c2i[c]] += 1;
        }

        queue<pair<string, vector<int>>> bfs;
        int used = 0;
        bfs.push({board, inHand});
        while (!bfs.empty() and used < hand.size()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                string curBoard = bfs.front().first;
                vector<int> ballLeft = bfs.front().second;
                bfs.pop();

                for (int pos = 0; pos < curBoard.size(); pos++) {
                    if (curBoard[pos] == curBoard[pos + 1] or ballLeft[c2i[curBoard[pos]]] == 0) {
                        continue;
                    }
                    string newBoard = curBoard;
                    vector<int> newHand = ballLeft;
                    newBoard.insert(pos, 1, curBoard[pos]);
                    collapse(newBoard);
                    if (newBoard.empty()) {
                        return used + 1;
                    }
                    newHand[c2i[curBoard[pos]]] -= 1;
                    bfs.push({newBoard, newHand});
                }
            }
            used += 1;
        }
        return -1;
    }
};
