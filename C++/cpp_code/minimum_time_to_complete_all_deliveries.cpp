/*
https://leetcode.com/problems/minimum-time-to-complete-all-deliveries/description/
3733. Minimum Time to Complete All Deliveries

You are given two integer arrays of size 2: d = [d1, d2] and r = [r1, r2].

Two delivery drones are tasked with completing a specific number of deliveries. Drone i must complete di deliveries.

Each delivery takes exactly one hour and only one drone can make a delivery at any given hour.

Additionally, both drones require recharging at specific intervals during which they cannot make deliveries. Drone i
must recharge every ri hours (i.e. at hours that are multiples of ri).

Return an integer denoting the minimum total time (in hours) required to complete all deliveries.



Example 1:

Input: d = [3,1], r = [2,3]

Output: 5

Explanation:

The first drone delivers at hours 1, 3, 5 (recharges at hours 2, 4).
The second drone delivers at hour 2 (recharges at hour 3).
Example 2:

Input: d = [1,3], r = [2,2]

Output: 7

Explanation:

The first drone delivers at hour 3 (recharges at hours 2, 4, 6).
The second drone delivers at hours 1, 5, 7 (recharges at hours 2, 4, 6).
Example 3:

Input: d = [2,1], r = [3,4]

Output: 3

Explanation:

The first drone delivers at hours 1, 2 (recharges at hour 3).
The second drone delivers at hour 3.


Constraints:

d = [d1, d2]
1 <= di <= 109
r = [r1, r2]
2 <= ri <= 3 * 104
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
#include <numeric>
using namespace std;

typedef long long ll;
class Solution {
private:
    ll lcm(ll a, ll b) {
        return a * b / gcd(a, b);
    }

    bool can_deliver(ll total, vector<int>& d, vector<int>& r) {
        ll available_1 = total - total / r[0];
        ll available_2 = total - total / r[1];
        if (available_1 < d[0] || available_2 < d[1]) {
            return false;
        }

        ll both_recharge = total / lcm(r[0], r[1]);
        ll both_available = total - both_recharge;
        return both_available >= d[0] + d[1];
    }

public:
    long long minimumTime(vector<int>& d, vector<int>& r) {
        ll left = 0;
        ll right = 2e10;
        ll rst = -1;
        while (left < right) {
            ll mid = left + (right - left) / 2;
            if (can_deliver(mid, d, r)) {
                rst = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return rst;
    }
};