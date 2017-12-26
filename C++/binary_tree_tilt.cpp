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

/*
Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input:
         1
       /   \
      2     3
Output: 1
Explanation:
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:

The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
 */

class Solution {
private:
    int calculate(TreeNode* root, int& tilt) {
        if (root == nullptr) {
            return 0;
        }

        int sum = root -> val;
        int left = calculate(root -> left, tilt);
        int right = calculate(root -> right, tilt);
        tilt += abs(left - right);
        return sum + left + right;
    }
public:
    int findTilt(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int tilt = 0;
        int left = calculate(root -> left, tilt);
        int right = calculate(root -> right, tilt);

        return tilt + abs(left - right);
    }
};

int main() {
    Solution s;
    return 0;
}
