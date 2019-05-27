/*
 Given a binary tree, determine if it is a complete binary tree.

 Definition of a complete binary tree from Wikipedia:
 In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.



 Example 1:



 Input: [1,2,3,4,5,6]
 Output: true
 Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
 Example 2:



 Input: [1,2,3,4,5,null,7]
 Output: false
 Explanation: The node with value 7 isn't as far left as possible.

 Note:

 The tree will have between 1 and 100 nodes.
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
#include <numeric>
using namespace std;

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        int level = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            bool lastLevel = false;
            if (curSize != pow(2, level)) {
                lastLevel = true;
            }

            if (lastLevel) {
                while (!bfs.empty()) {
                    TreeNode* node = bfs.front();
                    bfs.pop();
                    if (node -> left != nullptr or node -> right != nullptr) {
                        return false;
                    }
                }
                return true;
            }

            bool completed = true;
            for (int i = 0; i < curSize; i++) {
                TreeNode* node = bfs.front();
                bfs.pop();
                
                if (node -> left) {
                    if (!completed) {
                        return false;
                    }
                    bfs.push(node -> left);
                    if (node -> right) {
                        bfs.push(node -> right);
                    }
                    else {
                        completed = false;
                    }
                }
                else {
                    if (node -> right) {
                        return false;
                    }
                    else {
                        completed = false;
                    }
                }
            }
            level += 1;
        }
        return true;
    }
};
