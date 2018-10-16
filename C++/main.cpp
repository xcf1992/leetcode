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
    int threeSumMulti(vector<int> A, int target) {
        int MOD = 1e9 + 7;
        sort(A.begin(), A.end());
        unordered_map<int, int> count;
        vector<int> sorted;
        for (int i : A) {
            count[i] += 1;
            if (count[i] == 1) {
                sorted.push_back(i);
            }
        }
        
        int result = 0;
        int n = sorted.size();
        for (int i = 0; i < n; i++) {
            int needed = target - sorted[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                if (sorted[left] + sorted[right] == needed) {
                    int x =count[sorted[i]] * count[sorted[left]] * count[sorted[right]];
                    int temp = (x) % MOD;
                    result = (result + temp) % MOD;
                    left += 1;
                }
                else if (sorted[left] + sorted[right] < needed) {
                    left += 1;
                }
                else {
                    right -= 1;
                }
            }
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
    
    s.threeSumMulti({1,1,2,2,3,3,4,4,5,5}, 8);
    return 0;
}
