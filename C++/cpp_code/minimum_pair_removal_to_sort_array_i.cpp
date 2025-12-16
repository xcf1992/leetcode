/*
https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/description/
3507. Minimum Pair Removal to Sort Array I

Given an array nums, you can perform the following operation any number of times:

Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
Replace the pair with their sum.
Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).



Example 1:

Input: nums = [5,2,3,1]

Output: 2

Explanation:

The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
The array nums became non-decreasing in two operations.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

The array nums is already sorted.



Constraints:

1 <= nums.length <= 50
-1000 <= nums[i] <= 1000
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int count = 0;
        while (!is_sorted(nums.begin(), nums.end())) {
            int mini = INT_MAX, idx = -1;
            for (int i = 1, n = nums.size(); i < n; ++i) {
                int sum = nums[i - 1] + nums[i];
                if (sum < mini) {
                    mini = sum;
                    idx = i - 1;
                }
            }
            nums[idx] += nums[idx + 1];
            nums.erase(nums.begin() + idx + 1);
            ++count;
        }
        return count;
    }
};

class Solution {
private:
    bool is_sorted(map<int, int>& sorted_nums) {
        for (auto it = sorted_nums.begin(); it != sorted_nums.end(); ++it) {
            if (it == sorted_nums.begin()) {
                continue;
            }

            if (it->second < prev(it)->second) {
                return false;
            }
        }
        return true;
    }

public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        map<int, int> sorted_nums;
        for (int i = 0; i < n; i++) {
            sorted_nums[i] = nums[i];
        }

        int rst = 0;
        while (!is_sorted(sorted_nums)) {
            int min_sum = INT_MAX;
            int min_idx = -1;
            for (auto it = sorted_nums.begin(); it != sorted_nums.end(); ++it) {
                if (it == prev(sorted_nums.end())) {
                    continue;
                }

                int cur_sum = it->second + next(it)->second;
                if (cur_sum < min_sum) {
                    min_sum = cur_sum;
                    min_idx = it->first;
                }
            }

            if (min_idx != -1) {
                auto it = sorted_nums.find(min_idx);
                auto next_it = next(it);
                sorted_nums[min_idx] = it->second + next_it->second;
                sorted_nums.erase(next_it->first);
                rst += 1;
            }
        }
        return rst;
    }
};
