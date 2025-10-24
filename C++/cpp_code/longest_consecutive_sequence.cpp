/*
https://leetcode.com/problems/longest-consecutive-sequence/
128. Longest Consecutive Sequence

Given an unsorted array of integers,
find the length of the longest consecutive elements sequence.
Your algorithm should run in O(n) complexity.

Example:
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
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

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> count;
        for (int k : nums) {
            count.insert(k);
        }

        int result = 0;
        for (int k : nums) {
            if (count.find(k) == count.end()) {
                continue;
            }

            int left = k;
            while (count.find(left - 1) != count.end()) {
                count.erase(left - 1);
                left -= 1;
            }

            int right = k;
            while (count.find(right + 1) != count.end()) {
                count.erase(right + 1);
                right += 1;
            }

            result = max(result, right - left + 1);
            count.erase(k);
        }
        return result;
    }
};
