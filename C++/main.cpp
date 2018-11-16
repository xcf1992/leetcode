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
    int shortestSubarray(vector<int> A, int K) {
        int n = A.size();
        if (n == 0) {
            return -1;
        }
        int result = n + 1;
        int left = 0;
        int right = 0;
        int sum = A[0];
        while (right < n and left < n) {
            if (sum < K) {
                right += 1;
                if (right < n) {
                    sum += A[right];
                }
            }
            else if (left <= right){
                result = min(result, right - left + 1);
                sum -= A[left];
                left += 1;
            }
        }
        while (sum >= K and left < right) {
            result = min(result, right - left + 1);
            sum -= A[left];
            left += 1;
        }
        return result > n ? -1 : result;
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
    
    s.shortestSubarray({84,-37,32,40,95}, 167);
    return 0;
}
