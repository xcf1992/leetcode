/*
501. Find Mode in Binary Search Tree
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.


For example:
Given BST [1,null,2,2],

   1
    \
     2
    /
   2


return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
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
#include <map>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    TreeNode* pre;

    void find(TreeNode* root, vector<int>& result, int& count, int& maxCount) {
        if (root == nullptr) {
            return;
        }
        find(root -> left, result, count, maxCount);

        if (pre == nullptr) {
            count = 1;
        }
        else if (root -> val == pre -> val) {
            count += 1;
        }
        else {
            if (count > maxCount) {
                result.clear();
                result.push_back(pre -> val);
                maxCount = count;
            }
            else if (count == maxCount) {
                result.push_back(pre -> val);
            }
            count = 1;
        }
        pre = root;

        find(root -> right, result, count, maxCount);
    }
public:
    vector<int> findMode(TreeNode* root) {
        int maxCount = 0;
        int count = 0;
        pre = nullptr;
        vector<int> result;

        find(root, result, count, maxCount);
        if (pre == nullptr) { // we need to check for last several nodes if they have the same value, cause there may have no chance to update if they are all the same
            return result;
        }
        if (count == maxCount) {
            result.push_back(pre -> val);
        }
        if (count > maxCount) {
            result.clear();
            result.push_back(pre -> val);
        }
        return result;
    }
};
