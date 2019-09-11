/*
652. Find Duplicate Subtrees

Given a binary tree, return all duplicate subtrees.
For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1:

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:

      2
     /
    4
and
    4
Therefore, you need to return above trees' root in the form of a list.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    string parse(TreeNode* root, unordered_map<string, vector<TreeNode*>>& duplicates) {
        if (root == nullptr) {
            return "";
        }

        string rootStr = "(" + parse(root -> left, duplicates) + ")" +
                         to_string(root -> val) +
                         "(" + parse(root -> right, duplicates) + ")";
        duplicates[rootStr].push_back(root);
        return rootStr;
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, vector<TreeNode*>> duplicates;
        vector<TreeNode*> result;
        parse(root, duplicates);
        for (auto& nodes : duplicates) {
            if (nodes.second.size() > 1) {
                result.push_back(nodes.second.front());
            }
        }
        return result;
    }
};
