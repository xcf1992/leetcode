/*
https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/
2385. Amount of Time for Binary Tree to Be Infected

You are given the root of a binary tree with unique values, and an integer start.
At minute 0, an infection starts from the node with value start.

Each minute, a node becomes infected if:

The node is currently uninfected.
The node is adjacent to an infected node.
Return the number of minutes needed for the entire tree to be infected.



Example 1:


Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
Explanation: The following nodes are infected during:
- Minute 0: Node 3
- Minute 1: Nodes 1, 10 and 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2
It takes 4 minutes for the whole tree to be infected so we return 4.
Example 2:


Input: root = [1], start = 1
Output: 0
Explanation: At minute 0, the only node in the tree is infected so we return 0.


Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 105
Each node has a unique value.
A node with a value of start exists in the tree.
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
#include "extra_data_types.hpp"
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

class Solution {
private:
    void traverse(TreeNode* root, unordered_map<int, vector<int>>& connected) {
        if (root == nullptr) {
            return;
        }

        if (root->left != nullptr) {
            connected[root->val].push_back(root->left->val);
            connected[root->left->val].push_back(root->val);
        }
        traverse(root->left, connected);

        if (root->right != nullptr) {
            connected[root->val].push_back(root->right->val);
            connected[root->right->val].push_back(root->val);
        }
        traverse(root->right, connected);
    }
public:
    int amountOfTime(TreeNode* root, int start) {
        unordered_map<int, vector<int>> connected;
        traverse(root, connected);

        unordered_set<int> visited;
        queue<int> bfs;
        int result = 0;
        bfs.push(start);
        visited.insert(start);
        while (!bfs.empty()) {
            int cnt = bfs.size();
            for (int i = 0; i < cnt; i++) {
                int cur = bfs.front();
                bfs.pop();

                for (int nxt : connected[cur]) {
                    if (visited.find(nxt) != visited.end()) {
                        continue;
                    }

                    visited.insert(nxt);
                    bfs.push(nxt);
                }
            }
            if (!bfs.empty()) {
                result += 1;
            }
        }
        return result;
    }
};