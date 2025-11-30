/*
493. Reverse Pairs
https://leetcode.com/problems/reverse-pairs/

Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2 * nums[j].
You need to return the number of important reverse pairs in the given array.

Example1:
Input: [1,3,2,3,1]
Output: 2

Example2:
Input: [2,4,3,5,1]
Output: 3

Note:
The length of the given array will not exceed 50,000.
All the numbers in the input array are in the range of 32-bit integer.
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
#include <numeric>
using namespace std;

class Solution {
private:
    void calculate(vector<int>& nums, int left, int mid, int right, int& result) {
        int i = left;
        int j = mid;
        while (i < mid) {
            while (j < right and (long long) nums[i] > (long long)2 * nums[j]) {
                j += 1;
            }
            result += (j - mid);
            i += 1;
        }
        inplace_merge(nums.begin() + left, nums.begin() + mid, nums.begin() + right);
    }

    void mergeSort(vector<int>& nums, int start, int end, int& result) {
        if (start >= end - 1) {
            return;
        }

        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid, result);
        mergeSort(nums, mid, end, result);
        calculate(nums, start, mid, end, result);
    }

public:
    int reversePairs(vector<int>& nums) {
        int result = 0;
        mergeSort(nums, 0, nums.size(), result);
        return result;
    }
};

/*
solve using BST
but bst now gets TLE as test case with a very long sorted increasing array,
this would lead to very unbalance tree and degrade the performance to be O(n^2)
*/
struct BiggerNode {
    int value;
    int geCount;
    BiggerNode* left;
    BiggerNode* right;

    BiggerNode(int val) {
        value = val;
        geCount = 1;
        left = nullptr;
        right = nullptr;
    }
};

class Solution1 {
private:
    BiggerNode* insert(BiggerNode* root, int val) {
        if (root == nullptr) {
            return new BiggerNode(val);
        }

        if (val == root->value) {
            root->geCount += 1;
        } else if (val > root->value) {
            root->geCount += 1;
            root->right = insert(root->right, val);
        } else {
            root->left = insert(root->left, val);
        }
        return root;
    }

    int search(BiggerNode* root, long target) {
        if (root == nullptr) {
            return 0;
        }

        if (target == root->value) {
            return root->geCount;
        }

        if (target < root->value) {
            return root->geCount + search(root->left, target);
        }
        return search(root->right, target);
    }

public:
    int reversePairs(vector<int>& nums) {
        int result = 0;
        BiggerNode* root = nullptr;
        for (int n : nums) {
            result += search(root, n * 2);
            root = insert(root, n);
        }
        return result;
    }
};