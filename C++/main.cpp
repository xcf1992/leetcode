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
    int smallestRangeI(vector<int> A, int K) {
        int result = 0;
        int curMin = A[0] - K;
        int curMax = A[0] + K;
        for (int i = 1; i < A.size(); i++) {
            int newMin = A[i] - K;
            int newMax = A[i] + K;
            if (result == 0) {
                if (newMin > curMax || newMax < curMin) {
                    if (curMin > newMax) {
                        curMax = curMin;
                        curMin = newMax;
                    }
                    else {
                        curMin = curMax;
                        curMax = newMin;
                    }
                    result = curMax - curMin;
                }
                else {
                    newMin = max(newMin, curMin);
                    newMax = min(newMax, curMax);
                }
            }
            else {
                if (newMin > curMax) {
                    curMax = newMin;
                }
                else if (newMax < curMin) {
                    curMin = newMax;
                }
                result = curMax - curMin;
            }
        }
        return result;
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
    
    s.smallestRangeI({3,1,10}, 4);
    return 0;
}
