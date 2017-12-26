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
private:
    int getSum(TreeNode* root, unordered_map<TreeNode*, int>& treeSum) {
        if (root == nullptr) {
            return 0;
        }

        int sum = root -> val + getSum(root -> left, treeSum) + getSum(root -> right, treeSum);
        treeSum[root] = sum;
        return sum;
    }
public:
    bool checkEqualTree(TreeNode* root) {
        unordered_map<TreeNode*, int> treeSum;
        int sum = getSum(root, treeSum);

        return sum % 2 == 0 && treeSum.find(sum / 2) != treeSum.end();
    }
};