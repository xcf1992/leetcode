/*
https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/description/
1953. Maximum Number of Weeks for Which You Can Work

There are n projects numbered from 0 to n - 1. You are given an integer array milestones where each milestones[i]
denotes the number of milestones the ith project has.

You can work on the projects following these two rules:

Every week, you will finish exactly one milestone of one project. You must work every week.
You cannot work on two milestones from the same project for two consecutive weeks.
Once all the milestones of all the projects are finished, or if the only milestones that you can work on will cause you
to violate the above rules, you will stop working. Note that you may not be able to finish every project's milestones
due to these constraints.

Return the maximum number of weeks you would be able to work on the projects without violating the rules mentioned
above.



Example 1:

Input: milestones = [1,2,3]
Output: 6
Explanation: One possible scenario is:
​​​​- During the 1st week, you will work on a milestone of project 0.
- During the 2nd week, you will work on a milestone of project 2.
- During the 3rd week, you will work on a milestone of project 1.
- During the 4th week, you will work on a milestone of project 2.
- During the 5th week, you will work on a milestone of project 1.
- During the 6th week, you will work on a milestone of project 2.
The total number of weeks is 6.
Example 2:

Input: milestones = [5,2,1]
Output: 7
Explanation: One possible scenario is:
- During the 1st week, you will work on a milestone of project 0.
- During the 2nd week, you will work on a milestone of project 1.
- During the 3rd week, you will work on a milestone of project 0.
- During the 4th week, you will work on a milestone of project 1.
- During the 5th week, you will work on a milestone of project 0.
- During the 6th week, you will work on a milestone of project 2.
- During the 7th week, you will work on a milestone of project 0.
The total number of weeks is 7.
Note that you cannot work on the last milestone of project 0 on 8th week because it would violate the rules.
Thus, one milestone in project 0 will remain unfinished.


Constraints:

n == milestones.length
1 <= n <= 105
1 <= milestones[i] <= 109
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
#include <climits>
using namespace std;
/*
The Greedy idea is, if the max elements is larger than the sum of the rest elements. then the max answer is 2 * rest +
1, because the best strategy is pick max, pick other, pick max, pick other....pick max. otherwise, we can finish all of
the milestones.

Proof:
the 1st case is obviously, let's consider the 2nd case: each number are evenly distributed. when we pair 1 and 2 like 1,
2 ,1, 2, 1, 2, 1, 2, how about 3? notice that we can insert 3 into any slot between 1 and 2, like 1, 2, 3, 1, ,2, 3,
1,2, 3,... for number 4, we apply the same way to insert number 4, so we can insert all the number even the numbers are
evenly distributed.

if max < total-max
we will always be able to complete all jobs
first of we will be able to complete the max_cnt job, cause the rest > max,
for any other job < max_cnt job, we can always find a position to insert it cause it's cnt less than max
*/
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long max_cnt = *max_element(milestones.begin(), milestones.end());
        long long total = 0;
        for (int i = 0; i < milestones.size(); i++) {
            total += 1LL * milestones[i];
        }
        long long rest = total - max_cnt;
        return min(total, rest * 2 + 1);
    }
};