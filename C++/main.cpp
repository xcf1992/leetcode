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

class Solution { // DFS with memo
private:
    unordered_map<string, int> memo;
public:
    int kSimilarity(string cur, string target) {
        if (cur == target) {
            return 0;
        }

        if (memo.find(cur) != memo.end()) {
            return memo[cur];
        }

        int pos = 0;
        int len = cur.size();
        for (; pos < len; ++pos) {
            if (cur[pos] != target[pos]) {
                break;
            }
        }

        memo[cur] = len;
        for (int i = pos + 1; i < len; ++i) {
            if (cur[i] == target[pos]) {
                swap(cur[pos], cur[i]);
                memo[cur] = min(memo[cur], 1 + kSimilarity(cur, target));
                swap(cur[pos], cur[i]);
            }
        }
        return memo[cur];
    }
};

int main() {
    Solution s;
    vector<int> temp({2,7,9,4,4});
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
    s.kSimilarity("ab", "ba");
}
