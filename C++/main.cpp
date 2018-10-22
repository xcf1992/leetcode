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
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        if (n == 0) {
            return 0;
        }
        vector<int> leftOne(n + 2, 0);
        vector<int> rightZero(n + 2, 0);
        for (int i = 1; i < n + 1; i++) {
            leftOne[i] = leftOne[i - 1] + (S[i] - '0');
            
            int j = n + 1 - i;
            rightZero[j] = rightZero[j + 1] + ('1' - S[n - 1]);
        }
        
        int result = n;
        for (int i = 1; i < n + 2; i++) {
            result = min(result, leftOne[i - 1] + rightZero[i]);
        }
        return result;
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
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    
    s.minFlipsMonoIncr("00011000");
    return 0;
}
