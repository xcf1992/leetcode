/*
144. Binary Tree Preorder Traversal
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
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
            if (cur -> right) {
                stk.push(cur -> right);
            }
            if (cur -> left) {
                stk.push(cur -> left);
            }
        }
        return result;
    }
};
