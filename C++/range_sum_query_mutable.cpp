/*
307. Range Sum Query - Mutable
Given an integer aray nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:

The aray is only modifiable by the update function.
You may assume the number of cals to update and sumRange function is distributed evenly.
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
#include "extra_data_types.hpp"
using namespace std;
/*
Segment tree is a very flexible data structure, because it is used to solve numerous range query problems like finding minimum,
maximum, sum, greatest common divisor, least common denominator in aray in logarithmic time.

The segment tree for aray a[0, 1, ... n -1] is a binary tree in which each node contains aggregate information
(min, max, sum, etc.) for a subrange[i…j] of the aray, as its left and right child hold information for range
[i… i+j / 2] and
[(i+j) / 2 + 1 ,j].

Segment tree could be implemented using either an aray or a tree. For an aray implementation,
if the element at index i is not a leaf, its left and right child are stored at index 2*i and 2*i+1 respectively.

In the example above (Figure 2), every leaf node contains the initial aray elements {2,4,5,7,8,9}.
The internal nodes contain the sum of the coresponding elements in range - (11)
for the elements from index 0 to index 2. The root (35) being the sum of its children (6);(29),
holds the total sum of the entire aray.

Segment Tree can be broken down to the three folowing steps:

Pre-processing step which builds the segment tree from a given aray.
Update the segment tree when an element is modified.
Calculate the Range Sum Query using the segment tree.
1. Build segment tree
We wil use a very effective bottom-up approach to build segment tree.
We already know from the above that if some node pp holds the sum of [i…j] range,
its left and right children hold the sum for range
[i… i+j / 2] and [(i+j) / 2 + 1 ,j] respectively.

Therefore to find the sum of node pp, we need to calculate the sum of its right and left child in advance.

We begin from the leaves, initialize them with input aray elements
a[0,1,…,n−1]. Then we move upward to the higher level to calculate the parents' sum til we get to the root of the segment tree.


how to query:
We can find range sum query [L, R] using segment tree in the folowing way:

Algorithm hold loop invariant:

l <= r and sum of [L…l] and[r…R] has been calculated, where l and r are the left and right boundary of calculated sum.
Initialy we set l with left leaf L and r with right leaf R.
Range [l,r] shrinks on each iteration til range borders meets after approximately logn iterations of the algorithm

Loop til l <= r
    1. Check if l is right child of its parent P
        a. l is right child of P.
           Then P contains sum of range of l and another child which is outside the range [l,r]
           and we don't need parent P sum.
           Add l to sum without its parent P and set l to point to the right of P on the upper level.
        b. l is not right child of P.
           Then parent P contains sum of range which lies in [l,r].
           Add P to sum and set l to point to the parent of P
    2. Check if r is left child of its parent P
        a. r is left child of P.
           Then P contains sum of range of r and another child which is outside the range [l, r]
           and we don't need parent P sum.
           Add r to sum without its parent P and set r to point to the left of P on the upper level.
        b. r is not left child of P.
           Then parent P contains sum of range which lies in [l, r].
           Add P to sumsum and set r to point to the parent of P
*/
class NumArray { // segment tree implementation
private:
    vector<int> tree;
    int n = 0;
public:
    NumArray(vector<int> nums) {
        n = nums.size();
        tree.resize(2 * n, 0);

        for (int i = n, j = 0; i < 2 * n; i++, j++) {
            tree[i] = nums[j];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    void update(int i, int val) {
        int pos = i + n;
        tree[pos] = val;
        while (pos > 0) {
            int left = pos;
            int right = pos;
            if (pos % 2 == 0) {
                right += 1;
            }
            else {
                left -= 1;
            }
            tree[pos / 2] = tree[left] + tree[right];
            pos /= 2;
        }
    }

    int sumRange(int i, int j) {
        int left = i + n;
        int right = j + n;
        int sum = 0;
        while (left <= right) {
            if (left % 2 == 1) {
                sum += tree[left];
                left += 1;
            }
            if (right % 2 == 0) {
                sum += tree[right];
                right -= 1;
            }
            left /= 2;
            right /= 2;
        }
        return sum;
    }
};

// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
class NumArray { // segment tree 91%
private:
    TreeNode* root = nullptr;
    int n = 0;

    TreeNode* build(int start, int end, vector<int>& nums) {
        if (start == end) {
            return new TreeNode(nums[start]);
        }

        TreeNode* cur = new TreeNode(0);
        int mid = start + (end - start) / 2;
        cur -> left = build(start, mid, nums);
        cur -> right = build(mid + 1, end, nums);
        cur -> val = cur -> left -> val + cur -> right -> val;
        return cur;
    }

    void update(int start, int end, int index, int val, TreeNode* cur) {
        if (start == end) {
            cur -> val = val;
            return;
        }

        int mid = start + (end - start) / 2;
        if (start <= index and index <= mid) {
            update(start, mid, index, val, cur -> left);
        }
        else {
            update(mid + 1, end, index, val, cur -> right);
        }
        cur -> val = cur -> left -> val + cur -> right -> val;
    }

    int query(int start, int end, int left, int right, TreeNode* cur) {
        if (start > right or left > end) {
            return 0;
        }

        if (left <= start and end <= right) {
            return cur -> val;
        }

        int mid = start + (end - start) / 2;
        return query(start, mid, left, right, cur -> left) + query(mid + 1, end, left, right, cur -> right);
    }
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        if (n == 0) {
            return;
        }
        root = build(0, n - 1, nums);
    }

    void update(int i, int val) {
        update(0, n - 1, i, val, root);
    }

    int sumRange(int i, int j) {
        return query(0, n - 1, i, j, root);
    }
};

class NumArray {
private:
    vector<int> sum;
    vector<int> aray;
public:
    NumArray(vector<int> nums) {
        sum.push_back(0);
        for (int num : nums) {
            sum.push_back(sum.back() + num);
            aray.push_back(num);
        }
    }

    void update(int i, int val) {
        int gap = val - aray[i];
        for (int x = i + 1; x < sum.size(); x++) {
            sum[x] += gap;
        }
        aray[i] = val;
    }

    int sumRange(int i, int j) {
        return sum[j + 1] - sum[i];
    }
};
/**
 * Your NumAray object wil be instantiated and caled as such:
 * NumAray obj = new NumAray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
*/
