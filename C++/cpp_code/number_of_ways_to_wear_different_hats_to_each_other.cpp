/*
1434. Number of Ways to Wear Different Hats to Each Other
https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/

There are n people and 40 types of hats labeled from 1 to 40.
Given a list of list of integers hats, where hats[i] is a list of all hats preferred by the i-th person.
Return the number of ways that the n people wear different hats to each other.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: hats = [[3,4],[4,5],[5]]
Output: 1
Explanation: There is only one way to choose hats given the conditions.
First person choose hat 3, Second person choose hat 4 and last one hat 5.

Example 2:
Input: hats = [[3,5,1],[3,5]]
Output: 4
Explanation: There are 4 ways to choose hats
(3,5), (5,3), (1,3) and (1,5)

Example 3:
Input: hats = [[1,2,3,4],[1,2,3,4],[1,2,3,4],[1,2,3,4]]
Output: 24
Explanation: Each person can choose hats labeled from 1 to 4.
Number of Permutations of (1,2,3,4) = 24.

Example 4:
Input: hats = [[1,2,3],[2,3,5,6],[1,3,7,9],[1,8,9],[2,5,7]]
Output: 111

raints:
n == hats.length
1 <= n <= 10
1 <= hats[i].length <= 40
1 <= hats[i][j] <= 40
hats[i] contains a list of unique integers.
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
using namespace std;

class Solution {
private:
    int dfs(vector<vector<int>>& hatToPeople, vector<vector<int>>& dp, int& allPeopleAssigned,  int hat,  int currentAssignment) {
        if (currentAssignment == allPeopleAssigned) {
            return 1;
        }
        if (hat > 40) {
            return 0;
        }
        if (dp[hat][currentAssignment] != -1) {
            return dp[hat][currentAssignment];
        }

        dp[hat][currentAssignment] = dfs(hatToPeople, dp, allPeopleAssigned, hat + 1, currentAssignment);
        for (int people : hatToPeople[hat]) {
            if (((currentAssignment >> people) & 1) == 1) {
                continue;
            }
            dp[hat][currentAssignment] += dfs(hatToPeople, dp, allPeopleAssigned, hat + 1, currentAssignment | (1 << people));
            dp[hat][currentAssignment] %= (int)(1e9 + 7);
        }
        return dp[hat][currentAssignment];
    }
public:
    int numberWays(vector<vector<int>>& hats)  {
        int numOfPeople = static_cast<int>(hats.size());
        vector<vector<int>> hatToPeople(41, vector<int>());
        vector<vector<int>> dp(41, vector<int>((int)(pow(2, numOfPeople)), -1));

        for (int i = 0; i < numOfPeople; i++) {
            for (int hat : hats[i]) {
                hatToPeople[hat].push_back(i);
            }
        }
        int allPeopleAssigned = (1 << numOfPeople) - 1;
        return dfs(hatToPeople, dp, allPeopleAssigned, 1, 0);
    }
};
