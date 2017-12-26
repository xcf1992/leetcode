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
    int traverse(TreeNode* root, int value) {
        if (root == nullptr) {
            return value;
        }

        root -> val += traverse(root -> right, value);
        return traverse(root -> left, root -> val);
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }

        root -> val += traverse(root -> right, 0);
        traverse(root -> left, root -> val);
        return root;
    }
};

int main() {
    Solution s;
    return 0;
}