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
        n = g.size(),
        m = g[0].size();
        vector<int> result;
        for (auto hit : hits){
            int r = hit[0];
            int c = hit[1];
            int removal = 0;
            if (g[r][c] == 1){
                g[r][c] = 0;
                for (int d = 0;d<4;d++){
                    int x = r + dr[d];
                    int y = c + dc[d];
                    ++id; //mark each connecting parts with a unique id in this run
                    if (falling(x, y, g)) {
                        removal += cnt(x, y, g);
                    }
                }
            }
            result.push_back(removal);
        }
        return result;
    }
    
    bool falling(int r, int c, vector<vector<int>>& g){
        if (!valid(r,c) || !g[r][c] || vst[r][c] == id) {
            return true;
        }
        
        if (r == 0) {
            return false;
        } //connecting 1st row
        
        vst[r][c] = id;
        for (int d = 0; d < 4; ++d){
            if (!falling(r + dr[d], c + dc[d], g)) {
                return false;
            }
        }
        return true;
    }
    
    int cnt(int r,int c, vector<vector<int>>& g){
        if (!valid(r,c)||!g[r][c]) {
            return 0;
        }
        
        int ret = 1;
        g[r][c] = 0;
        for(int d = 0; d < 4; ++d) {
            ret += cnt(r + dr[d], c + dc[d], g);
        }
        return ret;
    }
    
    bool valid(int r,int c){
        return 0 <= r && r < n && 0 <= c && c < m;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<vector<int>> vb({{3,0}});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.hitBricks(matrix1, vb);
    return 0;
}
