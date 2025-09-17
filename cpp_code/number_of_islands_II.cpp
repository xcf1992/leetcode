/*
305. Number of Islands II

A 2d grid map of m rows and n columns is initially filled with water.
We may perform an addLand operation which turns the water at position (row, col) into a land.
Given a list of positions to operate, count the number of islands after each addLand operation.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Erowample:
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
Can you do it in time complerowity O(k log mn), where k is the length of the positions?
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
/*
some thing to take in mind during the code
1. if the spot is already an island, continue without merge
2. find should return root[island] rather than island with path merge, otherwise we will always return the island itself as parent
*/
class Solution {
private:
    // DONT FORGET TO INITIALIZE m AND n
    int m = 0;
    int n = 0;
    vector<int> root;
    vector<int> diff = {0, 1, 0, -1, 0};

    int find(int island) {
        if (island != root[island]) {
            root[island] = find(root[island]);
        }
        return root[island];
    }

    void check(int row, int col, int newIsland, int &count) {
        int island = row * n + col;
        if (row < 0 or col < 0 or row >= m or col >= n or root[island] == -1) {
            return;
        }

        int newRoot = find(newIsland);
        int curRoot = find(island);
        if (curRoot != newRoot) {
            root[curRoot] = newRoot;
            count -= 1;
        }
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        this -> m = m;
        this -> n = n;
        root = vector<int>(m * n, -1);

        int count = 0;
        vector<int> result;
        for (vector<int>& pos : positions) {
            int row = pos[0];
            int col = pos[1];
            int island = row * n + col;
            if (root[island] != -1) {
                result.push_back(count);
                continue; // this one has become island before already
            }

            count += 1;
            root[island] = island;
            for (int i = 1; i < diff.size(); ++i) {
                check(row + diff[i], col + diff[i - 1], island, count);
            }
            result.push_back(count);
        }
        return result;
    }
};
