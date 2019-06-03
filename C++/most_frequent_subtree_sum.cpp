/*
508. Most Frequent Subtree Sum

Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

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
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
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
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
private:
    unordered_map<int, int> frequency;
    int mostFrequent = 0;

    int getSum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int sum = root -> val + getSum(root -> left) + getSum(root -> right);
        frequency[sum] += 1;
        mostFrequent = max(mostFrequent, frequency[sum]);
        return sum;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> result;
        getSum(root);
        for (auto iter : frequency) {
            if (iter.second == mostFrequent) {
                result.push_back(iter.first);
            }
        }
        return result;
    }
};
