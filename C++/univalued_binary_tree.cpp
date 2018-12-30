/*
 A binary tree is univalued if every node in the tree has the same value.
 
 Return true if and only if the given tree is univalued.
 
 
 
 Example 1:
 
 
 Input: [1,1,1,1,1,null,1]
 Output: true
 Example 2:
 
 
 Input: [2,2,2,5,2]
 Output: false
 
 
 Note:
 
 The number of nodes in the given tree will be in the range [1, 100].
 Each node's value will be an integer in the range [0, 99].
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
    bool univalued(TreeNode* root, int value) {
        if (root == nullptr) {
            return true;
        }
        
        if (root -> val != value) {
            return false;
        }
        
        return univalued(root -> left, value) and univalued(root -> right, value);
    }
public:
    bool isUnivalTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        
        if (root -> left == nullptr and root -> right == nullptr) {
            return true;
        }
        
        int value = root -> val;
        return univalued(root, value);
    }
};
