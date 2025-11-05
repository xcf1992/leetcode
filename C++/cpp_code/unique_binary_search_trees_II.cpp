/*
95. Unique Binary Search Trees II
https://leetcode.com/problems/unique-binary-search-trees-ii/

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:
Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
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
private:
    vector<TreeNode *> generate(int start, int end) {
        if (start > end) {
            return {nullptr};
        }
        if (start == end) {
            return {new TreeNode(start)};
        }

        vector<TreeNode *> result;
        for (int i = start; i <= end; i++) {
            for (TreeNode *lc: generate(start, i - 1)) {
                for (TreeNode *rc: generate(i + 1, end)) {
                    TreeNode *root = new TreeNode(i);
                    root->left = lc;
                    root->right = rc;
                    result.push_back(root);
                }
            }
        }
        return result;
    }

public:
    vector<TreeNode *> generateTrees(int n) {
        if (n == 0) {
            return {};
        }
        return generate(1, n);
    }
};