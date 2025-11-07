/*
1235. Maximum Profit in Job Scheduling
https://leetcode.com/problems/maximum-profit-in-job-scheduling/

We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i],
obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays,
you need to output the maximum profit you can take
such that there are no 2 jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

Example 1:
          |profit=40|
     |profit=10|
|profit=50|profit=70     |
1    2    3    4    5    6
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job.
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

Example 2:
     |profit=20     |
          |profit=100                        |
|profit=20|    |profit=70|profit=60     |
1    2    3    4    5    6    7    8    9    10
Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job.
Profit obtained 150 = 20 + 70 + 60.

Example 3:
|profit=4                     |
|profit=6           |
|profit=5 |
1         2         3         4
Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6

Constraints:
1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
1 <= startTime[i] < endTime[i] <= 10^9
1 <= profit[i] <= 10^4
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
/*
Sort the jobs by endTime.

dp[time] = profit means that within the first time duration,
we cam make at most profit money.
Intial dp[0] = 0, as we make profit = 0 at time = 0.

For each job = [s, e, p], where s,e,p are its start time, end time and profit,
Then the logic is similar to the knapsack problem.
If we don't do this job, nothing will be changed.
If we do this job, binary search in the dp to find the largest profit we can make before start time s.
So we also know the maximum current profit that we can make doing this job.

Compare with last element in the dp,
we make more money,
it worth doing this job,
then we add the pair of [e, cur] to the back of dp.
Otherwise, we'd like not to do this job.

Complexity
Time O(NlogN) for sorting
Time O(NlogN) for binary search for each job
Space O(N)
*/
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());

        map<int, int> dp;
        dp[0] = 0;
        for (vector<int>& job : jobs) {
            int job_start_time = job[1];
            int job_end_time = job[0];
            int job_profit = job[2];
            // profit we can get if we take cur job
            int cur_profit = prev(dp.upper_bound(job_start_time))->second + job_profit;
            if (cur_profit > dp.rbegin()->second) {
                dp[job_end_time] = cur_profit;  // maximum profit we can get at time job[0]
            }
        }
        return dp.rbegin()->second;
    }
};
