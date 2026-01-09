/*
https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/description/
1359. Count All Valid Pickup and Delivery Options

Given n orders, each order consists of a pickup and a delivery service.

Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i).

Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 1
Output: 1
Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
Example 2:

Input: n = 2
Output: 6
Explanation: All possible orders:
(P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and (P2,D2,P1,D1).
This is an invalid order (P1,D2,P2,D1) because Pickup 2 is after of Delivery 2.
Example 3:

Input: n = 3
Output: 90


Constraints:

1 <= n <= 500
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
using namespace std;

/*
Intuition 1
Assume we have already n - 1 pairs, now we need to insert the nth pair.
To insert the first element, there are n * 2 - 1 chioces of position。
To insert the second element, there are n * 2 chioces of position。
So there are (n * 2 - 1) * n * 2 permutations.
Considering that delivery(i) is always after of pickup(i), we need to divide 2.
So it's (n * 2 - 1) * n.


Intuition 2
We consider the first element in all 2n elements.
The first must be a pickup, and we have n pickups as chioce.
Its pair can be any position in the rest of n*2-1 positions.
So it's (n * 2 - 1) * n.


Intuition 3
The total number of all permutation obviously eauqls to 2n!.
For each pair, the order is determined, so we need to divide by 2.
So the final result is (2n)!/(2^n)
 */
class Solution {
public:
    int countOrders(int n) {
        long long result = 1;
        long long mod = 1e9 + 7;
        for (int i = 1; i <= n; i++) {
            result = result * (2 * i - 1) * i % mod;
        }
        return result;
    }
};