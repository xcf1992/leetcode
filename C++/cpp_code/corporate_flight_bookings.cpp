/*
1109. Corporate Flight Bookings
https://leetcode.com/problems/corporate-flight-bookings/

There are n flights, and they are labeled from 1 to n.

We have a list of flight bookings.
The i-th booking bookings[i] = [i, j, k] means that we booked k seats from flights labeled i to j inclusive.

Return an array answer of length n,
representing the number of seats booked on each flight in order of their label.

Example 1:
Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]

Constraints:

1 <= bookings.length <= 20000
1 <= bookings[i][0] <= bookings[i][1] <= n <= 20000
1 <= bookings[i][2] <= 10000
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
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> count(n + 2, 0);  // count is 1 base
        for (vector<int>& booking : bookings) {
            count[booking[0]] += booking[2];
            count[booking[1] + 1] -= booking[2];
        }

        vector<int> result(n, 0);  // result is 0 base
        result[0] = count[1];
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] + count[i + 1];
        }
        return result;
    }
};