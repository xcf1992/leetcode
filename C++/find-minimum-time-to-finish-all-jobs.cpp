/*
1723. Find Minimum Time to Finish All Jobs
https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs
/
You are given an integer array jobs,
where jobs[i] is the amount of time it takes to complete the ith job.

There are k workers that you can assign jobs to.
Each job should be assigned to exactly one worker.
The working time of a worker is the sum of the time it takes to complete all jobs assigned to them.
Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.

Return the minimum possible maximum working time of any assignment.

Example 1:
Input: jobs = [3,2,3], k = 3
Output: 3
Explanation: By assigning each person one job, the maximum time is 3.
Example 2:
Input: jobs = [1,2,4,7,8], k = 2
Output: 11
Explanation: Assign the jobs the following way:
Worker 1: 1, 2, 8 (working time = 1 + 2 + 8 = 11)
Worker 2: 4, 7 (working time = 4 + 7 = 11)
The maximum working time is 11.

Constraints:
1 <= k <= jobs.length <= 12
1 <= jobs[i] <= 107
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
#include <numeric>
using namespace std;

class Solution {
public:
int worker[12] = {}, res = 0;
    int dfs(vector<int> &jobs, int i, int k, int cur)
    {
        if (cur >= res)
            return res;
        if (i == jobs.size())
            return res = cur;
        unordered_set<int> workTime;
        for (auto j = 0; j < k; ++j)
        {
            if (!workTime.insert(worker[j]).second)
                continue;
            worker[j] += jobs[i];
            dfs(jobs, i + 1, k, max(cur, worker[j]));
            worker[j] -= jobs[i];
        }
        return res;
    }
    
    int minimumTimeRequired(vector<int> &jobs, int k)
    {
        if (k == jobs.size())
            return *max_element(begin(jobs), end(jobs));
        sort(begin(jobs), end(jobs), greater<int>());
        for (int i = 0; i < jobs.size(); i += k)
            res += jobs[i];
        return dfs(jobs, 0, k, 0);
    }
};
