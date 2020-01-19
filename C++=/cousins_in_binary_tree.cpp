/*
 993. Cousins in Binary Tree

 In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

 Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

 We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

 Return true if and only if the nodes corresponding to the values x and y are cousins.

 Example 1:
                1
        2               3
    4
 Input: root = [1,2,3,4], x = 4, y = 3
 Output: false
 Example 2:


 Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
 Output: true
 Example 3:



 Input: root = [1,2,3,null,4], x = 2, y = 3
 Output: false


 Note:

 The number of nodes in the tree will be between 2 and 100.
 Each node has a unique integer value from 1 to 100.
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void isCousin(TreeNode* root, int depth, int x, int y, int& dx, int& dy, bool& cousin) {
        if (root == nullptr) {
            return;
        }

        if (root -> val == x) {
            dx = depth;
        }
        if (root -> val == y) {
            dy = depth;
        }

        if (root -> left != nullptr and root -> right != nullptr) {
            if ((root -> left -> val == x and root -> right -> val == y) or (root -> left -> val == y and root -> right -> val == x)) {
                cousin = false;
            }
        }
        isCousin(root -> left, depth + 1, x, y, dx, dy, cousin);
        isCousin(root -> right, depth + 1, x, y, dx, dy, cousin);
    }
public:
    bool isCousins(TreeNode* root, int x, int y) {
        int dx = 0;
        int dy = 0;
        bool cousin = true;
        isCousin(root, 0, x, y, dx, dy, cousin);
        return cousin and dx == dy;
    }
};
