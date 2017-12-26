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
    int minVal;
    int result;
    void search(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        if (root -> val > minVal && root -> val < result) {
            result = root -> val;
            return;
        }

        if (root -> val == minVal) {
            search(root -> left);
            search(root -> right);
        }

        return;
    }
public:
    int findSecondMinimumValue(TreeNode* root) {
        minVal = root -> val;
        result = INT_MAX;
        search(root);
        return result < INT_MAX ? result : -1;
    }
};