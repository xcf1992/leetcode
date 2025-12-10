/*
1530. Number of Good Leaf Nodes Pairs
https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/

Given the root of a binary tree and an integer distance.
A pair of two different leaf nodes of a binary tree is said to be good
if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree.

Example 1:
Input: root = [1,2,3,null,4], distance = 3
Output: 1
Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the
only good pair.

Example 2:
Input: root = [1,2,3,4,5,6,7], distance = 3
Output: 2
Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2. The pair [4,6] is not good because the length of
ther shortest path between them is 4.

Example 3:
Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
Output: 1
Explanation: The only good pair is [2,5].

Example 4:
Input: root = [100], distance = 1
Output: 0

Example 5:
Input: root = [1,1,1], distance = 2
Output: 1

Constraints:
The number of nodes in the tree is in the range [1, 2^10].
Each node's value is between [1, 100].
1 <= distance <= 10
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    vector<int> dfs(int d, TreeNode* root, int& result) {
        if (root == nullptr) {
            return {0};
        }

        if (root->left == nullptr and root->right == nullptr) {
            return {1};  // this a leaf node with distance 1
        }

        vector<int> l = dfs(d, root->left, result);   // list from left
        vector<int> r = dfs(d, root->right, result);  // list from right
        for (auto a : l) {
            for (auto b : r) {
                if ((a and b) and a + b <= d) {
                    result += 1;  // add all valid pairs
                }
            }
        }

        vector<int> ret;  // this is a list of all nodes which the current node will pass to its parent
        for (auto a : l) {
            if (a and a + 1 < d) {
                ret.push_back(a + 1);
            }
        }
        for (auto b : r) {
            if (b and b + 1 < d) {
                ret.push_back(b + 1);
            }
        }
        return ret;
    }

public:
    int countPairs(TreeNode* root, int d) {
        int result = 0;
        dfs(d, root, result);
        return result;
    }
};