/*
1248. Count Number of Nice Subarrays
https://leetcode.com/problems/count-number-of-nice-subarrays/

Given an array of integers nums and an integer k.
A subarray is called nice if there are k odd numbers on it.
Return the number of nice sub-arrays.

Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16

Constraints:
1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length
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
// 992. Subarrays with K Different Integers
// atMost(K) - atMost(K - 1)
class Solution {
private:
    int at_most_k_odd_num(vector<int>& A, int k) {
        int res = 0;
        int i = 0;
        int n = A.size();
        for (int j = 0; j < n; j++) {
            k -= A[j] % 2;
            while (k < 0) {
                k += A[i] % 2;
                i += 1;
            }
            res += j - i + 1;
        }
        return res;
    }

public:
    int numberOfSubarrays(vector<int>& A, int k) {
        return at_most_k_odd_num(A, k) - at_most_k_odd_num(A, k - 1);
    }
};