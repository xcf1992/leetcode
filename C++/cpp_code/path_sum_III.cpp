/*
437. Path Sum III

You are given a binary tree in which each node contains an integer value.
Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf,
but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:
root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1
Return 3. The paths that sum to 8 are:
1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
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

class Solution {
    // prefix sum
private:
    void dfs(TreeNode* root, int curSum, int target, int& result, unordered_map<int, int>& count) {
        if (root == nullptr) {
            return;
        }

        curSum += root->val;
        result += count[curSum - target];
        count[curSum] += 1;
        dfs(root->left, curSum, target, result, count);
        dfs(root->right, curSum, target, result, count);
        count[curSum] -= 1;
        // IMPORTANT here, as we pop back to upper level current sum would not be valid anymore, so we need to minus 1
        // here
    }

public:
    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> count;
        count[0] = 1;
        int result = 0;
        dfs(root, 0, sum, result, count);
        return result;
    }
};

class Solution1 {
private:
    int getAllPaths(TreeNode* root, int pre, int sum) {
        if (root == nullptr) {
            return 0;
        }

        int cur = pre + root->val;
        return (cur == sum) + getAllPaths(root->left, cur, sum) + getAllPaths(root->right, cur, sum);
    }

public:
    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr) {
            return 0;
        }
        return getAllPaths(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
};