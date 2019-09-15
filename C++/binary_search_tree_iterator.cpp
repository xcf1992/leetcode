/*
173. Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST).
Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Example:
                7
        3           15
                9       20
BSTIterator iterator = new BSTIterator(root);
iterator.next();    // return 3
iterator.next();    // return 7
iterator.hasNext(); // return true
iterator.next();    // return 9
iterator.hasNext(); // return true
iterator.next();    // return 15
iterator.hasNext(); // return true
iterator.next();    // return 20
iterator.hasNext(); // return false


Note:

next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class BSTIterator {
private:
    stack<TreeNode*> stk;
public:
    BSTIterator(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        TreeNode* cur = root;
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur -> left;
        }
    }

    /* @return whether we have a next smallest number*/
    bool hasNext() {
        return !stk.empty();
    }

    /* @return the next smallest number*/
    int next() {
        TreeNode* cur = stk.top();
        stk.pop();
        int result = cur -> val;
        if (cur -> right != nullptr) {
            cur = cur -> right;
            while (cur != nullptr) {
                stk.push(cur);
                cur = cur -> left;
            }
        }
        return result;
    }
};
/*
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
*/
