/*
https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/description/
3342. Find Minimum Time to Reach Last Room II

There is a dungeon with n x m rooms arranged as a grid.

You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you
can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving
between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.

Return the minimum time to reach the room (n - 1, m - 1).

Two rooms are adjacent if they share a common wall, either horizontally or vertically.



Example 1:

Input: moveTime = [[0,4],[4,4]]

Output: 7

Explanation:

The minimum time required is 7 seconds.

At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.
Example 2:

Input: moveTime = [[0,0,0,0],[0,0,0,0]]

Output: 6

Explanation:

The minimum time required is 6 seconds.

At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in two seconds.
At time t == 3, move from room (1, 1) to room (1, 2) in one second.
At time t == 4, move from room (1, 2) to room (1, 3) in two seconds.
Example 3:

Input: moveTime = [[0,1],[1,2]]

Output: 4



Constraints:

2 <= n == moveTime.length <= 750
2 <= m == moveTime[i].length <= 750
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
        vector<vector<vector<int>>> min_dist(m, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
        min_dist[0][0][0] = 0;

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({0, 0, 0});

        vector<int> diff({0, 1, 0, -1, 0});
        while (!pq.empty()) {
            auto [cur_t, cur_pos, step] = pq.top();
            pq.pop();

            int cur_r = cur_pos / n;
            int cur_c = cur_pos % n;

            if (cur_t > min_dist[cur_r][cur_c][step]) {
                continue;
            }

            if (cur_r == m - 1 && cur_c == n - 1) {
                return cur_t;
            }

            int cost = (step == 0) ? 1 : 2;
            step = 1 - step;
            for (int i = 0; i < 4; i++) {
                int next_r = cur_r + diff[i];
                int next_c = cur_c + diff[i + 1];
                if (next_r < 0 || next_r >= m || next_c < 0 || next_c >= n) {
                    continue;
                }

                int next_t = max(cur_t, moveTime[next_r][next_c]) + cost;
                if (next_t < min_dist[next_r][next_c][step]) {
                    min_dist[next_r][next_c][step] = next_t;
                    pq.push({next_t, next_r * n + next_c, step});
                }
            }
        }
        return -1;
    }
};
