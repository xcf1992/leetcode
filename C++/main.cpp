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
    bool findDuplicate(string& result, char c, int k) {
        if (result.size() < k - 1) {
            return false;
        }

        int n = result.size();
        if (result.substr(n - k + 1) == string(n - 1, c)) {
            result = result.substr(0, n - k + 1);
            return true;
        }
        return false;
    }
public:
    string removeDuplicates(string s, int k) {
        int n = s.size();
        if (n < k) {
            return s;
        }

        string result = "";
        result.push_back(s[0]);
        for (int i = 1; i < n; ++i) {
            if (!findDuplicate(result, s[i], k)) {
                result.push_back(s[i]);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    s.removeDuplicates("deeedbbcccbdaa", 3);

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
