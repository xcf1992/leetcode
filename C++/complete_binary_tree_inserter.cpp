/*
 A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.
 
 Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:
 
 CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;
 CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v so that the tree remains complete, and returns the value of the parent of the inserted TreeNode;
 CBTInserter.get_root() will return the head node of the tree.
 
 
 Example 1:
 
 Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
 Output: [null,1,[1,2]]
 Example 2:
 
 Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
 Output: [null,3,4,[1,2,3,4,5,6,7,8]]
 
 
 Note:
 
 The initial given tree is complete and contains between 1 and 1000 nodes.
 CBTInserter.insert is called at most 10000 times per test case.
 Every value of a given or inserted node is between 0 and 5000.
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

class CBTInserter {
private:
    int treeSize;
    TreeNode* _root;
    
    int getTreeSize(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        return 1 + getTreeSize(root -> left) + getTreeSize(root -> right);
    }
public:
    CBTInserter(TreeNode* root) {
        _root = root;
        treeSize = getTreeSize(root);
    }
    
    int insert(int v) {
        treeSize += 1;
        int temp = treeSize;
        stack<int> stk;
        while (temp != 1) {
            if (temp % 2 == 0) {
                stk.push(0);
            }
            else {
                stk.push(1);
            }
            temp /= 2;
        }
        
        TreeNode* parent = _root;
        while (stk.size() != 1) {
            if (stk.top() == 0) {
                parent = parent -> left;
            }
            else {
                parent = parent -> right;
            }
            stk.pop();
        }
        if (stk.top() == 0) {
            parent -> left = new TreeNode(v);
        }
        else {
            parent -> right = new TreeNode(v);
        }
        return parent -> val;
    }
    
    TreeNode* get_root() {
        return _root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter obj = new CBTInserter(root);
 * int param_1 = obj.insert(v);
 * TreeNode* param_2 = obj.get_root();
 */
