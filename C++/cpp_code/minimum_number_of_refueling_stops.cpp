/*
871. Minimum Number of Refueling Stops

A car travels from a starting position to a destination
which is target miles east of the starting position.

Along the way, there are gas stations.
Each station[i] represents a gas station that is station[i][0] miles east of the starting position,
and has station[i][1] liters of gas.

The car starts with an infinite tank of gas,
which initially has startFuel liters of fuel in it.
It uses 1 liter of gas per 1 mile that it drives.

When the car reaches a gas station,
it may stop and refuel,
transferring all the gas from the station into the car.

What is the least number of refueling stops the car must make in order to reach its destination?
If it cannot reach the destination, return -1.

Note that if the car reaches a gas station with 0 fuel left,
the car can still refuel there.
If the car reaches the destination with 0 fuel left, it is still considered to have arrived.

Example 1:
Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.

Example 2:
Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can't reach the target (or even the first gas station).

Example 3:
Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation:
We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.

Note:
1 <= target, startFuel, stations[i][1] <= 10^9
0 <= stations.length <= 500
0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < target
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
use priority queue
When driving past a gas station,
let's remember the amount of fuel it contained.
We don't need to decide yet whether to fuel up here or not - for example,
there could be a bigger gas station up ahead that we would rather refuel at.

When we run out of fuel before reaching the next station,
we'll retroactively fuel up: greedily choosing the largest gas stations first.

This is guaranteed to succeed because we drive the largest distance possible before each refueling stop,
and therefore have the largest choice of gas stations to (retroactively) stop at.
*/
struct myComp {
    bool operator()(int a, int b) {
        return a < b;
    }
};

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        stations.push_back({target, 0});
        priority_queue<int, vector<int>, myComp> pq;
        int tank = startFuel;
        int pos = 0;
        int result = 0;
        for (vector<int>& station : stations) {
            tank -= station[0] - pos;
            while (tank < 0 and !pq.empty()) {
                tank += pq.top();
                pq.pop();
                result += 1;
            }

            if (tank < 0) {
                return -1;
            }

            pq.push(station[1]);
            pos = station[0];
        }
        return result;
    }
};

/*
Let's determine dp[i], the farthest location we can get to using i refueling stops.
This is motivated by the fact that we want the smallest i for which dp[i] >= target.
Let's update dp as we consider each station in order.
With no stations, clearly we can get a maximum distance of startFuel with 0 refueling stops.

Now let's look at the update step. When adding a station station[i] = (location, capacity),
any time we could reach this station with t refueling stops,
we can now reach capacity further with t+1 refueling stops.

For example, if we could reach a distance of 15 with 1 refueling stop,
and now we added a station at location 10 with 30 liters of fuel,
then we could potentially reach a distance of 45 with 2 refueling stops.
--------------------------------------------------------------------------------------------------
dp[t] means the furthest distance that we can get with t times of refueling.

So for every station s[i],
if the current distance dp[t] >= s[i][0], we can refuel:
dp[t + 1] = max(dp[t + 1], dp[t] + s[i][1])

In the end, we'll return the first t with dp[i] >= target,
otherwise we'll return -1.

time complexity is O(n ^ 2), n is the number of stations
*/
class Solution2 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        vector<long> dp(n + 1, startFuel);
        for (int i = 0; i < n; i++) {
            for (int t = i; t >= 0; t--) {
                if (dp[t] >= stations[i][0]) {
                    dp[t + 1] = max(dp[t + 1], dp[t] + stations[i][1]);
                }
            }
        }

        for (int i = 0; i <= n; i++) {
            if (dp[i] >= target) {
                return i;
            }
        }
        return -1;
    }
};

class Solution1 {
private:
    bool refuel(int leftGas, int curStation, int stops, int& result, vector<vector<int>>& stations) {
        if (leftGas < 0) {
            return false;
        }

        if (curStation == stations.size() - 1) {
            result = min(result, stops);
            return true;
        }

        int distance = stations[curStation + 1][0] - stations[curStation][0];
        if (refuel(leftGas - distance, curStation + 1, stops, result, stations) or
            refuel(leftGas - distance + stations[curStation][1], curStation + 1, stops + 1, result, stations)) {
            return true;
        }
        return false;
    }

public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        stations.push_back({target, 0});
        int result = INT_MAX;
        if (refuel(startFuel - stations[0][0], 0, 0, result, stations)) {
            return result;
        }
        return -1;
    }
};