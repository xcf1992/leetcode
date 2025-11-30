/*
1430. Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
https://leetcode.com/problems/check-if-a-string-is-a-valid-sequence-from-root-to-leaves-path-in-a-binary-tree/

Given a binary tree where each path going from the root to any leaf form a valid sequence,
check if a given string is a valid sequence in such binary tree.

We get the given string from the concatenation of an array of integers arr
and the concatenation of all values of the nodes along a path results in a sequence in the given binary tree.

Example 1:
                                    0
            1                                           0
    1               0                               0
        1        0    0
Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,0,1]
Output: true
Explanation:
The path 0 -> 1 -> 0 -> 1 is a valid sequence (green color in the figure).
Other valid sequences are:
0 -> 1 -> 1 -> 0
0 -> 0 -> 0

Example 2:
Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,0,1]
Output: false
Explanation: The path 0 -> 0 -> 1 does not exist, therefore it is not even a sequence.

Example 3:
Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,1]
Output: false
Explanation: The path 0 -> 1 -> 1 is a sequence, but it is not a valid sequence.

Constraints:
1 <= arr.length <= 5000
0 <= arr[i] <= 9
Each node's value is between [0 - 9].
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    bool check(TreeNode* root, vector<int>& arr, int index) {
        if (root == nullptr) {
            return false;
        }

        if (root->val != arr[index]) {
            return false;
        }

        if (root->left == nullptr and root->right == nullptr) {
            return index == arr.size() - 1;
        }

        if (index == arr.size() - 1) {
            return false;
        }
        return check(root->left, arr, index + 1) or check(root->right, arr, index + 1);
    }

public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        if (root == nullptr) {
            return arr.size() == 0;
        }
        if (arr.size() == 0) {
            return false;
        }
        return check(root, arr, 0);
    }
};
