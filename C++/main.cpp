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
    int find(string s, int k, int start, int end) {
        if (start > end) {
            return 0;
        }
        
        vector<int> count(26, 0);
        for (int i = start; i <= end; i++) {
            count[s[i] - 'a'] += 1;
        }
        
        int pos = start;
        while (pos <= end and count[s[pos] - 'a'] >= k) {
            pos += 1;
        }
        if (pos > end) {
            return end - start + 1;
        }
        
        int result = 0;
        int left = start;
        for (int i = start; i <= end; ++i) {
            if (count[s[start] - 'a'] < k) {
                result = max(result, find(s, k, left, i - 1));
                left = i + 1;
            }
        }
        return max(result, find(s, k, left, end));
    }
public:
    int longestSubstring(string s, int k) {
        return find(s, k, 0, s.size() - 1);
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
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
    vector<string> words({"10","0001","111001","1","0"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.longestSubstring("aaabb", 3);
}
