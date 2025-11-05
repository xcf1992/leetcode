/*
1707. Maximum XOR With an Element From Array
https://leetcode.com/problems/maximum-xor-with-an-element-from-array/

You are given an array nums consisting of non-negative integers.
You are also given a queries array, where queries[i] = [xi, mi].

The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums
that does not exceed mi.
In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi.
If all elements in nums are larger than mi, then the answer is -1.

Return an integer array answer where answer.length == queries.length
and answer[i] is the answer to the ith query.

Example 1:
Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
Output: [3,3,7]
Explanation:
1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
2) 1 XOR 2 = 3.
3) 5 XOR 2 = 7.
Example 2:
Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
Output: [15,-1,5]

Constraints:
1 <= nums.length, queries.length <= 105
queries[i].length == 2
0 <= nums[j], xi, mi <= 109
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
Idea

The idea behind this problem comes from LC 421 and LC 1697.

Similar to LC 421, we can convert each number to binary format
and construct a trie that has children of 0 and 1. In this way,
we can query the maximum bitwise XOR value in O(32) time.

Similar to LC 1697, we can sort queries and construct the trie on the fly.
We use a two pointer approach to make sure only elements that do not exceed m_i are added to the trie.

Putting these thoughts together, we arrive at the solution below. Please refer to the code for more details.
*/


class Solution {
private:
    class TreeNode {
    public:
        TreeNode *next[2];

        TreeNode() {
            next[0] = nullptr;
            next[1] = nullptr;
        };
    };

    TreeNode *buildTree(vector<int> &nums) {
        TreeNode *root = new TreeNode(), *cur;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            cur = root;
            for (int j = 31; j >= 0; j--) {
                int index = ((num >> j) & 1);
                if (cur->next[index] == nullptr) {
                    cur->next[index] = new TreeNode();
                }
                cur = cur->next[index];
            }
        }
        return root;
    }

    int dfs(TreeNode *root, int x, int limit, int value, int height) {
        if (value > limit) {
            return -1;
        }

        if (height == -1) {
            return x ^ value;
        }

        int bit_x = (x >> height) & 1;
        if (root->next[1 - bit_x] != nullptr) {
            int v = dfs(root->next[1 - bit_x], x, limit, (value | ((1 - bit_x) << height)), height - 1);
            if (v >= 0) {
                return v;
            }
        }

        if (root->next[bit_x] != nullptr) {
            int v = dfs(root->next[bit_x], x, limit, (value | (bit_x << height)), height - 1);
            if (v >= 0)
                return v;
        }
        return -1;
    }

public:
    vector<int> maximizeXor(vector<int> &nums, vector<vector<int> > &queries) {
        vector<int> ans;
        TreeNode *root = buildTree(nums);
        for (const vector<int> &query: queries) {
            int tmp = dfs(root, query[0], query[1], 0, 31);
            ans.push_back(tmp);
        }
        return ans;
    }
};