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
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode* newRoot = new TreeNode(v);
            newRoot -> left = root;
            return newRoot;
        }

        queue<TreeNode*> row;
        row.push(root);
        row.push(nullptr);
        int depth = 1;
        while (depth < d - 1) {
            while (row.front() != nullptr) {
                TreeNode* node = row.front();
                if (node -> left) {
                    row.push(node->left);
                }
                if (node -> right) {
                    row.push(node -> right);
                }
                row.pop();
            }
            row.pop();
            row.push(nullptr);
            depth += 1;
        }

        while (row.front() != nullptr) {
            TreeNode* node = row.front();

            TreeNode* newLeft = new TreeNode(v);
            newLeft -> left = node -> left;
            node -> left = newLeft;

            TreeNode* newRight = new TreeNode(v);
            newRight -> right = node -> right;
            node -> right = newRight;

            row.pop();
        }

        return root;
    }
};

int main() {
    Solution s;
    return 0;
}
