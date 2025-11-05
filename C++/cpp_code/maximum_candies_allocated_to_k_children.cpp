/*
https://leetcode.com/problems/maximum-candies-allocated-to-k-children/
2226. Maximum Candies Allocated to K Children

You are given a 0-indexed integer array candies. Each element in the array denotes a pile of candies of size candies[i]. You can divide each pile into any number of sub piles, but you cannot merge two piles together.

You are also given an integer k. You should allocate piles of candies to k children such that each child gets the same number of candies. Each child can be allocated candies from only one pile of candies and some piles of candies may go unused.

Return the maximum number of candies each child can get.



Example 1:

Input: candies = [5,8,6], k = 3
Output: 5
Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and candies[2] into 2 piles of size 5 and 1. We now have five piles of candies of sizes 5, 5, 3, 5, and 1. We can allocate the 3 piles of size 5 to 3 children. It can be proven that each child cannot receive more than 5 candies.
Example 2:

Input: candies = [2,5], k = 11
Output: 0
Explanation: There are 11 children but only 7 candies in total, so it is impossible to ensure each child receives at least one candy. Thus, each child gets no candy and the answer is 0.


Constraints:

1 <= candies.length <= 105
1 <= candies[i] <= 107
1 <= k <= 1012
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
    bool can_allocate(vector<int> &candies, long long k, int candy_cnt) {
        long long cnt = 0;
        for (long long pile_cnt: candies) {
            cnt += pile_cnt / candy_cnt;
            if (cnt >= k) {
                return true;
            }
        }
        return false;
    }

public:
    int maximumCandies(vector<int> &candies, long long k) {
        int n = candies.size();
        long long max_cnt = 0;
        long long total_cnt = 0;
        for (int pile_cnt: candies) {
            if (pile_cnt > max_cnt) {
                max_cnt = pile_cnt;
            }
            total_cnt += pile_cnt;
        }

        if (total_cnt < k) {
            return 0;
        }

        int rst = 1;
        int left = 1;
        int right = max_cnt + 1;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (can_allocate(candies, k, mid)) {
                rst = mid;
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return rst;
    }
};