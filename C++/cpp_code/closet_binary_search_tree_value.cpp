/*
270. Closest Binary Search Tree Value

Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target. If
there are multiple answers, print the smallest.

Example:
Input: root = [4,2,5,1,3], target = 3.714286
    4
   / \
  2   5
 / \
1   3
Output: 4
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
#include <map>

using namespace std;

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closet = root->val;
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (abs(target - cur->val) < abs(target - closet)) {
                closet = cur->val;
            } else if (abs(target - cur->val) == abs(target - closet) && cur->val < closet) {
                closet = cur->val;
            }
            cur = cur->val > target ? cur->left : cur->right;
        }
        return closet;
    }
};