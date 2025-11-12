/*
1383. Maximum Performance of a Team
https://leetcode.com/problems/maximum-performance-of-a-team/

There are n engineers numbered from 1 to n and two arrays:
speed and efficiency,
where speed[i] and efficiency[i] represent the speed and efficiency for the i-th engineer respectively.
Return the maximum performance of a team composed of at most k engineers,
since the answer can be a huge number, return this modulo 10^9 + 7.

The performance of a team is the sum of their engineers' speeds multiplied by the minimum efficiency among their
engineers.

Example 1:
Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
Output: 60
Explanation:
We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5
(with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.

Example 2:
Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
Output: 68
Explanation:
This is the same example as the first but k = 3. We can select engineer 1, engineer 2 and engineer 5 to get the maximum
performance of the team. That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.

Example 3:
Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
Output: 72

Constraints:
1 <= n <= 10^5
speed.length == n
efficiency.length == n
1 <= speed[i] <= 10^5
1 <= efficiency[i] <= 10^8
1 <= k <= n
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition
Doesn't efficiency and speed are the same thing?
Like efficiency = speed = produce / time?
Speed sounds more like time actually.
You work slow, so you need more time.

@Msylcatam reminded me this problem 857. Minimum Cost to Hire K Workers
for your extra exercise as revision.

Hungry and out for meal.
For C++, may you refer to 857, exact the same template.

Special period, take care of yourself.
Wash your hand, touch the keyboard instead of your face.
Consider of putting a mask if necessary.
Very important, mute tv and twitter of terrible speech.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
We keep the queue with maximum size of k.
Each time when we introduce a new engineer,
we need only O(logK) to find the smallest speed in the team now.


Complexity
Time O(NlogN) for sorting
Time O(NlogK) for priority queue
Space O(N)

First of all, it may have some greedy, but I don't see it as a greedy problem.
Original problem: Find the maximum of min(efficiency) * sum(speed)
Problem I solved: Given any efficiency threshold , find out maximum sum(speed) with all efficiency > threshold.
You can see that, different statement here, but they solve the same problem.
And my solution are exactly what the second demands.
If one really understand the logic behind, it doesn't need any prove.
I don't understand why people are so into a "prove".
*/
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> worker;
        for (int i = 0; i < n; ++i) {
            worker.emplace_back(efficiency[i], speed[i]);
        }
        sort(worker.begin(), worker.end(), [](pair<int, int>& a, pair<int, int>& b) { return a.first > b.first; });

        long sum = 0;
        long result = 0;
        priority_queue<int, vector<int>, greater<int>> pq;  // minheap of speed
        for (auto& [efc, spd] : worker) {
            pq.emplace(spd);
            sum += spd;
            if (pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            result = max(result, sum * efc);
        }
        return result % int(1e9 + 7);
    }
};