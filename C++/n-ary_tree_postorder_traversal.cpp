/*
 Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

 For example, given a 3-ary tree:
        1
    /   |  \
   3    2   4
  / \
 5   6

 Return its postorder traversal as: [5,6,3,2,4,1].
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
    vector<int> postorder(Node* root) {
        stack<Node*> stk;
        stk.push(root);
        vector<int> result;
        while (!stk.empty() && root != nullptr) {
            Node* cur = stk.top();
            stk.pop();
            result.push_back(cur -> val);
            for (Node* child : cur -> children) {
                stk.push(child);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

class Solution1 {
private:
    void traversal(Node* root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }

        for (Node* child : root -> children) {
            traversal(child, result);
        }
        result.push_back(root -> val);
        return;
    }
public:
    vector<int> postorder(Node* root) {
        vector<int> result;
        return result;
    }
};
