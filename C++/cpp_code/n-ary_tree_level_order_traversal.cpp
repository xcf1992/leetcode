/*
 Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

 For example, given a 3-ary tree:
       1
   /   |  \
  3    2   4
 / \
 5   6
 We should return its level order traversal:

 [
 [1],
 [3,2,4],
 [5,6]
 ]
 Note:

 The depth of the tree is at most 1000.
 The total number of nodes is at most 5000.
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
    vector<Node *> children;

    Node() {
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<vector<int> > levelOrder(Node *root) {
        vector<vector<int> > result;
        if (root == nullptr) {
            return result;
        }

        queue<Node *> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            vector<int> level;

            int length = bfs.size();
            for (int i = 0; i < length; i++) {
                Node *cur = bfs.front();
                bfs.pop();
                level.push_back(cur->val);
                for (Node *child: cur->children) {
                    if (child != nullptr) {
                        bfs.push(child);
                    }
                }
            }

            result.push_back(level);
        }
        return result;
    }
};