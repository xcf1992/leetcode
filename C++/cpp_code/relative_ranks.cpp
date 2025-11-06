/*
506. Relative Ranks
Given scores of N athletes,
find their relative ranks and the people with the top three highest scores,
who will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

Example 1:
Input: [5, 4, 3, 2, 1]
Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and
"Bronze Medal". For the left two athletes, you just need to output their relative ranks according to their scores. Note:
N is a positive integer and won't exceed 10,000.
All the scores of athletes are guaranteed to be unique.
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

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        unordered_map<int, int> index;
        priority_queue<int> rank;
        for (int i = 0; i < nums.size(); i++) {
            index[nums[i]] = i;
            rank.push(nums[i]);
        }

        vector<string> result(nums.size(), "");
        int count = 1;
        while (rank.size() > 0) {
            if (count == 1) {
                result[index[rank.top()]] = "Gold Medal";
            } else if (count == 2) {
                result[index[rank.top()]] = "Silver Medal";
            } else if (count == 3) {
                result[index[rank.top()]] = "Bronze Medal";
            } else {
                result[index[rank.top()]] = to_string(count);
            }
            rank.pop();
            count += 1;
        }
        return result;
    }
};