/*
347. Top K Frequent Elements
https://leetcode.com/problems/top-k-frequent-elements/

Given a non-empty array of integers, return the k most frequent elements.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
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

struct myCmp {
    bool operator()(pair<int, int>& myPair1, pair<int, int>& myPair2) {
        return myPair1.first < myPair2.first;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::vector<int> result;

        unordered_map<int, int> frequency;
        for (int i = 0; i < nums.size(); i++) {
            frequency[nums[i]] += 1;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, myCmp> pq;
        for (auto& it : frequency) {
            pq.push({it.second, it.first});
        }

        while (!pq.empty() and result.size() < k) {
            auto& p = pq.top();
            result.push_back(p.second);
            pq.pop();
        }
        return result;
    }
};