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
    bool sameTree(TreeNode* s, TreeNode* t) {
        if (s == nullptr && t == nullptr) {
            return true;
        }
        if (s == nullptr || t == nullptr) {
            return false;
        }

        if (s -> val != t -> val) {
            return false;
        }

        return sameTree(s -> left, t -> left) && sameTree(s -> right, t -> right);
    }
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (t == nullptr) {
            return true;
        }

        if (s == nullptr) {
            return false;
        }

        return sameTree(s, t) || isSubtree(s -> left, t) || isSubtree(s -> right, t);
    }
};