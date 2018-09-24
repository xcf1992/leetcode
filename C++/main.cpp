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
    int getDestination(int pos, vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        int row = m - 1 - (pos - 1) / n;
        int col = (pos - 1) % n;
        if ((m - 1 - row) % 2 != 0) {
            col = n - 1 - col;
        }
        
        if (board[row][col] == -1) {
            return pos;
        }
        return board[row][col];
    }
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int end = board.size() * board[0].size();
        vector<bool> visited(end + 1, false);
        queue<int> bfs;
        bfs.push(1);
        visited[1] = true;
        int step = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int pos = bfs.front();
                bfs.pop();
                
                if (pos == end) {
                    return step;
                }
                
                for (int move = 1; move <= 6; move++) {
                    if (pos + move > end) {
                        break;
                    }
                    int next = getDestination(pos + move, board);
                    if (!visited[next]) {
                        bfs.push(next);
                        visited[next] = true;
                    }
                }
            }
            step += 1;
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,35,-1,-1,13,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,15,-1,-1,-1,-1}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.snakesAndLadders(matrix1);
    return 0;
}
