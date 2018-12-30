/*
 Given a binary tree, we install cameras on the nodes of the tree.
 
 Each camera at a node can monitor its parent, itself, and its immediate children.
 
 Calculate the minimum number of cameras needed to monitor all nodes of the tree.
 
 
 
 Example 1:
 
 
 Input: [0,0,null,0,0]
 Output: 1
 Explanation: One camera is enough to monitor all nodes if placed as shown.
 Example 2:
 
 
 Input: [0,0,null,0,null,0,null,null,0]
 Output: 2
 Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
 
 Note:
 
 The number of nodes in the given tree will be in the range [1, 1000].
 Every node has value 0.
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
private:
    int count(TreeNode* root, bool monitored) {
        if (root == nullptr) {
            return 0;
        }
        
        if (root -> left == nullptr and root -> right == nullptr) {
            return monitored ? 0 : 1;
        }
        
        if (root -> left != nullptr and root -> right != nullptr) {
            return 1 + count(root -> left, true) + count(root -> right, true);
        }
        
        TreeNode* child = root -> left == nullptr ? root -> right : root -> left;
        return min(1 + count(child, true), count(child, false));
    }
public:
    int minCameraCover(TreeNode* root) {
        
    }
};
