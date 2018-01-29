//
//  sliding_puzzle.cpp
//  C++
//
//  Created by Chenfu Xie on 1/29/18.
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

class Solution {
private:
    unordered_map<int, vector<int>> moves{{0,{1,3}},{1,{0,2,4}},{2,{1,5}},{3,{0,4}},{4,{3,5,1}},{5,{4,2}}};
    
    void dfs(string puzzle, unordered_map<string, int>& transform, int curZero, int swapZero, int curMove, int& minMoves) {
        swap(puzzle[curZero], puzzle[swapZero]);
        
        if (puzzle == "123450") {
            minMoves = min(minMoves, curMove);
        }
        
        if (curMove < minMoves && (transform[puzzle] == 0 || transform[puzzle] > curMove)) {
            transform[puzzle] = curMove;
            for (int newZero : moves[swapZero]) {
                dfs(puzzle, transform, swapZero, newZero, curMove + 1, minMoves);
            }
        }
    }
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string puzzle = "";
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                puzzle += to_string(board[i][j]);
            }
        }
        
        int minMoves = INT_MAX;
        unordered_map<string, int> transform;
        dfs(puzzle, transform, puzzle.find('0'), puzzle.find('0'), 0, minMoves);
        return minMoves == INT_MAX ? -1 : minMoves;
    }
};
