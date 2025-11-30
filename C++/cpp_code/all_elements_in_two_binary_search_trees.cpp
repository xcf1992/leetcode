/*
1305. All Elements in Two Binary Search Trees
https://leetcode.com/problems/all-elements-in-two-binary-search-trees/

Given two binary search trees root1 and root2.
Return a list containing all the integers from both trees sorted in ascending order.

Example 1:
Input: root1 = [2,1,4], root2 = [1,0,3]
Output: [0,1,1,2,3,4]

Example 2:
Input: root1 = [0,-10,10], root2 = [5,1,7,0,2]
Output: [-10,0,0,1,2,5,7,10]

Example 3:
Input: root1 = [], root2 = [5,1,7,0,2]
Output: [0,1,2,5,7]

Example 4:
Input: root1 = [0,-10,10], root2 = []
Output: [-10,0,10]

Example 5:
Input: root1 = [1,null,8], root2 = [8,1]
Output: [1,1,8,8]

Constraints:
Each tree has at most 5000 nodes.
Each node's value is between [-10^5, 10^5].
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void pushLeft(stack<TreeNode*>& stk, TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        stk.push(root);
        pushLeft(stk, root->left);
    }

public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        stack<TreeNode*> s1;
        pushLeft(s1, root1);  // we need push all the left tree nodes to the stack at the beginning
        stack<TreeNode*> s2;
        pushLeft(s2, root2);
        vector<int> result;
        while (!s1.empty() or !s2.empty()) {
            stack<TreeNode*>& temp = s1.empty() ? s2 : (s2.empty() ? s1 : (s1.top()->val > s2.top()->val ? s2 : s1));
            TreeNode* cur = temp.top();
            temp.pop();
            result.push_back(cur->val);
            pushLeft(temp, cur->right);
        }
        return result;
    }
};