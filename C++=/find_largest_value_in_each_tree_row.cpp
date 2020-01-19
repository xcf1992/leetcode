/*
515. Find Largest Value in Each Tree Row
https://leetcode.com/problems/find-largest-value-in-each-tree-row/

You need to find the largest value in each row of a binary tree.
Example:
Input:
          1
         / \
        3   2
       / \   \
      5   3   9
Output: [1, 3, 9]
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
#include "extra_data_types.hpp"
using namespace std;

class Solution { // dfs
private:
    void dfs(int depth, TreeNode* root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }

        if (depth == result.size()) {
            result.push_back(root -> val);
        }
        else {
            result[depth] = max(result[depth], root -> val);
        }
        dfs(depth + 1, root -> left, result);
        dfs(depth + 1, root -> right, result);
    }
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        dfs(0, root, result);
        return result;
    }
};

class Solution1 { // bfs
public:
    vector<int> largestValues(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        vector<int> result;
        queue<TreeNode*> row;
        row.push(root);
        while (!row.empty()) {
            int max_value = INT_MIN;
            int curSize = row.size();
            for (int i = 0; i < curSize; ++i) {
                TreeNode* current = row.front();
                row.pop();
                
                max_value = max(max_value, current -> val);
                if (current -> left != nullptr) {
                    row.push(current -> left);
                }
                if (current -> right != nullptr) {
                    row.push(current -> right);
                }
            }
            result.push_back(max_value);
        }
        return result;
    }
};
