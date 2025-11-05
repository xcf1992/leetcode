/*
894. All Possible Full Binary Trees
https://leetcode.com/problems/all-possible-full-binary-trees/

A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Return a list of all possible full binary trees with N nodes.
Each element of the answer is the root node of one possible tree.

Each node of each tree in the answer must have node.val = 0.
You may return the final list of trees in any order.

Example 1:
Input: 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:

Note:
1 <= N <= 20
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    unordered_map<int, vector<TreeNode *> > memo;

public:
    vector<TreeNode *> allPossibleFBT(int N) {
        if (N % 2 == 0) {
            return {};
        }

        if (N == 1) {
            return {new TreeNode(0)};
        }

        if (memo.find(N) != memo.end()) {
            return memo[N];
        }

        for (int i = 1; i <= N - 2; i += 2) {
            vector<TreeNode *> leftChildren = allPossibleFBT(i);
            vector<TreeNode *> rightChildren = allPossibleFBT(N - 1 - i);
            for (TreeNode *lc: leftChildren) {
                for (TreeNode *rc: rightChildren) {
                    TreeNode *root = new TreeNode(0);
                    root->left = lc;
                    root->right = rc;
                    memo[N].push_back(root);
                }
            }
        }
        return memo[N];
    }
};

class Solution1 {
public:
    vector<TreeNode *> allPossibleFBT(int N) {
        if (N % 2 == 0) {
            return {};
        }

        if (N == 1) {
            return {new TreeNode(0)};
        }

        vector<TreeNode *> result;
        for (int i = 1; i <= N - 1; i += 2) {
            vector<TreeNode *> leftChildren = allPossibleFBT(i);
            vector<TreeNode *> rightChildren = allPossibleFBT(N - 1 - i);
            for (TreeNode *lc: leftChildren) {
                for (TreeNode *rc: rightChildren) {
                    TreeNode *root = new TreeNode(0);
                    root->left = lc;
                    root->right = rc;
                    result.push_back(root);
                }
            }
        }
        return result;
    }
};