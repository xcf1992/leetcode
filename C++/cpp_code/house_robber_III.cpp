/*
337. House Robber III

The thief has found himself a new place for his thievery again.
There is only one entrance to this area, called the "root."
Besides the root, each house has one and only one parent house.
After a tour, the smart thief realized that "all houses in this place forms a binary tree".
It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \
     3   1

Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:

Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
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
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    unordered_map<TreeNode*, int> cache;
public:
    int rob(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if (cache.find(root) != cache.end()) {
            return cache[root];
        }

        int maxMoney = root -> val;
        if (root -> left != nullptr) {
            maxMoney += rob(root -> left -> left) + rob(root -> left -> right);
        }
        if (root -> right != nullptr) {
            maxMoney += rob(root -> right -> left) + rob(root -> right -> right);
        }
        cache[root] = max(maxMoney, rob(root -> left) + rob(root -> right));
        return cache[root];
    }
};
