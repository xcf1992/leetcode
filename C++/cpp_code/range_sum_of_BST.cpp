/*
 938. Range Sum of BST
 Given the root node of a binary search tree,
 return the sum of values of all nodes with value between L and R (inclusive).

 The binary search tree is guaranteed to have unique values.



 Example 1:

 Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
 Output: 32
 Example 2:

 Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
 Output: 23


 Note:

 The number of nodes in the tree is at most 10000.
 The final answer is guaranteed to be less than 2^31.
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
#include <climits>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void count(TreeNode* root, int L, int R, int& result) {
        if (root == nullptr) {
            return;
        }

        if (root->val <= R and root->val >= L) {
            result += root->val;
        }
        count(root->left, L, R, result);
        count(root->right, L, R, result);
    }

public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        int result = 0;
        count(root, L, R, result);
        return result;
    }
};