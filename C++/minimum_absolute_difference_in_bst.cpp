/*
530. Minimum Absolute Difference in BST
Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).


Note: There are at least two nodes in this BST.
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
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    void find(TreeNode* root, TreeNode*& prev, long& result) {
        if (root == nullptr) {
            return;
        }

        find(root -> left, prev, result);
        if (prev != nullptr) {
            if (result == -1) {
                result = abs(root -> val - prev -> val);
            }
            else {
                result = min(result, (long)abs(prev -> val - root -> val));
            }
        }

        prev = root;
        find(root -> right, prev, result);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        long result = -1;
        TreeNode* prev = nullptr;
        find(root, prev, result);
        return result;
    }
};
