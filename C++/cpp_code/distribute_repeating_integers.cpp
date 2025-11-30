/*
1655. Distribute Repeating Integers
https://leetcode.com/problems/distribute-repeating-integers/

You are given an array of n integers, nums,
where there are at most 50 unique values in the array.
You are also given an array of m customer order quantities, quantity,
where quantity[i] is the amount of integers the ith customer ordered.
Determine if it is possible to distribute nums such that:

The ith customer gets exactly quantity[i] integers,
The integers the ith customer gets are all equal, and
Every customer is satisfied.
Return true if it is possible to distribute nums according to the above conditions.

Example 1:
Input: nums = [1,2,3,4], quantity = [2]
Output: false
Explanation: The 0th customer cannot be given two different integers.

Example 2:
Input: nums = [1,2,3,3], quantity = [2]
Output: true
Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.

Example 3:
Input: nums = [1,1,2,2], quantity = [2,2]
Output: true
Explanation: The 0th customer is given [1,1], and the 1st customer is given [2,2].

Example 4:
Input: nums = [1,1,2,3], quantity = [2,2]
Output: false
Explanation: Although the 0th customer could be given [1,1], the 1st customer cannot be satisfied.

Example 5:
Input: nums = [1,1,1,1,1], quantity = [2,3]
Output: true
Explanation: The 0th customer is given [1,1], and the 1st customer is given [1,1,1].

Constraints:
n == nums.length
1 <= n <= 105
1 <= nums[i] <= 1000
m == quantity.length
1 <= m <= 10
1 <= quantity[i] <= 105
There are at most 50 unique values in nums.
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
#include <cfloat>
#include <climits>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;
/*
First calculate the count of each type of value in nums and store in vector a

Now idea is to iterate over a and try out each possible scenario of assigning this to different quantity orders i.e b.
In particular the possibilities are to either use current element from a or skip it.

When considering the first option,
we need to find a subset of b over which we can distribute the current element from a .
Using bitmask we can find all such subsets.

Since m <= 10 (i.e size of b), there can be only 1024 subsets, we iterate over all of them.
*/
class Solution {
public:
    int m, n;
    vector<int> a;
    vector<int> b;
    vector<vector<int>> dp;

    bool solve(int idx, int mask) {
        if (mask == (1 << m) - 1)
            return 1;

        if (idx == n)
            return 0;

        if (dp[idx][mask] != -1)
            return dp[idx][mask];

        bool ans = solve(idx + 1, mask);

        for (int i = 0; i < (1 << m); i++) {
            if (mask != (mask & (i)))
                continue;
            int nm = mask;
            int sum = 0;
            for (int j = 0; j < m; j++) {
                if (mask & (1 << j))
                    continue;
                if (i & (1 << j)) {
                    sum += b[j];
                    nm |= (1 << j);
                }
            }
            if (sum <= a[idx])
                ans |= solve(idx + 1, nm);
        }

        return dp[idx][mask] = ans;
    }

    bool canDistribute(vector<int>& nums, vector<int>& b) {
        unordered_map<int, int> mp;
        for (int x : nums) {
            mp[x] += 1;
        }
        for (auto p : mp)
            a.push_back(p.second);

        this->b = b;
        this->m = b.size();
        this->n = a.size();
        dp.clear();
        dp.resize(n, vector<int>((1 << m), -1));

        return solve(0, 0);
    }
};