/*
 A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 Example:

 Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
 Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

 0 0 0
 0 0 0
 0 0 0
 Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

 1 0 0
 0 0 0   Number of islands = 1
 0 0 0
 Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

 1 1 0
 0 0 0   Number of islands = 1
 0 0 0
 Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

 1 1 0
 0 0 1   Number of islands = 2
 0 0 0
 Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

 1 1 0
 0 0 1   Number of islands = 3
 0 1 0
 We return the result as an array: [1, 1, 2, 3]

 Challenge:

 Can you do it in time complexity O(k log mn), where k is the length of the positions?
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
#include <set>
using namespace std;

class Solution {
private:
    vector<int> root;

    int findRoot(int island) {
        while (island != root[island]) {
            island = root[island];
        }
        return island;
    }

    void check(int x, int y, int m, int n, int island, int &count) {
        if (x < 0 || y < 0 || x >= m || y >= n) {
            return;
        }

        int newIsland = x * n + y;
        if (root[newIsland] != -1) {
            int newRoot = findRoot(newIsland);
            int curRoot = findRoot(island);
            if (curRoot != newRoot) {
                root[curRoot] = newRoot;
                count -= 1;
            }
        }
    }
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> result;
        root = vector<int>(m * n, -1);
        int count = 0;
        for (pair<int, int>& pos : positions) {
            int row = pos.first;
            int col = pos.second;
            int island = row * n + col;
            root[island] = island;
            count += 1;

            check(row - 1, col, m, n, island, count);
            check(row + 1, col, m, n, island, count);
            check(row, col - 1, m, n, island, count);
            check(row, col + 1, m, n, island, count);
            result.push_back(count);
        }
        return result;
    }
};
