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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
private:
    int find(TreeNode* root, int& diameter) {
        if (root == nullptr) {
            return 0;
        }

        int leftLength = find(root -> left, diameter);
        int rightLength = find(root -> right, diameter);
        diameter = max(diameter, leftLength + rightLength);
        return max(leftLength, rightLength) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        find(root, diameter);
        return diameter;
    }
};