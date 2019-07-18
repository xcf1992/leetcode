/*
538. Convert BST to Greater Tree

Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
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
#include "extra_data_types.hpp"
using namespace std;

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
        traverse(root, 0);
        return root;
    }
};

int main() {
    Solution s;
    return 0;
}