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
    unordered_map<string, int> memo;
public:
    int longestDecomposition(string text) {
        int n = text.size();
        if (n <= 1) {
            return n;
        }

        if (memo.find(text) != memo.end()) {
            return memo[text];
        }

        memo[text] = 1;
        for (int len = 1; len <= n / 2; ++len) {
            string left = text.substr(len);
            string right = text.substr(n - len, len);
            if (left == right) {
                memo[text] = max(memo[text], 2 + longestDecomposition(text.substr(len, n - len * 2)));
            }
        }
        return memo[text];
    }
};

int main() {
    Solution s;
    vector<int> temp({1,17,8});
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
    s.longestDecomposition("ghiabcdefhelloadamhelloabcdefghi");
}
