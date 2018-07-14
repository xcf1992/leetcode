/*
 Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
 
 For example, given a 3-ary tree:
     1
  /   |  \
  3    2   4
 / \
 5   6
 
 Return its preorder traversal as: [1,3,5,6,2,4].
 Note: Recursive solution is trivial, could you do it iteratively?
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;
    
    Node() {}
    
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<Node*> stk;
        stk.push(root);
        while (!stk.empty()) {
            Node* cur = stk.top();
            stk.pop();
            result.push_back(cur -> val);
            for (int i = cur -> children.size() - 1; i >= 0; i--) {
                if (cur -> children[i] != nullptr) {
                    stk.push(cur -> children[i]);
                }
            }
        }
        return result;
    }
};

class Solution1 {
private:
    void travel(Node* root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        
        result.push_back(root -> val);
        for (Node* child : root -> children) {
            travel(child, result);
        }
    }
public:
    vector<int> preorder(Node* root) {
        vector<int> result;
        travel(root, result);
        return result;
    }
};
