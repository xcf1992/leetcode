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
    bool isValid(vector<vector<int>> board, int N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[0][0] ^ board[0][j] ^ board[i][0] ^ board[i][j] == 1) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    int movesToChessboard(vector<vector<int>> board) {
        int N = board.size();
        if (!isValid(board, N)) {
            return -1;
        }
        
        
        return 0;
    }
};

int main() {
    Solution s;
    auto comp = [](int a, int b) {
        return a > b;
    };
    priority_queue<int, vector<int>, decltype(comp)> minHeap(comp);
    for (int i = 0; i < 10; i++) {
        minHeap.push(i);
    }
    while (!minHeap.empty()) {
        cout << minHeap.top() << endl;;
        minHeap.pop();
    }
    return 0;
}
