/*
https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/description/
3414. Maximum Score of Non-overlapping Intervals

You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and
ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen
intervals is defined as the total sum of their weights.

Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your
choice of non-overlapping intervals.

Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or
right boundary are considered overlapping.



Example 1:

Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]

Output: [2,3]

Explanation:

You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.

Example 2:

Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]

Output: [1,3,5,6]

Explanation:

You can choose the intervals with indices 1, 3, 5, and 6 with respective weights of 7, 6, 3, and 5.



Constraints:

1 <= intevals.length <= 5 * 104
intervals[i].length == 3
intervals[i] = [li, ri, weighti]
1 <= li <= ri <= 109
1 <= weighti <= 109
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
#include <map>
#include <stdio.h>
using namespace std;

class Solution {
public:
    std::vector<int> maximumWeight(std::vector<std::vector<int>>& intervals) {
        int n = intervals.size();
        for (int i = 0; i < n; ++i) {
            intervals[i].push_back(i);
        }

        // Sort by end time
        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& left, const std::vector<int>& right) { return left[1] < right[1]; });

        std::vector<std::vector<std::pair<long, std::vector<int>>>> dp(
                n, std::vector<std::pair<long, std::vector<int>>>(5, {0, {}}));

        dp[0][1] = {intervals[0][2], {intervals[0][3]}}; // weight, index
        long maxWeight = intervals[0][2];

        for (int i = 1; i < n; ++i) {
            int low = 0, high = i - 1, idx = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (intervals[mid][1] < intervals[i][0]) {
                    idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            for (int j = 1; j < 5; ++j) {
                dp[i][j] = dp[i - 1][j];  // Inherit from previous state
                if (idx != -1) {
                    long newWeight = dp[idx][j - 1].first + intervals[i][2];
                    std::vector<int> newIndices = dp[idx][j - 1].second;
                    newIndices.push_back(intervals[i][3]);
                    std::sort(newIndices.begin(), newIndices.end());

                    if (dp[i][j].first < newWeight || (dp[i][j].first == newWeight && newIndices < dp[i][j].second)) {
                        dp[i][j] = {newWeight, newIndices};
                    }
                }

                if (j == 1) {
                    long singleWeight = intervals[i][2];
                    std::vector<int> singleIndex = {intervals[i][3]};

                    if (dp[i][j].first < singleWeight ||
                        (dp[i][j].first == singleWeight && singleIndex < dp[i][j].second)) {
                        dp[i][j] = {singleWeight, singleIndex};
                    }
                }

                maxWeight = std::max(maxWeight, dp[i][j].first);
            }
        }

        std::vector<int> result = {100000};
        for (int j = 1; j < 5; ++j) {
            if (maxWeight == dp[n - 1][j].first) {
                result = std::min(result, dp[n - 1][j].second);
            }
        }

        return result;
    }
};
