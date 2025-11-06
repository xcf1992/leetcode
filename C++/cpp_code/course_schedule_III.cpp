/*
630. Course Schedule III

There are n different online courses numbered from 1 to n.
Each course has some duration(course length) t and closed on dth day.
A course should be taken continuously for t days and must be finished before or on the dth day.
You will start at the 1st day.

Given n online courses represented by pairs (t,d),
your task is to find the maximal number of courses that can be taken.

Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation:
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course
on the 101st day. Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to
take the next course on the 1101st day. Third, take the 2nd course, it costs 200 days so you will finish it on the
1300th day. The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed
date.

Note:
The integer 1 <= d, t, n <= 10,000.
You can't take two courses simultaneously.
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
#include <numeric>
using namespace std;
/*
Sort the courses by the ascending order of deadline.

At each deadline:
we try to take as many as courses possible, (say take k courses)

# rule1 *
the courses take in total cur days,
if there are multiple ways of taking k courses, we keep the way which has least cur.

# rule2
At deadline d with course duration = t:
If cur + t <= d, that means we can take the course without violating its deadline, so we take it:
cur += t

Else, that means we can't simply take the course:
If t >= the max duration of any courses currently taken, then it won't benefit us by taking this course, so we skip it.
If t < the max duration of any courses currently taken:
    let max_t be the course taken which has max duration,
    since t < max_t, we should use course t to replace max_t,
    the benefit is that, now we have new_cur = old_cur + t - max_t which is less than old_cur.
    How do we make sure that we can always take t without violating its deadline d?
        This is always guaranteed, because:
        old_cur <= d (always guaranteed by the algorithm)
        because new_cur = old_cur + t - max_t and t < max_t, new_cur < old_cur
        so new_cur < d
        that means by replacing max_t with t, we guarantee the total days (new_cur) is less than the deadline.
Running Time: O(N log N)
Space: O(N)

1. Why we just pop out the last longest course that is screwing total day time?
Because all the courses that we have saw till now all complete before the d day.
Hence we can just simply remove any of the course from it.
Ideally we should remove the course which will give the maximum savings(d - t).
But since the courses are sorted by d,
Just the largest t course removal will suffice.
Hence we can save some time for the next incoming courses

2. When we replace a longer course with a much shorter one,
does that mean we'll have enough room to take some courses previously ignored for being too long?
The answer is NO, because any courses we missed would be longer than what's in priority queue.
So the increase in number of days cannot be larger than the largest element in queue,
and certainly will be less than a previously ignored course which has to be even longer.

Example : [[10,100],[95,100],[100,5000]]
Here we could take the 10 day course, then the 100 day course & now since more days are available we can take 95 day
course BUT THAT IS WRONG We need to complete the 95 day course by the 100TH day which will never be possible So either
we can take 10 day one or 95 day one. But it will be only one course possible (Better take smaller length course so the
next courses get time. Thats why Priority queues are used)
*/
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; });

        priority_queue<int> maxHeap;
        int current = 0;
        for (vector<int>& c : courses) {
            current += c[0];
            maxHeap.push(c[0]);
            if (current > c[1]) {
                current -= maxHeap.top();
                maxHeap.pop();
            }
        }
        return maxHeap.size();
    }
};

class Solution1 {
    // dfs with memo TLE
private:
    int schedule(vector<vector<int>>& courses, vector<vector<int>>& dp, int start, int curTime) {
        if (start >= courses.size()) {
            return 0;
        }
        if (dp[start][curTime] != -1) {
            return dp[start][curTime];
        }

        dp[start][curTime] = 0;
        if (curTime + courses[start][0] <= courses[start][1]) {
            dp[start][curTime] = 1 + schedule(courses, dp, start + 1, curTime + courses[start][0]);
        }
        dp[start][curTime] = max(dp[start][curTime], schedule(courses, dp, start + 1, curTime));
        return dp[start][curTime];
    }

public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();
        if (n == 0) {
            return 0;
        }

        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; });
        vector<vector<int>> dp(n, vector<int>(courses.back()[1] + 1, -1));
        return schedule(courses, dp, 0, 0);
    }
};