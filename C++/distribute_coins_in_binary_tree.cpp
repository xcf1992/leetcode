/*
979. Distribute Coins in Binary Tree
https://leetcode.com/problems/distribute-coins-in-binary-tree/

Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to another.
(The move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.

Example 1:
    3
0       0
Input: [3,0,0]
Output: 2
Explanation:
From the root of the tree, we move one coin to its left child, and one coin to its right child.

Example 2:
    0
3       0
Input: [0,3,0]
Output: 3
Explanation:
From the left child of the root, we move two coins to the root [taking two moves].
Then, we move one coin from the root of the tree to the right child.

Example 3:
    1
0       2
Input: [1,0,2]
Output: 2

Example 4:
    1
0       0
  3
Input: [1,0,0,null,3]
Output: 4

Note:

1<= N <= 100
0 <= node.val <= N
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int traverse(TreeNode* root, int& result) { // return number of coins we should pass to parent
        if (root == nullptr) {
            return 0;
        }

        int leftCarry = traverse(root -> left, result);
        int rightCarry = traverse(root -> right, result);
        result += abs(leftCarry) + abs(rightCarry); // we abs here as it may happen we should give coin to child actually
        return leftCarry + rightCarry + root -> val - 1;
    }
public:
    int distributeCoins(TreeNode* root) {
        int result = 0;
        traverse(root, result);
        return result;
    }
};

class Solution1 {
private:
    void check(TreeNode* root, int& result) {
        if (root == nullptr) {
            return;
        }

        check(root -> left, result);
        check(root -> right, result);
        if (root -> left != nullptr) {
            int move = (root -> left -> val) - 1;
            result += abs(move);
            (root -> val) += move;
        }
        if (root -> right != nullptr) {
            int move = (root -> right -> val) - 1;
            result += abs(move);
            (root -> val) += move;
        }
        return;
    }
public:
    int distributeCoins(TreeNode* root) {
        int result = 0;
        check(root, result);
        return result;
    }
};

