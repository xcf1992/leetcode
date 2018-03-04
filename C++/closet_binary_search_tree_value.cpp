/*
 Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
 
 Note:
 Given target value is a floating point.
 You are guaranteed to have only one unique value in the BST that is closest to the target.
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
using namespace std;


  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

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
