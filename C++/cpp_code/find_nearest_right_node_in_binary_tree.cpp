/*
https://leetcode.com/problems/find-nearest-right-node-in-binary-tree/description/
1602. Find Nearest Right Node in Binary Tree

Given the root of a binary tree and a node u in the tree, return the nearest node on the same level that is to the right
of u, or return null if u is the rightmost node in its level.



Example 1:


Input: root = [1,2,3,null,4,5,6], u = 4
Output: 5
Explanation: The nearest node on the same level to the right of node 4 is node 5.
Example 2:


Input: root = [3,null,4,2], u = 2
Output: null
Explanation: There are no nodes to the right of 2.


Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 105
All values in the tree are distinct.
u is a node in the binary tree rooted at root.
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
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        if (root == nullptr) {
            return nullptr;
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; ++i) {
                TreeNode* cur = bfs.front();
                bfs.pop();

                if (cur == u) {
                    if (i == cur_size - 1) {
                        return nullptr;
                    }
                    return bfs.front();
                }

                if (cur -> left != nullptr) {
                    bfs.push(cur -> left);
                }
                if (cur -> right != nullptr) {
                    bfs.push(cur -> right);
                }
            }
        }
        return nullptr;
    }
};