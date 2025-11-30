/*
1390. Four Divisors
https://leetcode.com/problems/four-divisors/

Given an integer array nums,
return the sum of divisors of the integers in that array that have exactly four divisors.

If there is no such integer in the array, return 0.

Example 1:
Input: nums = [21,4,7]
Output: 32
Explanation:
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.

Constraints:
1 <= nums.length <= 10^4
1 <= nums[i] <= 10^5
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
#include "extra_data_types.hpp"
using namespace std;
/*
Any number n greater than 1 already have two divisors: 1 and n. So, for a number to have exact 4 divisors, there should
be only one pair of divisors d and n / d.

Catch: if d == n / d, the number has 3 divisors, not four.
*/
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int sum = 0;
        for (int n : nums) {
            int last_d = 0;
            for (int d = 2; d * d <= n; ++d) {
                if (n % d == 0) {
                    if (last_d == 0)
                        last_d = d;
                    else {
                        last_d = 0;
                        break;
                    }
                }
            }
            if (last_d > 0 && last_d != n / last_d) {
                sum += 1 + n + last_d + n / last_d;
            }
        }
        return sum;
    }
};