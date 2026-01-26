/*
1723. Find Minimum Time to Finish All Jobs
https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs

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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

/*
This is multi-knapsack problem, which is NP-complete. Thus, the tight constraint (k <= 12).

So, we need to do the full search, but we can speed it up a little:

Track the current best result and use it to prune.
If two or more workers have the same working time, we only need to consider one of them.
The last optimization helps a lot, and we can just use a hash set to track the working time.

Update. I originally had the sorting but later removed as the solution got accepted without it.

In order to prune more efficiently, we can sort the jobs in the descending order, and calculate a greedy result, which
should be a great start.

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

The Critical Part: Avoiding Duplicate Work
Now for the part you asked about:
cppunordered_set<int> work_time;
for (auto j = 0; j < k; ++j) {
    if (!work_time.insert(worker[j]).second) {
        continue;
    }
    // ... assign job to worker j ...
}
What This Does
This code prevents exploring symmetric/duplicate assignments.
Example to Illustrate
Suppose we have:

jobs = [5, 3, 2]
k = 3 workers
Currently at job_idx = 0 (assigning the job with time 5)

Without this optimization, we'd try:

Assign job 5 to worker 0 (workload becomes [5, 0, 0])
Assign job 5 to worker 1 (workload becomes [0, 5, 0])
Assign job 5 to worker 2 (workload becomes [0, 0, 5])

But these are all identical! All three workers start with 0 workload, so it doesn't matter which one we pick. We're just
exploring the same solution space three times. How work_time Set Prevents This cppunordered_set<int> work_time;  //
Tracks which workload values we've tried Step-by-step for the example: Iterationjworker[j]work_time before insertInsert
resultAction100{}{0}, .second = true✅ Try this assignment210{0}{0}, .second = false❌ Skip (already tried worker with 0
workload)320{0}{0}, .second = false❌ Skip Result: We only explore assigning the job to ONE worker with workload 0, not
all three. Another Example with Different Workloads Suppose workers currently have workloads [5, 3, 5] and we're
assigning a new job: Iterationjworker[j]work_time beforeInsert resultAction105{}{5}, .second = true✅ Try
assignment213{5}{5, 3}, .second = true✅ Try assignment (different workload)325{5, 3}{5, 3}, .second = false❌ Skip
(already tried worker with workload 5) Understanding .second The .insert() method returns a pair<iterator, bool>:

.first: iterator to the element
.second: true if insertion happened (new element), false if element already existed

cppif (!work_time.insert(worker[j]).second) {
    continue;  // If .second is false, skip this worker
}
This means: "If we've already tried assigning a job to a worker with this exact workload, skip it."
Why This Optimization Matters
Without this optimization, the algorithm would explore many symmetric solutions. For example, with 3 empty workers,
assigning jobs in order [A→worker0, B→worker1] produces the same result as [A→worker1, B→worker0]. This optimization can
reduce the search space exponentially!
*/
class Solution {
public:
    int worker[12] = {};
    int rst = 0;

    int dfs(vector<int>& jobs, int job_idx, int k, int max_work_time) {
        if (max_work_time >= rst) {
            return rst;
        }

        if (job_idx == jobs.size()) {
            rst = max_work_time;
            return rst;
        }

        unordered_set<int> work_time;
        for (auto j = 0; j < k; ++j) {
            if (work_time.find(worker[j]) != work_time.end()) {
                continue;
            }

            work_time.insert(worker[j]);
            worker[j] += jobs[job_idx];
            dfs(jobs, job_idx + 1, k, max(max_work_time, worker[j]));
            worker[j] -= jobs[job_idx];
        }
        return rst;
    }

    int minimumTimeRequired(vector<int>& jobs, int k) {
        if (k == jobs.size()) {
            return *max_element(begin(jobs), end(jobs));
        }

        sort(jobs.rbegin(), jobs.rend());
        for (int i = 0; i < jobs.size(); i += k) {
            rst += jobs[i];  // this is the initial worst cast, we should try do better to reduce it
        }
        return dfs(jobs, 0, k, 0);
    }
};