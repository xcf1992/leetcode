/*
https://leetcode.com/problems/count-nodes-equal-to-sum-of-descendants/description/
1973. Count Nodes Equal to Sum of Descendants

Given the root of a binary tree, return the number of nodes where the value of the node is equal to the sum of the
values of its descendants.

A descendant of a node x is any node that is on the path from node x to some leaf node. The sum is considered to be 0 if
the node has no descendants.



Example 1:


Input: root = [10,3,4,2,1]
Output: 2
Explanation:
For the node with value 10: The sum of its descendants is 3+4+2+1 = 10.
For the node with value 3: The sum of its descendants is 2+1 = 3.
Example 2:


Input: root = [2,3,null,2,null]
Output: 0
Explanation:
No node has a value that is equal to the sum of its descendants.
Example 3:


Input: root = [0]
Output: 1
For the node with value 0: The sum of its descendants is 0 since it has no descendants.


Constraints:

The number of nodes in the tree is in the range [1, 105].
0 <= Node.val <= 105
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
    long long get_descendant_sum(TreeNode* root, int& rst) {
        if (root == nullptr) {
            return 0;
        }

        long long desc_sum = 0;
        desc_sum += get_descendant_sum(root->left, rst);
        desc_sum += get_descendant_sum(root->right, rst);
        if (root->val == desc_sum) {
            rst += 1;
        }
        desc_sum += root->val;
        return desc_sum;
    }
public:
    int equalToDescendants(TreeNode* root) {
        int rst = 0;
        get_descendant_sum(root, rst);
        return rst;
    }
};