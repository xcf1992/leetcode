/*
 145. Binary Tree Postorder Traversal
 Given a binary tree, return the postorder traversal of its nodes' values.

 Example:

 Input: [1,null,2,3]
 1
   \
    2
   /
  3

 Output: [3,2,1]
 Follow up: Recursive solution is trivial, could you do it iteratively?
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;


struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        vector<int> result;
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode* cur = stk.top();
            stk.pop();
            result.push_back(cur -> val);

            if (cur -> left) {
                stk.push(cur -> left);
            }
            if (cur -> right) {
                stk.push(cur -> right);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
