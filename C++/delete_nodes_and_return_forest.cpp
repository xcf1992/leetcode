/*
1110. Delete Nodes And Return Forest
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the result in any order.



Example 1:
                        1
            2                   3
        4       5           6       7

Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]


Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.
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
#include <set>
#include <numeric>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    TreeNode* deleteNodes(TreeNode* root, bool isRoot, unordered_set<int>& to_delete, vector<TreeNode*>& result) {
        if (root == nullptr) {
            return root;
        }

        bool deleted = to_delete.find(root -> val) != to_delete.end();
        if (isRoot and !deleted) {
            result.push_back(root);
        }

        root -> left = deleteNodes(root -> left, deleted, to_delete, result);
        root -> right = deleteNodes(root -> right, deleted, to_delete, result);
        return deleted ? nullptr : root;
    }

public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> deleted(to_delete.begin(), to_delete.end());
        vector<TreeNode*> result;
        deleteNodes(root, true, deleted, result);
        return result;
    }
};
