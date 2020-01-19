/*
491. Increasing Subsequences

Given an integer array,
your task is to find all the different possible increasing subsequences of the given array,
and the length of an increasing subsequence should be at least 2 .

Example:
Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
Note:
The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates,
and two equal integers should also be considered as a special case of increasing sequence.
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
A short explanation to the hash table:
this is to record used numbers so that if we ever encounters a duplicate later,
it will be skipped.
For example, if we have {4, 6(1), 7, 6(2), 6(3), ...}.
At some point the hash table is {4, 6(1)}.
When we visit 6(2) or 6(3),
since we find 6(1) is already in the table,
we skip to the next number.
*/
class Solution {
private:
    void dfs(vector<vector<int>>& result, vector<int>& cur, vector<int>& nums, int index) {
        if (cur.size() > 1) {
            result.push_back(cur);
        }

        unordered_set<int> unique;
        for (int i = index; i < nums.size(); i++) {
            if ((cur.empty() or nums[i] >= cur.back()) and unique.find(nums[i]) == unique.end()) {
                cur.push_back(nums[i]);
                dfs(result, cur, nums, i + 1);
                cur.pop_back();
                unique.insert(nums[i]);
            }
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> cur;
        dfs(result, cur, nums, 0);
        return result;
    }
};

/*
this is to generate increasing arrays using numbers from nums
class Solution {
private:
    void dfs(vector<vector<int>>& result, vector<int>& cur, map<int, int> count) {
        if (cur.size() > 1) {
            result.push_back(cur);
        }

        for (auto& it : count) {
            if (cur.empty() or it.first > cur.back()) {
                vector<int> temp = cur;
                for (int i = 0; i < it.second; ++i) {
                    temp.push_back(it.first);
                    dfs(result, temp, count);
                }
            }
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        map<int, int> count;
        for (int num : nums) {
            count[num] += 1;
        }

        vector<vector<int>> result;
        vector<int> cur;
        dfs(result, cur, count);
        return result;
    }
};
*/