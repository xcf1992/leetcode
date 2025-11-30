#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

/*
Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /
  4

Output: "1(2(4))(3)"

Explanation: Originally it needs to be "1(2(4)())(3()())",
but you need to omit all the unnecessary empty parenthesis pairs.
And it will be "1(2(4))(3)".

Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \
      4

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example,
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the
output.
*/
class Solution {
public:
    string tree2str(TreeNode* t) {
        string result = "";
        if (t) {
            result = to_string(t->val);
            if (t->left) {
                result += "(" + tree2str(t->left) + ")";
            } else if (t->right) {
                result += "()";
            }
            if (t->right) {
                result += "(" + tree2str(t->right) + ")";
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}