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
    vector<int> leaves;

    void traverse(TreeNode*& root) { // !!! use TreeNode*& here rather than TreeNode*
        if (root == nullptr) {
            return;
        }

        if (root -> left == nullptr && root -> right == nullptr) {
            leaves.push_back(root -> val);
            root = nullptr;
            return;
        }

        traverse(root -> left);
        traverse(root -> right);
    }

public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;
        while (root != nullptr) {
            traverse(root);
            result.push_back(leaves);
            leaves.clear();
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}