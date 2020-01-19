/*
473. Matchsticks to Square

Remember the story of Little Match Girl?
By now, you know exactly what matchsticks the little match girl has,
please find out a way you can make one square by using up all those matchsticks.
You should not break any stick, but you can link them up,
and each matchstick must be used exactly one time.

Your input will be several matchsticks the girl has,
represented with their stick length.
Your output will either be true or false,
to represent whether you could make one square using all the matchsticks the little match girl has.

Example 1:
Input: [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.

Example 2:
Input: [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.

Note:
The length sum of the given matchsticks is in the range of 0 to 10^9.
The length of the given matchstick array will not exceed 15.
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
#include <numeric>
using namespace std;

class Solution {
public:
    bool makesquare(vector<int>& nums) {
        int n = nums.size();
        long sum = accumulate(nums.begin(), nums.end(), 0l);
        if (sum % 4) {
            return false;
        }
        long sideLen = sum / 4;
        // need to solve the problem of partitioning nums into four equal subsets each having sum equal to sideLen
        vector<int> usedMasks;
        // validHalfSubsets[i] == true iff the subset represented by bitmask i
        // has sum == 2 * sideLen,
        // AND the subset represented by i can be further partitioned into two equal subsets.
        vector<bool> validHalfSubsets(1 << n, false);

        // E.g., if n = 5, (1 << 5 - 1) = 11111 represents the whole set
        int all = (1 << n) - 1;
        // go through all possible subsets each represented by a bitmask
        for (int mask = 0; mask <= all; mask++) {
            long subsetSum = 0;
            // calculate the sum of this subset
            for (int i = 0; i < 32; i++) if ((mask >> i) & 1) {
                subsetSum += nums[i];
            }
            if (subsetSum != sideLen) {
                continue;
            }

            for (int usedMask : usedMasks) if ((usedMask & mask) == 0) {
                // then they form a valid half subset whose sum is 2 * sideLen,
                // that can be further partitioned into two equal subsets (usedMask and mask)
                int validHalf = usedMask | mask;
                validHalfSubsets[validHalf] = true;
                // if in the past we concluded that the other half is also a valid half subset, DONE!
                if (validHalfSubsets[all ^ validHalf]) {
                    return true;
                }
            }
            // usedMask only store the mask has the sum of length == sideLen
            usedMasks.push_back(mask);
        }
        return false;
    }
};

class Solution1 { // simple dfs but slow
private:
    bool valid(vector<int>& nums, int index, vector<int>& side, int length) {
        if (index >= nums.size()) {
            for (int l : side) {
                if (l != length) {
                    return false;
                }
            }
            return true;
        }

        for (int i = 0; i < side.size(); i++) {
            if (side[i] + nums[index] <= length) {
                side[i] += nums[index];
                if (valid(nums, index + 1, side, length)) {
                    return true;
                }
                side[i] -= nums[index];
            }
        }
        return false;
    }
public:
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4) {
            return false;
        }

        int sum = 0;
        int longest = 0;
        for (int num : nums) {
            sum += num;
            longest = max(longest, num);
        }

        if (sum % 4 != 0) {
            return false;
        }

        int length = sum / 4;
        if (longest > length) {
            return false;
        }

        vector<int> side(4, 0);
        sort(nums.rbegin(), nums.rend()); // trick here accelerate process time, cause longer stick will fail first
        return valid(nums, 0, side, length);
    }
};
