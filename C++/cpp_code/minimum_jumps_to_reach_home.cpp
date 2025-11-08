/*
1654. Minimum Jumps to Reach Home
https://leetcode.com/problems/minimum-jumps-to-reach-home/

A certain bug's home is on the x-axis at position x.
Help them get there from position 0.

The bug jumps according to the following rules:
It can jump exactly a positions forward (to the right).
It can jump exactly b positions backward (to the left).
It cannot jump backward twice in a row.
It cannot jump to any forbidden positions.
The bug may jump forward beyond its home,
but it cannot jump to positions numbered with negative integers.

Given an array of integers forbidden,
where forbidden[i] means that the bug cannot jump to the position forbidden[i],
and integers a, b, and x,
return the minimum number of jumps needed for the bug to reach its home.
If there is no possible sequence of jumps that lands the bug on position x, return -1.

Example 1:
Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
Output: 3
Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.

Example 2:
Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
Output: -1

Example 3:
Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
Output: 2
Explanation: One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug home.

Constraints:
1 <= forbidden.length <= 1000
1 <= a, b, forbidden[i] <= 2000
0 <= x <= 2000
All the elements in forbidden are distinct.
Position x is not forbidden.
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
#include <stdio.h>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        unordered_set<int> forbi(forbidden.begin(), forbidden.end());
        // visited array has two states:
        // visited[0][i] means the ith cell was reached from its left hand side jumping forward,
        // visited[1][i] means the ith cell was reached from its right hand side jumping backward.
        vector<vector<int>> visited(2, vector<int>(6000, 0));
        visited[0][0] = 1;
        visited[1][0] = 1;
        // true means your last jump was backward jumping, you cannot jump backward in current step.
        // false, otherwise.
        queue<pair<int, bool>> bfs;
        bfs.push({0, false});

        int rst = 0;
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            while (cur_size > 0) {
                cur_size -= 1;
                int cur = bfs.front().first;
                bool flag = bfs.front().second;
                bfs.pop();

                if (cur == x) {
                    return rst;
                }

                int forward = cur + a;
                int backward = cur - b;
                if (forward < 6000 && visited[0][forward] == 0 && !forbi.count(forward)) {
                    bfs.push({forward, false});
                    visited[0][forward] = 1;
                }

                if (backward >= 0 && visited[1][backward] == 0 && !forbi.count(backward) && !flag) {
                    bfs.push({backward, true});
                    visited[1][backward] = 1;
                }
            }
            rst += 1;
        }
        return -1;
    }
};
