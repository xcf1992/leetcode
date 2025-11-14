/*
https://leetcode.com/problems/maximum-number-of-robots-within-budget/
2398. Maximum Number of Robots Within Budget

You have n robots. You are given two 0-indexed integer arrays, chargeTimes and runningCosts, both of length n. The ith
robot costs chargeTimes[i] units to charge and costs runningCosts[i] units to run. You are also given an integer budget.

The total cost of running k chosen robots is equal to max(chargeTimes) + k * sum(runningCosts), where max(chargeTimes)
is the largest charge cost among the k robots and sum(runningCosts) is the sum of running costs among the k robots.

Return the maximum number of consecutive robots you can run such that the total cost does not exceed budget.



Example 1:

Input: chargeTimes = [3,6,1,3,4], runningCosts = [2,1,3,4,5], budget = 25
Output: 3
Explanation:
It is possible to run all individual and consecutive pairs of robots within budget.
To obtain answer 3, consider the first 3 robots. The total cost will be max(3,6,1) + 3 * sum(2,1,3) = 6 + 3 * 6 = 24
which is less than 25. It can be shown that it is not possible to run more than 3 consecutive robots within budget, so
we return 3. Example 2:

Input: chargeTimes = [11,12,19], runningCosts = [10,8,7], budget = 19
Output: 0
Explanation: No robot can be run that does not exceed the budget, so we return 0.


Constraints:

chargeTimes.length == runningCosts.length == n
1 <= n <= 5 * 104
1 <= chargeTimes[i], runningCosts[i] <= 105
1 <= budget <= 1015
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
#include <deque>
#include <map>
using namespace std;

class Solution1 {
public:
    int maximumRobots(vector<int>& times, vector<int>& costs, long long budget) {
        int left = 0;
        long long sum = 0;
        int n = times.size();
        multiset<int> time_set;
        for (int right = 0; right < n; ++right) {
            sum += costs[right];
            time_set.insert(times[right]);
            if (*rbegin(time_set) + sum * (right - left + 1) >
                budget) {  // not use while here so the window do not shrink
                sum -= costs[left];
                time_set.erase(time_set.find(times[left]));
                left += 1;
            }
        }
        return n - left;
    }
};

class Solution {
public:
    int maximumRobots(vector<int>& times, vector<int>& costs, long long budget) {
        int left = 0;
        long long sum = 0;
        int n = times.size();
        deque<int> dq;
        for (int right = 0; right < n; ++right) {
            sum += costs[right];
            while (!dq.empty() && times[dq.back()] <= times[right]) {
                dq.pop_back();
            }
            dq.push_back(right);
            if (times[dq.front()] + (right - left + 1) * sum > budget) {
                sum -= costs[left];
                if (dq.front() == left) {
                    dq.pop_front();
                }
                left += 1;
            }
        }
        return n - left;
    }
};