/*
1395. Count Number of Teams
https://leetcode.com/problems/count-number-of-teams/

There are n soldiers standing in a line.
Each soldier is assigned a unique rating value.

You have to form a team of 3 soldiers amongst them under the following rules:
Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
A team is valid if:
(rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k])
where (0 <= i < j < k < n).

Return the number of teams you can form given the conditions.
(soldiers can be part of multiple teams).

Example 1:
Input: rating = [2,5,3,4,1]
Output: 3
Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).

Example 2:
Input: rating = [2,1,3]
Output: 0
Explanation: We can't form any team given the conditions.

Example 3:
Input: rating = [1,2,3,4]
Output: 4

Constraints:
n == rating.length
1 <= n <= 200
1 <= rating[i] <= 10^5
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
#include <numeric>
using namespace std;

class Solution {
public:
    int numTeams(vector<int> &rating) {
        int res = 0;
        for (auto i = 1; i < rating.size() - 1; ++i) {
            int less[2] = {};
            int greater[2] = {};
            for (auto j = 0; j < rating.size(); ++j) {
                if (rating[i] < rating[j]) {
                    ++less[j > i];
                }
                if (rating[i] > rating[j]) {
                    ++greater[j > i];
                }
            }
            res += less[0] * greater[1] + greater[0] * less[1];
        }
        return res;
    }
};