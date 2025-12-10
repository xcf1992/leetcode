/*
549. Binary Tree Longest Consecutive Sequence II
Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.

Especially, this path can be either increasing or decreasing.
For example, [1,2,3,4] and [4,3,2,1] are both considered valid,
but the path [1,2,4,3] is not valid.
On the other hand, the path can be in the child-Parent-child order,
where not necessarily be parent-child order.

Example 1:
Input:
  1
 / \
2   3
Output: 2
Explanation: The longest consecutive path is [1, 2] or [2, 1].
Example 2:
Input:
  2
 / \
1   3
Output: 3
Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
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
#include <climits>
#include <map>

using namespace std;

class Solution {
private:
    vector<int> traverse(TreeNode* root, int& result) {  // return the lenght of longest path with gap {-1, 1}
        if (root == nullptr) {
            return {0, 0};
        }

        vector<int> l1 = traverse(root->left, result);
        vector<int> l2 = traverse(root->right, result);
        if (root->left != nullptr) {
            if (root->left->val != root->val - 1) {
                l1[0] = 0;
            }
            if (root->left->val != root->val + 1) {
                l1[1] = 0;
            }
        }
        if (root->right != nullptr) {
            if (root->right->val != root->val - 1) {
                l2[0] = 0;
            }
            if (root->right->val != root->val + 1) {
                l2[1] = 0;
            }
        }
        result = max(result, 1 + max(l1[0] + l2[1], l1[1] + l2[0]));
        return {1 + max(l1[0], l2[0]), 1 + max(l1[1], l2[1])};
    }

public:
    int longestConsecutive(TreeNode* root) {
        int result = 0;
        traverse(root, result);
        return result;
    }
};

class Solution1 {
private:
    int findPath(TreeNode* root, int preVal, int diff) {
        if (root == nullptr) {
            return 0;
        }

        if (root->val == preVal + diff) {
            return max(findPath(root->left, root->val, diff), findPath(root->right, root->val, diff)) + 1;
        }
        return 0;
    }

public:
    int longestConsecutive(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int l1 = findPath(root->left, root->val, -1) + findPath(root->right, root->val, 1) + 1;
        int l2 = findPath(root->left, root->val, 1) + findPath(root->right, root->val, -1) + 1;
        int longest = max(longestConsecutive(root->left), longestConsecutive(root->right));

        return max(longest, max(l1, l2));
    }
};
