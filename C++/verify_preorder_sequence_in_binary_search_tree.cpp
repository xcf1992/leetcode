/*
255. Verify Preorder Sequence in Binary Search Tree
https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/

Given an array of numbers,
verify whether it is the correct preorder traversal sequence of a binary search tree.
You may assume each number in the sequence is unique.
Consider the following binary search tree:

     5
    / \
   2   6
  / \
 1   3
Example 1:
Input: [5,2,6,1,3]
Output: false

Example 2:
Input: [5,2,1,3,6]
Output: true

Follow up:
Could you do it using only constant space complexity?
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
using namespace std;
/*
To translate this into code:
looking for the trend of numbers, if it’s decreasing, it’s still traversing the left child node all the way down,
we push the value into stack. When we read a value greater than the last one,
we know the current value belongs to a right node (let it be rc: right child) of one of the previous nodes (let it be p)
we pushed to stack, in other words, p is a parent node of the current node rc. Due to the property of preorder traversal,
p’s value is pushed to stack before its left subtree nodes, so to find the parent node, we pop all the nodes in its left subtree,
and the last popped node whose value is smaller than rc is rc’s parent p, whose value becomes the lower bound.

Then we keep reading the serialized array, in any case we see any value not greater than the lower bound,
we return false. Lower bound is updated whenever we read a right child node’s value.
*/
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> stk;
        int lower_bound = INT_MIN;
        for (int i = 0; i < preorder.size(); i++) {
            if (stk.empty() or preorder[i] < preorder[i - 1]) {
                if (preorder[i] <= lower_bound) {
                    return false;
                }
            }
            else {
                while (!stk.empty() and stk.top() < preorder[i]) {
                    lower_bound = stk.top();
                    stk.pop();
                }
            }
            stk.push(preorder[i]);
        }
        return true;
    }
};

class Solution1 {
private:
    bool verify(vector<int>& preorder, int start, int end, int minVal, int maxVal) {
        if (start >= end) {
            return true;
        }

        if (preorder[start] <= minVal or preorder[start] >= maxVal) {
            return false;
        }

        int newEnd = start + 1;
        while (newEnd < preorder.size() and preorder[newEnd] <= preorder[start]) {
            newEnd += 1;
        }
        return verify(preorder, start + 1, newEnd, minVal, preorder[start]) and
                verify(preorder, newEnd, end, preorder[start], maxVal);
    }
public:
    bool verifyPreorder(vector<int>& preorder) {
        int n = preorder.size();
        if (n <= 1) {
            return true;
        }
        return verify(preorder, 0, n, INT_MIN, INT_MAX);
    }
};
