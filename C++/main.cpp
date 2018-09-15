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
    void collapse(string& board) {
        bool removed = true;
        while (removed) {
            removed = false;
            int pos = 0;
            while (pos < board.size()) {
                if (pos + 2 < board.size() && board[pos] == board[pos + 1] && board[pos] == board[pos + 2]) {
                    removed = true;
                    board.erase(pos, 3);
                    break;
                }
                pos += 1;
            }
        }
        return;
    }
    
public:
    int findMinStep(string board, string hand) {
        unordered_map<char, int> c2i({
            {'R', 0}, {'Y', 1}, {'B', 2}, {'G', 3}, {'W', 4}
        });
        vector<int> inHand(5, 0);
        for (char c : hand) {
            inHand[c2i[c]] += 1;
        }
        
        queue<pair<string, vector<int>>> bfs;
        int used = 0;
        bfs.push({board, inHand});
        while (!bfs.empty() && used < hand.size()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                string curBoard = bfs.front().first;
                vector<int> ballLeft = bfs.front().second;
                bfs.pop();
                
                for (int pos = 0; pos < curBoard.size() - 1; pos++) {
                    if (curBoard[pos] == curBoard[pos + 1] || ballLeft[c2i[curBoard[pos]]] == 0) {
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

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,0,2,0,1}, {0,0,0,0,0}, {0,0,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.findMinStep("GG", "G");
    return 0;
}
