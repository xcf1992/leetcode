/*
 675. Cut Off Trees for Golf Event

 You are asked to cut off trees in a forest for a golf event.
 The forest is represented as a non-negative 2D map, in this map:

 0 represents the obstacle can't be reached.
 1 represents the ground can be walked through.
 The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.

 You are asked to cut off all the trees in this forest in the order of tree's height,
 always cut off the tree with lowest height first.
 And after cutting, the original place has the tree will become a grass (value 1).

 You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees.
 If you can't cut off all the trees, output -1 in that situation.

 You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.

 Example 1:

 Input:
 [
 [1,2,3],
 [0,0,4],
 [7,6,5]
 ]
 Output: 6


 Example 2:

 Input:
 [
 [1,2,3],
 [0,0,0],
 [7,6,5]
 ]
 Output: -1


 Example 3:

 Input:
 [
 [2,3,4],
 [0,0,5],
 [8,7,6]
 ]
 Output: 6
 Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int M = 0;
    int N = 0;

    int count(vector<vector<int>>& forest, int curR, int curC, int desR, int desC) {
        queue<pair<int, int>> bfs;
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        bfs.push({curR, curC});
        visited[curR][curC] = true;

        int steps = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int row = bfs.front().first;
                int col = bfs.front().second;
                bfs.pop();

                if (row == desR and col == desC) {
                    return steps;
                }

                for (int k = 0; k < 4; k++) {
                    int nextR = row + dir[k][0];
                    int nextC = col + dir[k][1];
                    if (nextC >= 0 and nextR >= 0 and nextC < N and nextR < M and !visited[nextR][nextC] and forest[nextR][nextC] != 0) {
                        bfs.push({nextR, nextC});
                        visited[nextR][nextC] = true;
                    }
                }
            }
            steps += 1;
        }
        return -1;
    }
public:
    int cutOffTree(vector<vector<int>>& forest) {
        M = forest.size();
        if (M == 0) {
            return -1;
        }
        N = forest[0].size();

        vector<vector<int>> heights;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (forest[i][j] > 1) {
                    heights.push_back({forest[i][j], i, j});
                }
            }
        }
        sort(heights.begin(), heights.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });

        int result = 0;
        int row = 0;
        int col = 0;
        for (int i = 0; i < heights.size(); i++) {
            int steps = count(forest, row, col, heights[i][1], heights[i][2]);
            if (steps == -1) {
                return -1;
            }
            result += steps;
            row = heights[i][1];
            col = heights[i][2];
        }
        return result;
    }
};
