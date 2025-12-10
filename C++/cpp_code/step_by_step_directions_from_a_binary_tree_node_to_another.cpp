/*
https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another
2096. Step-By-Step Directions From a Binary Tree Node to Another
Medium
Topics
conpanies icon
Companies
Hint
You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also
given an integer startValue representing the value of the start node s, and a different integer destValue representing
the value of the destination node t.

Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a
string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:

'L' means to go from a node to its left child node.
'R' means to go from a node to its right child node.
'U' means to go from a node to its parent node.
Return the step-by-step directions of the shortest path from node s to node t.



Example 1:


Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
Output: "UURL"
Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
Example 2:


Input: root = [2,1], startValue = 2, destValue = 1
Output: "L"
Explanation: The shortest path is: 2 → 1.


Constraints:

The number of nodes in the tree is n.
2 <= n <= 105
1 <= Node.val <= n
All the values in the tree are unique.
1 <= startValue, destValue <= n
startValue != destValue
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
private:
    TreeNode* lowest_common_ancestor(TreeNode* root, int startValue, int destValue) {
        if (root == nullptr || root->val == startValue || root->val == destValue) {
            return root;
        }

        TreeNode* lca_left = lowest_common_ancestor(root->left, startValue, destValue);
        TreeNode* lca_right = lowest_common_ancestor(root->right, startValue, destValue);
        if (lca_left != nullptr && lca_right != nullptr) {
            return root;
        }
        return lca_left != nullptr ? lca_left : lca_right;
    }

    bool find_path(TreeNode* root, int val, string& path) {
        if (root == nullptr) {
            return false;
        }

        if (root->val == val) {
            return true;
        }

        path.push_back('L');
        if (find_path(root->left, val, path)) {
            return true;
        }

        path.pop_back();
        path.push_back('R');
        if (find_path(root->right, val, path)) {
            return true;
        }

        path.pop_back();
        return false;
    }

public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        TreeNode* lca_root = lowest_common_ancestor(root, startValue, destValue);
        string start_path = "";
        find_path(lca_root, startValue, start_path);

        string dest_path = "";
        find_path(lca_root, destValue, dest_path);

        string rst(start_path.size(), 'U');
        return rst + dest_path;
    }
};
