/*
https://leetcode.com/problems/cousins-in-binary-tree-ii/description/
2641. Cousins in Binary Tree II

Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.

Two nodes of a binary tree are cousins if they have the same depth with different parents.

Return the root of the modified tree.

Note that the depth of a node is the number of edges in the path from the root node to it.



Example 1:


Input: root = [5,4,9,1,10,null,7]
Output: [0,0,0,7,7,null,11]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 5 does not have any cousins so its sum is 0.
- Node with value 4 does not have any cousins so its sum is 0.
- Node with value 9 does not have any cousins so its sum is 0.
- Node with value 1 has a cousin with value 7 so its sum is 7.
- Node with value 10 has a cousin with value 7 so its sum is 7.
- Node with value 7 has cousins with values 1 and 10 so its sum is 11.
Example 2:


Input: root = [3,1,2]
Output: [0,0,0]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 3 does not have any cousins so its sum is 0.
- Node with value 1 does not have any cousins so its sum is 0.
- Node with value 2 does not have any cousins so its sum is 0.


Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 104
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
#include <climits>
#include <set>
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
    TreeNode* replaceValueInTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            unordered_map<TreeNode*, int> child_sum;
            int total_sum = 0;
            for (int i = 0; i < cur_size; ++i) {
                TreeNode* cur = bfs.front();
                bfs.pop();

                int sum = 0;
                if (cur->left != nullptr) {
                    sum += cur->left->val;
                    bfs.push(cur->left);
                }

                if (cur->right != nullptr) {
                    sum += cur->right->val;
                    bfs.push(cur->right);
                }

                if (sum != 0) {
                    child_sum[cur] = sum;
                }
                total_sum += sum;
            }

            int cnt = child_sum.size();
            for (auto& [parent, sum] : child_sum) {
                if (cnt <= 1) {
                    if (parent->left != nullptr) {
                        parent->left->val = 0;
                    }
                    if (parent->right != nullptr) {
                        parent->right->val = 0;
                    }
                } else {
                    if (parent->left != nullptr) {
                        parent->left->val = total_sum - sum;
                    }
                    if (parent->right != nullptr) {
                        parent->right->val = total_sum - sum;
                    }
                }
            }
        }

        root->val = 0;
        return root;
    }
};