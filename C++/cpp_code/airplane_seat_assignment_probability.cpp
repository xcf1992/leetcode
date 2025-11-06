/*
1227. Airplane Seat Assignment Probability
https://leetcode.com/problems/airplane-seat-assignment-probability/

n passengers board an airplane with exactly n seats.
The first passenger has lost the ticket and picks a seat randomly.
But after that, the rest of passengers will:

Take their own seat if it is still available,
Pick other seats randomly when they find their seat occupied
What is the probability that the n-th person can get his own seat?

Example 1:
Input: n = 1
Output: 1.00000
Explanation: The first person can only get the first seat.

Example 2:
Input: n = 2
Output: 0.50000
Explanation: The second person has a probability of 0.5 to get the second seat (when first person gets the first seat).

Constraints:
1 <= n <= 10^5
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;
/*
The main idea is:
The probability of "nth person can get the nth seat" can be divided into 2 parts:

The first person gets the first seat, then the nth person is guaranteed to get the nth seat. The probability of this
situation is 1/n. The first person gets any other seat except the first one and the nth one, then the problem shrinks
into a subproblem with size n-1. The probability of this situation is (n-2)/n. Therefore, P(N) = 1/n + (n-2)/n * P(N -
1)
*/
class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        return n == 1 ? 1.0 : 0.5;
    }
};