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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (root == nullptr) {
            return root;
        }

        if (root -> val > R) {
            return trimBST(root -> left);
        }

        if (root -> val < L) {
            return trimBST(root -> right);
        }

        root -> left = trimBST(root -> left, L, R);
        root -> left = trimBST(root -> right, L, R);
        return root;
    }
};