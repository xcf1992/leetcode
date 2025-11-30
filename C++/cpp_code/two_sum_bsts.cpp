/*
1214. Two Sum BSTs
https://leetcode.com/problems/two-sum-bsts/

Given two binary search trees,
return True if and only if there is a node in the first tree and a node in the second tree
whose values sum up to a given integer target.

Example 1:
        2                               1
    1       4                       0       3
Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
Output: true
Explanation: 2 and 3 sum up to 5.

Example 2:
        0                                   5
-10           10                   1                7
                                0     2
Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
Output: false

Constraints:
Each tree has at most 5000 nodes.
-10^9 <= target, node.val <= 10^9
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
#include "extra_data_types.hpp"
using namespace std;
/*
basically, we trying to find every possible target - root2 -> val
in root1 tree.
Time O(n2 * log(n1))
*/
class Solution {
private:
    bool binarySearch(TreeNode* root, int target) {
        if (root == nullptr) {
            return false;
        }
        if (root->val == target) {
            return true;
        }
        return root->val > target ? binarySearch(root->left, target) : binarySearch(root->right, target);
    }

public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        if (root1 == nullptr or root2 == nullptr) {
            return false;
        }

        if (binarySearch(root1, target - root2->val)) {
            return true;
        }

        return twoSumBSTs(root1, root2->left, target) or twoSumBSTs(root1, root2->right, target);
    }
};

class Solution1 {
    // 25%
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        if (root1 == nullptr or root2 == nullptr) {
            return false;
        }

        int sum = root1->val + root2->val;
        if (sum == target) {
            return true;
        }

        if (sum > target) {
            return twoSumBSTs(root1->left, root2, target) or twoSumBSTs(root1, root2->left, target);
        }
        return twoSumBSTs(root1->right, root2, target) or twoSumBSTs(root1, root2->right, target);
    }
};