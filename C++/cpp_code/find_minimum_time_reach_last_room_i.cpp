/*
https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/
3341. Find Minimum Time to Reach Last Room I
There is a dungeon with n x m rooms arranged as a grid.

You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds after which
the room opens and can be moved to. You start from the room (0, 0) at time t = 0 and can move to an adjacent room.
Moving between adjacent rooms takes exactly one second.

Return the minimum time to reach the room (n - 1, m - 1).

Two rooms are adjacent if they share a common wall, either horizontally or vertically.



Example 1:

Input: moveTime = [[0,4],[4,4]]

Output: 6

Explanation:

The minimum time required is 6 seconds.

At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in one second.
Example 2:

Input: moveTime = [[0,0,0],[0,0,0]]

Output: 3

Explanation:

The minimum time required is 3 seconds.

At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in one second.
At time t == 2, move from room (1, 1) to room (1, 2) in one second.
Example 3:

Input: moveTime = [[0,1],[1,2]]

Output: 3



Constraints:

2 <= n == moveTime.length <= 50
2 <= m == moveTime[i].length <= 50
0 <= moveTime[i][j] <= 109
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

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int m = moveTime.size();
        int n = moveTime[0].size();

        vector<vector<int>> min_time(m, vector<int>(n, INT_MAX));
        min_time[0][0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});

        vector<int> diff({0, 1, 0, -1, 0});
        while (!pq.empty()) {
            int cur_t = pq.top().first;
            int cur_r = pq.top().second / n;
            int cur_c = pq.top().second % n;
            pq.pop();

            if (cur_t > min_time[cur_r][cur_c]) {
                continue;
            }

            if (cur_r == m - 1 && cur_c == n - 1) {
                return cur_t;
            }

            for (int i = 0; i < 4; i++) {
                int next_r = cur_r + diff[i];
                int next_c = cur_c + diff[i + 1];
                if (next_r < 0 || next_r >= m || next_c < 0 || next_c >= n) {
                    continue;
                }

                int next_t = max(cur_t, moveTime[next_r][next_c]) + 1; // add the move time
                if (next_t < min_time[next_r][next_c]) {
                    min_time[next_r][next_c] = next_t;
                    pq.push({next_t, next_r * n + next_c});
                }
            }
        }
        return -1;
    }
};
