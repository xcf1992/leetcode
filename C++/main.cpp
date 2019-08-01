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
public:
    string makeLargestSpecial(string S) {
        vector<string> specials;
        int count = 0;
        for (char c : S) {
            if (count == 0) {
                specials.push_back("");
            }
            count += c == '1' ? 1 : -1;
            specials.back().push_back(c);
        }

        for (string& special : specials) {
            special = "1" + makeLargestSpecial(special.substr(1, special.size() - 2)) + "0";
        }

        sort(specials.begin(), specials.end(), [](string& a, string& b) {
            return a > b;
        });
        string result = "";
        for (string special : specials) {
            result += special;
        }
        return result;
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
    s.makeLargestSpecial("11011000");
}
