/*
1359. Count All Valid Pickup and Delivery Options
https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/

Given n orders,
each order consist in pickup and delivery services.

Count all valid pickup/delivery possible sequences
such that delivery(i) is always after of pickup(i).

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
package main

import (
	"fmt"
)

/*
Assume we have already n - 1 pairs, now we need to insert the nth pair.
To insert the first element, there are n * 2 - 1 chioces of position。
To insert the second element, there are n * 2 chioces of position。
So there are (n * 2 - 1) * n * 2 permutations.
Considering that delivery(i) is always after of pickup(i), we need to divide 2.
So it's (n * 2 - 1) * n.
*/
func countOrders(n int) int {
	var result int64 = 1;
	var mod int64 = 1e9 + 7
    for i := int64(1); i <= int64(n); i++ {
		result = result * (i * 2 - 1) * i % mod
	}
    return int(result)
}
