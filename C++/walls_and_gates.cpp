//
//  walls_and_gates.cpp
//  C++
//
//  Created by Chenfu Xie on 2/28/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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

/*
 You are given a m x n 2D grid initialized with these three possible values.
 
 -1 - A wall or an obstacle.
 0 - A gate.
 INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
 Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
 
 For example, given the 2D grid:
 
 INF  -1  0  INF
 INF INF INF  -1
 INF  -1 INF  -1
   0  -1 INF INF
 
 After running your function, the 2D grid should be:
 
 3  -1   0   1
 2   2   1  -1
 1  -1   2  -1
 0  -1   3   4
 
 */

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty()) {
            return;
        }
        queue<int> bfs;
        int m = rooms.size();
        int n = rooms[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    bfs.push(i * n + j);
                }
            }
        }
        
        vector<int> move({0, 1, 0, -1, 0});
        while (!bfs.empty()) {
            int pos = bfs.front();
            bfs.pop();
            int i = pos / n;
            int j = pos % n;
            for (int k = 0; k < 4; k++) {
                int p = i + move[k];
                int q = j + move[k + 1];
                if (p >= 0 && q >= 0 && p < m && q < n && rooms[p][q] > rooms[i][j] + 1) {
                    rooms[p][q] = rooms[i][j] + 1;
                    bfs.push(p * n + q);
                }
            }
        }
    }
};
