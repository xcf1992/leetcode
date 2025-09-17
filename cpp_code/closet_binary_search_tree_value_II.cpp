/*
272. Closest Binary Search Tree Value II

Given a non-empty binary search tree and a target value,
find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Example:
Input: root = [4,2,5,1,3], target = 3.714286, and k = 2
    4
   / \
  2   5
 / \
1   3
Output: [4,3]

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?
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
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        stack<TreeNode*> larger;
        stack<TreeNode*> smaller;
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (cur -> val > target) {
                larger.push(cur);
                cur = cur -> left;
            }
            else {
                smaller.push(cur);
                cur = cur -> right;
            }
        }

        vector<int> closet;
        while (closet.size() < k) {
            // update left parents stack to have the next closest node on top
            if (larger.empty() or (!smaller.empty() and larger.top() -> val - target > target - smaller.top() -> val)) {
                cur = smaller.top();
                smaller.pop();
                closet.push_back(cur -> val);

                cur = cur -> left;
                while (cur != nullptr) {
                    smaller.push(cur);
                    cur = cur -> right;
                }
            }
            else { // update right parents stack to have the next closest node on top
                cur = larger.top();
                larger.pop();
                closet.push_back(cur -> val);

                cur = cur -> right;
                while (cur != nullptr) {
                    larger.push(cur);
                    cur = cur -> left;
                }
            }
        }
        return closet;
    }
};

class Solution1 { // O(n) solution, easier to understand
private:
    void find(TreeNode* root, double target, int k, deque<int>& result) {
        if (root == nullptr) {
            return;
        }

        find(root -> left, target, k, result);

        result.push_back(root -> val);
        if (result.size() > k) {
            if (abs(result.front() - target) > abs(result.back() - target)) {
                result.pop_front();
            }
            else {
                result.pop_back();
            }
        }

        find(root -> right, target, k, result);
    }
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        deque<int> result;
        find(root, target, k, result);
        return vector<int>(result.begin(), result.end());
    }
};
