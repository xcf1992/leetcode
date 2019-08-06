/*
 493. Reverse Pairs

 Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].

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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    void calculate(vector<int>& nums, int s1, int e1, int s2, int e2, int& result) {
        int i = s1;
        int j = s2;
        while (i <= e1) {
            while (j <= e2 && (long long)nums[i] > (long long)2 * nums[j]) {
                j += 1;
            }
            result += (j - s2);
            i += 1;
        }
        inplace_merge(nums.begin() + s1, nums.begin() + s2, nums.begin() + e2 + 1);
    }

    void mergeSort(vector<int>& nums, int start, int end, int& result) {
        if (start >= end) {
            return;
        }

        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid, result);
        mergeSort(nums, mid + 1, end, result);
        calculate(nums, start, mid, mid + 1, end, result);
    }
public:
    int reversePairs(vector<int>& nums) {
        int result = 0;
        mergeSort(nums, 0, nums.size() - 1, result);
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

        if (val == root -> value) {
            root -> geCount += 1;
        }
        else if (val > root -> value) {
            root -> geCount += 1;
            root -> right = insert(root -> right, val);
        }
        else {
            root -> left = insert(root -> left, val);
        }
        return root;
    }

    int search(BiggerNode* root, long target) {
        if (root == nullptr) {
            return 0;
        }

        if (target == root -> value) {
            return root -> geCount;
        }

        if (target < root -> value) {
            return root -> geCount + search(root -> left, target);
        }
        return search(root -> right, target);
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
