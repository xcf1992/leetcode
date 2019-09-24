/*
934. Shortest Bridge
https://leetcode.com/problems/shortest-bridge/

In a given 2D binary array A, there are two islands.
(An island is a 4-directionally connected group of 1s not connected to any other 1s.)

Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.
Return the smallest number of 0s that must be flipped.
(It is guaranteed that the answer is at least 1.)

Example 1:
Input: [[0,1],[1,0]]
Output: 1

Example 2:
Input: [[0,1,0],[0,0,0],[0,0,1]]
Output: 2

Example 3:
Input: [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1

Note:
1 <= A.length = A[0].length <= 100
A[i][j] == 0 or A[i][j] == 1
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
    int M = 0;
    int N = 0;
    vector<int> rmoves = vector<int>({1, -1, 0, 0});
    vector<int> cmoves = vector<int>({0, 0, 1, -1});

    bool isValid(int row, int col) {
        return row >= 0 and row < M and col >= 0 and col < N;
    }

    void paint(int row, int col, int color, vector<vector<int>>& A, queue<pair<int, int>>& bfs) {
        if (isValid(row, col) and A[row][col] == 1) {
            A[row][col] = color;
            if (color == 2) {
                bfs.push({row, col});
            }

            for (int i = 0; i < 4; i++) {
                paint(row + rmoves[i], col + cmoves[i], color, A, bfs);
            }
        }
    }
public:
    int shortestBridge(vector<vector<int>>& A) {
        M = A.size();
        N = A[0].size();

        int color = 2;
        queue<pair<int, int>> bfs;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (A[i][j] == 1) {
                    paint(i, j, color, A, bfs);
                    color += 1;
                }
            }
        }

        int distance = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int x = 0; x < curSize; x++) {
                int row = bfs.front().first;
                int col = bfs.front().second;
                bfs.pop();

                for (int i = 0; i < 4; i++) {
                    int nextR = row + rmoves[i];
                    int nextC = col + cmoves[i];
                    if (isValid(nextR, nextC)) {
                        if (A[nextR][nextC] == 3) {
                            return distance;
                        }
                        else if (A[nextR][nextC] == 0) {
                            A[nextR][nextC] = 2;
                            bfs.push({nextR, nextC});
                        }
                    }
                }
            }
            distance += 1;
        }
        return distance;
    }
};
