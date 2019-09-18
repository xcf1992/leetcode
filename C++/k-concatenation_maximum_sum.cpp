/*
1191. K-Concatenation Maximum Sum
https://leetcode.com/problems/k-concatenation-maximum-sum/

Given an integer array arr and an integer k,
modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array.
Note that the length of the sub-array can be 0 and its sum in that case is 0.
As the answer can be very large, return the answer modulo 10^9 + 7.

Example 1:
Input: arr = [1,2], k = 3
Output: 9

Example 2:
Input: arr = [1,-2,1], k = 5
Output: 2

Example 3:
Input: arr = [-1,-2], k = 7
Output: 0

Constraints:
1 <= arr.length <= 10^5
1 <= k <= 10^5
-10^4 <= arr[i] <= 10^4
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    int mod = 1e9 + 7;
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int n = arr.size();
        long total = arr[0];
        int preMax = arr[0];
        int sufSum = arr[n - 1];
        int sufMax = arr[n - 1];
        int maxSum = arr[0];
        int curMax = arr[0];
        int curMin = arr[0];
        int minSum = arr[0];
        for (int i = 1; i < arr.size(); ++i) {
            curMax = max(curMax + arr[i], arr[i]) % mod;
            maxSum = max(maxSum, curMax);
            total = (total + arr[i]) % mod;
            preMax = max(preMax, (int)total);

            curMin = min(curMin + arr[i], arr[i]) % mod;
            minSum = min(minSum, curMin);

            int j = n - 1 - i;
            sufSum = (sufSum + arr[j]) % mod;
            sufMax = max(sufMax, sufSum);
        }

        if (maxSum <= 0) {
            return 0;
        }
        if (k == 1) {
            return maxSum % mod;
        }
        if (total < 0) {
            total = 0;
        }
        total = total * (k - 2) % mod;
        return max((int)total % mod + preMax + sufMax, maxSum) % mod;
    }
};
