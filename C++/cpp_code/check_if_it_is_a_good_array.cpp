/*
1250. Check If It Is a Good Array
https://leetcode.com/problems/check-if-it-is-a-good-array/

Given an array nums of positive integers.
Your task is to select some subset of nums,
multiply each element by an integer and add all these numbers.
The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.

Return True if the array is good otherwise return False.

Example 1:
Input: nums = [12,5,7,23]
Output: true
Explanation: Pick numbers 5 and 7.
5*3 + 7*(-2) = 1

Example 2:
Input: nums = [29,6,10]
Output: true
Explanation: Pick numbers 29, 6 and 10.
29*1 + 6*(-3) + 10*(-1) = 1

Example 3:
Input: nums = [3,6]
Output: false

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
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
using namespace std;
/*
Intuition
This problem is realated a Chinese theorem:
Chinese remainder theorem, created in 5th centry.
Also well known as Hanson Counting (韩信点兵).

Explanation
If a % x = 0 and b % x = 0,
appareantly we have (pa + qb) % x == 0
If x > 1, making it impossible pa + qb = 1.

Complexity
Of course youcan return true as soon as gcd = 1
I take gcd calculate as O(1).

Time O(N)
Space O(1)

The solution it self is easy:
The result is true, if and only if there are two numbers in the array that are mutually prime.

The hard part is, why?
proof https://leetcode.com/problems/check-if-it-is-a-good-array/discuss/419529/Why-GCD-Look-proof-here!Python2-1-line
*/

class Solution {
private:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

public:
    bool isGoodArray(vector<int> &nums) {
        int result = nums[0];
        for (int num: nums) {
            result = gcd(result, num);
        }
        return result == 1;
    }
};