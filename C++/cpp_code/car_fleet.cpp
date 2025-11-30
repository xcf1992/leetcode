/*
853. Car Fleet
https://leetcode.com/problems/car-fleet/

N cars are going to the same destination along a one lane road.
The destination is target miles away.

Each car i has a constant speed speed[i] (in miles per hour),
and initial position position[i] miles towards the target along the road.

A car can never pass another car ahead of it,
but it can catch up to it, and drive bumper to bumper at the same speed.

The distance between these two cars is ignored - they are assumed to have the same position.

A car fleet is some non-empty set of cars driving at the same position and same speed.
Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point,
it will still be considered as one car fleet.

How many car fleets will arrive at the destination?

Example 1:
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 and 8 become a fleet, meeting each other at 12.
The car starting at 0 doesn't catch up to any other car, so it is a fleet by itself.
The cars starting at 5 and 3 become a fleet, meeting each other at 6.
Note that no other cars meet these fleets before the destination, so the answer is 3.

Note:
0 <= N <= 10 ^ 4
0 < target <= 10 ^ 6
0 < speed[i] <= 10 ^ 6
0 <= position[i] < target
All initial positions are different.
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
using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n == 0) {
            return 0;
        }

        vector<pair<double, double>> car;
        for (int i = 0; i < n; i++) {
            car.push_back({position[i], speed[i]});
        }
        sort(car.begin(), car.end(),
             [](pair<double, double>& a, pair<double, double>& b) { return a.first < b.first; });

        int result = 1;
        double arrive = (target - car[n - 1].first) / car[n - 1].second;
        for (int i = n - 2; i >= 0; i--) {
            double newArrive = (target - car[i].first) / car[i].second;
            if (newArrive > arrive) {
                arrive = newArrive;
                result += 1;
            }
        }
        return result;
    }
};