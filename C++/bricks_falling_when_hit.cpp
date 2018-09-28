/*
 We have a grid of 1s and 0s; the 1s in a cell represent bricks.  A brick will not drop if and only if it is directly connected to the top of the grid, or at least one of its (4-way) adjacent bricks will not drop.
 
 We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j), the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.
 
 Return an array representing the number of bricks that will drop after each erasure in sequence.
 
 Example 1:
 Input:
 grid = [[1,0,0,0],[1,1,1,0]]
 hits = [[1,0]]
 Output: [2]
 Explanation:
 If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.
 Example 2:
 Input:
 grid = [[1,0,0,0],[1,1,0,0]]
 hits = [[1,1],[1,0]]
 Output: [0,0]
 Explanation:
 When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.  Note that the erased brick (1, 0) will not be counted as a dropped brick.
 
 
 Note:
 
 The number of rows and columns in the grid will be in the range [1, 200].
 The number of erasures will not exceed the area of the grid.
 It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
 An erasure may refer to a location with no brick - if it does, no bricks drop.
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
public:
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, 1, 0, -1};
    int vst[201][201], id;
    int n, m;
    
    vector<int> hitBricks(vector<vector<int>>& g, vector<vector<int>>& hits) {
        n = g.size();
        m = g[0].size();
        vector<int> result;
        for (auto hit : hits){
            if (g[hit[0]][hit[1]] == 0) {
                result.push_back(0);
                continue;
            }
            
            g[hit[0]][hit[1]] = 0;
            int drop = 0;
            for (int d = 0; d < 4;d++){
                int x = hit[0] + dr[d];
                int y = hit[1] + dc[d];
                ++id; //mark each connecting parts with a unique id in this run
                unordered_set<int> connected;
                if (falling(x, y, g, connected)) {
                    // if we find one brick will drop, then it mean all bricks connected to this brick will drop
                    // otherwise this brick will not drop itself.
                    drop += connected.size();
                    for (auto& pos : connected) {
                        g[pos / m][pos % m] = 0;
                    }
                }
            }
            result.push_back(drop);
        }
        return result;
    }
    
    bool falling(int r, int c, vector<vector<int>>& g, unordered_set<int>& connected){
        if (!valid(r,c) || !g[r][c] || vst[r][c] == id) {
            return true;
        }
        
        if (r == 0) {
            return false;
        }
        
        vst[r][c] = id;
        connected.insert(r * m + c);
        for (int d = 0; d < 4; ++d){
            if (!falling(r + dr[d], c + dc[d], g, connected)) {
                return false;
            }
        }
        return true;
    }
    
    bool valid(int r, int c){
        return 0 <= r && r < n && 0 <= c && c < m;
    }
};
