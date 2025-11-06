/*
968. Binary Tree Cameras

Given a binary tree, we install cameras on the nodes of the tree.
Each camera at a node can monitor its parent, itself, and its immediate children.
Calculate the minimum number of cameras needed to monitor all nodes of the tree.

Example 1:
Input: [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.

Example 2:
Input: [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree.
The above image shows one of the valid configurations of camera placement.

Note:
The number of nodes in the given tree will be in the range [1, 1000].
Every node has value 0.
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
Greedy
Intuition:
Consider a node in the tree.
It can be covered by its parent, itself, its two children.
Four options.

Consider the root of the tree.
It can be covered by left child, or right child, or itself.
Three options.

Consider one leaf of the tree.
It can be covered by its parent or by itself.
Two options.

If we set a camera at the leaf, the camera can cover the leaf and its parent.
If we set a camera at its parent, the camera can cover the leaf, its parent and its cousin.

We can see that the second plan is always better than the first.
Now we have only one option, set up camera to all leaves' parent.

Here is our greedy solution:

Set cameras on all leaves' parents, then remove all covered nodes.
Repeat step 1 until all nodes are covered.

Apply a recusion function dfs.
Return 0 if it's a leaf or a parent whose children are all node 2.
Return 1 if it's a parent of a leaf, with a camera on this node.
Return 2 if it's coverd, without a camera on this node.

For each node,
if it has a child, which is leaf (node 0), then it needs camera.
if it has a child, which is the parent of a leaf (node 1), then it's covered.
If it needs camera, then res++ and we return 1.
If it's covered, we return 2.
Otherwise, we return 0.
*/
class Solution {
private:
    int identify(TreeNode* root, int& result) {
        if (root == nullptr) {
            return 2;
        }
        if (root->left == nullptr and root->right == nullptr) {
            return 0;
        }

        int lc = identify(root->left, result);
        int rc = identify(root->right, result);
        if (lc == 0 or rc == 0) {
            result += 1;
            return 1;
        }
        return lc == 1 or rc == 1 ? 2 : 0;
    }

public:
    int minCameraCover(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int result = 0;
        int kind = identify(root, result);
        return kind == 0 ? result + 1 : result;
    }
};

// we can also solve this problem using DP, simillar to house robber III
struct ResultType {
    int subNodesCovered;  // all nodes below its level are covered (not including itself)
    int coveredNoCamera;  // the node itself is covered by its children
    int coveredCamera;    // the node is covered by itself
    ResultType(int subNodesCovered, int coveredNoCamera, int coveredCamera) {
        this->subNodesCovered = subNodesCovered;
        this->coveredNoCamera = coveredNoCamera;
        this->coveredCamera = coveredCamera;
    }
};

class Solution1 {
private:
    ResultType check(TreeNode* root) {
        if (root == nullptr) {
            return ResultType(0, 0, INT_MAX);
        }

        ResultType leftResult = check(root->left);
        int leftMin = min(leftResult.coveredCamera, leftResult.coveredNoCamera);
        ResultType rightResult = check(root->right);
        int rightMin = min(rightResult.coveredCamera, rightResult.coveredNoCamera);

        int subNodesCovered = leftResult.coveredNoCamera + rightResult.coveredNoCamera;
        int coveredNoCam = min(leftResult.coveredCamera + rightMin, rightResult.coveredCamera + leftMin);
        int coveredCam = 1 + min(leftMin, leftResult.subNodesCovered) + min(rightMin, rightResult.subNodesCovered);
        return ResultType(subNodesCovered, coveredNoCam, coveredCam);
    }

public:
    int minCameraCover(TreeNode* root) {
        ResultType result = check(root);
        return min(result.coveredCamera, result.coveredNoCamera);
    }
};