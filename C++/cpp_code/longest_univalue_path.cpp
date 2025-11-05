/*
 687. Longest Univalue Path
 Given a binary tree,
 find the length of the longest path where each node in the path has the same value.
 This path may or may not pass through the root.

 Note: The length of path between two nodes is represented by the number of edges between them.

 Example 1:

 Input:

     5
    / \
   4   5
  / \   \
 1   1   5
 Output:

 2
 Example 2:

 Input:

     1
    / \
   4   5
  / \   \
 4   4   5
 Output:

 2
 Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
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
#include <set>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int getPathLenth(TreeNode *root, int &result, long pValue) {
        if (root == nullptr) {
            return 0;
        }

        int leftLen = getPathLenth(root->left, result, root->val);
        int rightLen = getPathLenth(root->right, result, root->val);
        result = max(result, leftLen + rightLen + 1);
        return pValue == root->val ? max(leftLen, rightLen) + 1 : 0;
    }

public:
    int longestUnivaluePath(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int result = 0;
        getPathLenth(root, result, (long) INT_MIN - 1);
        return result - 1;
    }
};