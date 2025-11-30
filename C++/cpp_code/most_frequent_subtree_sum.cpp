/*
508. Most Frequent Subtree Sum
https://leetcode.com/problems/most-frequent-subtree-sum/

Given the root of a tree,
you are asked to find the most frequent subtree sum.
The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node
(including the node itself).
So what is the most frequent subtree sum value?
If there is a tie, return all the values with the highest frequency in any order.

Examples 1
Input:
  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.

Examples 2
Input:
  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.

Note:
You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
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

class Solution {
private:
    unordered_map<int, int> frequency;
    int mostFrequent = -1;

    int getSum(TreeNode* root, vector<int>& result) {
        if (root == nullptr) {
            return 0;
        }

        int sum = root->val + getSum(root->left, result) + getSum(root->right, result);
        frequency[sum] += 1;
        if (mostFrequent == -1 or mostFrequent < frequency[sum]) {
            result.clear();
            result.push_back(sum);
            mostFrequent = frequency[sum];
        } else if (mostFrequent == frequency[sum]) {
            result.push_back(sum);
        }
        return sum;
    }

public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> result;
        getSum(root, result);
        return result;
    }
};