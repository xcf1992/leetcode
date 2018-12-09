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
    int find(int n, int k, int number, int& rank) {
        if (rank == k) {
            return number;
        }
        
        for (int digit = 0; digit <= 9; digit++) {
            int temp = number * 10 + digit;
            if (temp > n) {
                break;
            }
            rank += 1;
            int result = find(n, k, temp, rank);
            if (result != -1) {
                return result;
            }
        }
        return -1;
    }
public:
    int findKthNumber(int n, int k) {
        int rank = 0;
        int result = -1;
        for (int i = 1; i <= 9; i++) {
            if (i > n) {
                break;
            }
            rank += 1;
            result = find(n, k, i, rank);
            if (result != -1) {
                break;
            }
        }
        return result;
    }
};

int main() {
    vector<bool> visited(10, false);
    visited[2] = true;
    visited[7] = true;
    visited[4] = true;
    visited.resize(10, false);
    visited.clear();
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
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    s.findKthNumber(13, 6);
    return 0;
}
