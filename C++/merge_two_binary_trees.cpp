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
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 * Input:
 *      Tree 1                     Tree 2
          1                         2
         / \                       / \
        3   2                     1   3
       /                           \   \
      5                             4   7
Output:
Merged tree:
         3
        / \
       4   5
      / \   \
     5   4   7
 */
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 && t2) {
            TreeNode* root = new TreeNode(t1 -> val + t2 -> val);
            root -> left = mergeTrees(t1 -> left, t2 -> left);
            root -> right = mergeTrees(t1 -> right, t2 -> right);
            return root;
        }

        return t1 ? t1 : t2;
    }
};

int main() {
    Solution s;
    return 0;
}
