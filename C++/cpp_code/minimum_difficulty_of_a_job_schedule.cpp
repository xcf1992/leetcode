/*
1335. Minimum Difficulty of a Job Schedule
https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

You want to schedule a list of jobs in d days.
Jobs are dependent
(i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day.
The difficulty of a job schedule is the sum of difficulties of each day of the d days.
The difficulty of a day is the maximum difficulty of a job done in that day.

Given an array of integers jobDifficulty and an integer d.
The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule.
If you cannot find a schedule for the jobs return -1.

Example 1:
    6
    5
    4
    3
    2
    1           1
 day 1        day 2
Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7

Example 2:
Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.

Example 3:
Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.

Example 4:
Input: jobDifficulty = [7,1,7,1,7,1], d = 3
Output: 15

Example 5:
Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
Output: 843

Constraints:
1 <= jobDifficulty.length <= 300
0 <= jobDifficulty[i] <= 1000
1 <= d <= 10
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
#include "extra_data_types.hpp"
using namespace std;
/*
Solution1: Top-down DP with cache
dfs help find the the minimum difficulty
if start work at ith job with d days left.

If d = 1, only one day left, we have to do all jobs,
return the maximum difficulty of jobs.

Time complexity O(nnd)
Space complexity O(nd)

We denote dp[d][i] as: We have d days left, and and we have finished all the tasks before arr[i] (not including i).
Then the answer is just dp[day][0] (using all the days given, and starting from arr[0]).

Now, consider the state conversion:

dp[d][i] = minimum of ( maximum value between arr[i,j] + dp[d-1][j+1] ); in which j is from [i, n].

Explanation: We can use current day to finish many tasks, so we discuss them one by one.
If we just finish one task today, then dp[d][i] = arr[i] + dp[d-1][i+1]
If we finish two tasks today, then dp[d][i] = max(arr[i], arr[i+1]) + dp[d-1][i+2] and so on...

Note: We should note that there could be illegal cases, where you have too many days left,
and even you finish only one tasks per day, you cannot use all the days left,
we should explicitly consider this case,
that is: n-i < d, and assign this case with value INF.

Improvement (not included in the code): We can preprocess the maximum value between arr[i,j]
and store them to make the code faster, I will not implement it here,
just to make the code easier to understand.
https://www.geeksforgeeks.org/divide-the-array-in-k-segments-such-that-the-sum-of-minimums-is-maximized/
*/
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int inf = 1e9 + 7;
        int n = jobDifficulty.size();
        if (n < d) {
            return -1;
        }

        vector<int> dp(n + 1, inf);
        dp[n] = 0;
        for (int k = 1; k <= d; ++k) {
            for (int i = 0; i <= n - k; ++i) {
                int maxDiffculty = 0;
                dp[i] = inf;
                for (int j = i; j <= n - k; ++j) {
                    maxDiffculty = max(maxDiffculty, jobDifficulty[j]);
                    dp[i] = min(dp[i], maxDiffculty + dp[j + 1]);
                }
            }
        }
        return dp[0];
    }
};