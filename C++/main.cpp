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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    unordered_map<int, unordered_map<int, int>> memo;

    int dfs(int cur, int prev, vector<int>& arr1, vector<int>& arr2) {
        if (cur >= arr1.size()) {
            return 0;
        }

        if (memo.find(cur) != memo.end() and memo[cur].find(prev) != memo[cur].end()) {
            return memo[cur][prev];
        }

        memo[cur][prev] = INT_MAX;
        if (arr1[cur] > prev) {
            memo[cur][prev] = min(memo[cur][prev], dfs(cur + 1, arr1[cur], arr1, arr2));
        }

        auto it = upper_bound(arr2.begin(), arr2.end(), prev);
        if (it != arr2.end() and *it < arr1[cur]) {
            int move = dfs(cur + 1, *it, arr1, arr2);
            if (move != INT_MAX) {
                memo[cur][prev] = min(memo[cur][prev], 1 + move);
            }
        }
        return memo[cur][prev];
    }
public:
    int makeArrayIncreasing(vector<int> arr1, vector<int> arr2) { // dfs with memo
        sort(arr2.begin(), arr2.end());
        int result = dfs(0, INT_MIN, arr1, arr2);
        return result == INT_MAX ? -1 : result;
    }
};

int main() {
    Solution s;
    s.makeArrayIncreasing({1,5,3,6,7}, {1,3,4});

    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
}
