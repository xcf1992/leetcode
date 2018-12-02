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
    bool valid(string A) {
        if (A[0] > '2') {
            return false;
        }
        
        if (A[0] == '2') {
            if (A[1] > '3') {
                return false;
            }
        }
        
        if (A[2] > '5') {
            return false;
        }
        return true;
    }
    
    bool firstValid(vector<int>& A, vector<bool>& used, string& result) {
        if (result.size() == 4) {
            return valid(result);
        }
        
        for (int i = 0; i < 4; i++) {
            if (!used[i]) {
                result += ('0' + A[i]);
                used[i] = true;
                if (firstValid(A, used, result)) {
                    return true;
                }
                result.pop_back();
                used[i] = false;
            }
        }
        return false;
    }
public:
    string largestTimeFromDigits(vector<int> A) {
        sort(A.rbegin(), A.rend());
        vector<bool> used(4, false);
        string result = "";
        if (!firstValid(A, used, result)) {
            return "";
        }
        result.insert(2, ":");
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
    s.largestTimeFromDigits({1,2,3,4});
    return 0;
}
