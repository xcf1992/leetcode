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
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftValue = 0;
        if (root -> left != nullptr && root -> left -> left == nullptr && root -> left -> right == nullptr) {
            leftValue = root -> left -> val;
        }
        else {
            leftValue = sumOfLeftLeaves(root -> left);
        }

        return leftValue + sumOfLeftLeaves(root -> right);
    }
};

int main() {
    Solution s;
    return 0;
}