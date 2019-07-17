/*
 373. Find K Pairs with Smallest Sums
 You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

 Define a pair (u,v) which consists of one element from the first array and one element from the second array.

 Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

 Example 1:
 Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

 Return: [1,2],[1,4],[1,6]

 The first 3 pairs are returned from the sequence:
 [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
 Example 2:
 Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

 Return: [1,1],[1,1]

 The first 2 pairs are returned from the sequence:
 [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
 Example 3:
 Given nums1 = [1,2], nums2 = [3],  k = 3

 Return: [1,3],[2,3]

 All possible pairs are returned from the sequence:
 [1,3],[2,3]
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
using namespace std;

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 == 0 or len2 == 0) {
            return {};
        }

        auto comp = [](vector<int>& a, vector<int>& b) {
            return a[2] > b[2];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> minHeap(comp);
        for (int j = 0; j < len2; ++j) {
            minHeap.push({0, j, nums1[0] + nums2[j]});
        }

        vector<vector<int>> result;
        while (!minHeap.empty() and result.size() < k) {
            vector<int> pair = minHeap.top();
            minHeap.pop();
            result.push_back({nums1[pair[0]], nums2[pair[1]]});
            if (pair[0] + 1 < len1) {
                minHeap.push({pair[0] + 1, pair[1], nums1[pair[0] + 1] + nums2[pair[1]]});
            }
        }
        return result;
    }
};

class Solution2 {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (nums1.empty() || nums2.empty()) {
            return {};
        }

        vector<vector<int>> pairs;
        for (int num1 : nums1) {
            for (int num2 : nums2) {
                pairs.push_back({num1, num2});
            }
        }
        sort(pairs.begin(), pairs.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] + a[1] < b[0] + b[1];
        });

        vector<vector<int>> result;
        for (int i = 0; i < pairs.size() && result.size() < k; ++i) {
            result.push_back(pairs[i]);
        }
        return result;
    }
};

class Solution1 {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;
        if (nums1.empty() || nums2.empty()) {
            return result;
        }

        auto comp = [](vector<int>& a, vector<int>& b) {
            return a[0] + a[1] > b[0] + b[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> minHeap(comp);

        for (int num1 : nums1) {
            for (int num2 : nums2) {
                minHeap.push({num1, num2});
            }
        }

        while (!minHeap.empty() && result.size() < k) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        return result;
    }
};
