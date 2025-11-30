/*
663. Equal Tree Partition
Given a binary tree with n nodes,
your task is to check if it's possible to partition the tree to two trees
which have the equal sum of values after removing exactly one edge on the original tree.

Example 1:
Input:
    5
   / \
  10 10
    /  \
   2   3

Output: True
Explanation:
    5
   /
  10

Sum: 15

   10
  /  \
 2    3

Sum: 15
Example 2:
Input:
    1
   / \
  2  10
    /  \
   2   20

Output: False
Explanation: You can't split the tree into two trees with equal sum after removing exactly one edge on the tree.
Note:
The range of tree node value is in the range of [-100000, 100000].
1 <= n <= 10000
*/
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

class Solution {
private:
    int getSum(TreeNode* root, unordered_map<int, int>& count) {
        if (root == nullptr) {
            return 0;
        }

        int sum = root->val + getSum(root->left, count) + getSum(root->right, count);
        count[sum] += 1;
        return sum;
    }

public:
    bool checkEqualTree(TreeNode* root) {
        unordered_map<int, int> count;
        int sum = getSum(root, count);
        if (sum % 2 != 0) {
            return false;
        }

        if (sum == 0) {
            return count[0] > 1;
        }
        return count.find(sum / 2) != count.end();
    }
};