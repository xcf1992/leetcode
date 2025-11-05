/*
 Given a n-ary tree, find its maximum depth.

 The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

 For example, given a 3-ary tree:

           1
       /   |  \
      3    2   4
     / \
    5   6

 We should return its max depth, which is 3.

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
    int val;
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
    int maxDepth(Node *root) {
        if (root == nullptr) {
            return 0;
        }

        int depth = 1;
        for (Node *child: root->children) {
            depth = max(depth, maxDepth(child) + 1);
        }
        return depth;
    }
};

class Solution1 {
private:
    int getDepth(Node *root, int depth) {
        if (root == nullptr) {
            return depth;
        }

        int newDepth = 0;
        for (Node *child: root->children) {
            newDepth = max(newDepth, getDepth(child, depth));
        }
        return newDepth + 1;
    }

public:
    int maxDepth(Node *root) {
        return getDepth(root, 1);
    }
};