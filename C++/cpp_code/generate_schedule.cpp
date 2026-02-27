/*
https://leetcode.com/problems/generate-schedule/description/
3680. Generate Schedule

You are given an integer n representing n teams. You are asked to generate a schedule such that:

Each team plays every other team exactly twice: once at home and once away.
There is exactly one match per day; the schedule is a list of consecutive days and schedule[i] is the match on day i.
No team plays on consecutive days.
Return a 2D integer array schedule, where schedule[i][0] represents the home team and schedule[i][1] represents the away
team. If multiple schedules meet the conditions, return any one of them.

If no schedule exists that meets the conditions, return an empty array.



Example 1:

Input: n = 3

Output: []

Explanation:

​​​​​​​Since each team plays every other team exactly twice, a total of 6 matches need to be played:
[0,1],[0,2],[1,2],[1,0],[2,0],[2,1].

It's not possible to create a schedule without at least one team playing consecutive days.

Example 2:

Input: n = 5

Output:
[[0,1],[2,3],[0,4],[1,2],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[2,0],[3,1],[4,0],[2,1],[4,3],[1,0],[3,2],[4,1],[3,0],[4,2]]

Explanation:

Since each team plays every other team exactly twice, a total of 20 matches need to be played.

The output shows one of the schedules that meet the conditions. No team plays on consecutive days.



Constraints:

2 <= n <= 50​​​​​​​
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
using namespace std;

class Solution {
public:
    vector<vector<int>> generateSchedule(int n) {
        if (n <= 4) {
            return {};  // Not possible
        }

        if (n == 5) {
            return {{0, 1}, {2, 3}, {0, 4}, {1, 2}, {3, 4}, {0, 2}, {1, 3}, {2, 4}, {0, 3}, {1, 4},
                    {2, 0}, {3, 1}, {4, 0}, {2, 1}, {4, 3}, {1, 0}, {3, 2}, {4, 1}, {3, 0}, {4, 2}};  // Base case
        }

        int half = n / 2;
        int oneRound = (n * (n - 1)) / 2;
        vector<int> first, second;
        // Divide teams into two groups
        for (int i = 0; i < half; i++) {
            first.push_back(i);
        }
        for (int i = half; i < n; i++) {
            second.push_back(i);
        }

        // Group A vs Group B matches
        vector<vector<int>> rst;
        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                if (i == 0 && n % 2 != 0) {
                    rst.push_back({first[(j + 1) % half], n - 1});  // For odd case ( first column )
                }

                rst.push_back({first[j], second[(j + i) % half]});

                if (i == half - 1 && n % 2 != 0) {
                    rst.push_back({second[(j + 1) % half], n - 1});  // For odd case ( last column )
                }
            }
        }

        // Matches within the same group
        for (int i = 0; i < half; i++) {  // Matches in same group
            for (int j = i + 1; j < half; j++) {
                rst.push_back({first[i], first[j]});
                rst.push_back({second[i], second[j]});
            }
        }

        // Reverse home/away for the second half of the schedule
        for (int i = 0; i < oneRound; i++) {
            rst.push_back({rst[i][1], rst[i][0]});
        }
        return rst;
    }
};