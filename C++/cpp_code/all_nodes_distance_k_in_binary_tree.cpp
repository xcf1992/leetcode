/*
863. All Nodes Distance K in Binary Tree
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

We are given a binary tree (with root node root),
a target node, and an integer value K.

Return a list of the values of all nodes that have a distance K from the target node.
The answer can be returned in any order.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
       3
    /     \
   5       1
  / \     / \
 6   2   0   8
    / \
   7   4
Output: [7,4,1]
Explanation:
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.

Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.

Note:
The given tree is non-empty.
Each node in the tree has unique values 0 <= node.val <= 500.
The target node is a node in the tree.
0 <= K <= 1000.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (root == nullptr or target == nullptr) {
            return {};
        }

        unordered_map<TreeNode*, vector<TreeNode*>> graph;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();

            if (cur -> left != nullptr) {
                graph[cur].push_back(cur -> left);
                graph[cur -> left].push_back(cur);
                q.push(cur -> left);
            }
            if (cur -> right != nullptr) {
                graph[cur].push_back(cur -> right);
                graph[cur -> right].push_back(cur);
                q.push(cur -> right);
            }
        }

        unordered_set<TreeNode*> visited;
        visited.insert(target);
        q.push(target);
        int distance = 0;
        vector<int> result;
        while (!q.empty()) {
            int curSize = q.size();
            for (int i = 0; i < curSize; i++) {
                TreeNode* cur = q.front();
                q.pop();

                if (distance == K) {
                    result.push_back(cur -> val);
                    continue;
                }

                for (TreeNode* next : graph[cur]) if (visited.find(next) == visited.end()) {
                    visited.insert(cur);
                    q.push(next);
                }
            }
            distance += 1;
        }
        return result;
    }
};
