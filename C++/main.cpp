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

class Solution1 {
public:
    int smallestRangeII(vector<int> A, int K) {
        int tempMin = INT_MAX;
        int tempMax = INT_MIN;
        for (int num : A) {
            tempMin = min(num, tempMin);
            tempMax = max(num, tempMax);
        }
        int curMin = INT_MAX;
        int curMax = INT_MIN;
        if (tempMax - tempMin > K) {
            curMin = min(tempMin + K, tempMax - K);
            curMax = max(tempMin + K, tempMax - K);
        }
        else {
            curMin = tempMin + K;
            curMax = tempMax + K;
        }
        int result = curMax - curMin;
        for (int num : A) {
            if (num + K <= curMax && num + K >= curMin) {
                continue;
            }
            if (num - K <= curMax && num - K >= curMin) {
                continue;
            }
            int newMin = num - K;
            int newMax = num + K;
            if (newMax < curMin) {
                curMin = newMax;
            }
            else if (newMin > curMax) {
                curMax = newMin;
            }
            else if (newMin < curMin && newMax > curMax) {
                if (newMax - curMin > curMax - newMin) {
                    curMin = newMin;
                }
                else {
                    curMax = newMax;
                }
            }
            result = curMax - curMin;
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
    
    s.smallestRangeII({1}, 0);
    return 0;
}
