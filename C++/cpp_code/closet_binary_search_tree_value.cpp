/*
270. Closest Binary Search Tree Value

Given a non-empty binary search tree and a target value,
find the value in the BST that is closest to the target.

Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.

Example:
Input: root = [4,2,5,1,3], target = 3.714286
    4
   / \
  2   5
 / \
1   3
Output: 4
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
#include <map>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closet = root -> val;
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (abs(target - cur -> val) < abs(target - closet)) {
                closet = cur -> val;
            }
            cur = cur -> val > target ? cur -> left : cur -> right;
        }
        return closet;
    }
};
