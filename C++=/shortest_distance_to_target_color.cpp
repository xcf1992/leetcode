/*
1182. Shortest Distance to Target Color
https://leetcode.com/problems/shortest-distance-to-target-color/

You are given an array colors,
in which there are three colors: 1, 2 and 3.

You are also given some queries.
Each query consists of two integers i and c,
return the shortest distance between the given index i and the target color c.
If there is no solution return -1.

Example 1:
Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
Output: [3,0,3]
Explanation:
The nearest 3 from index 1 is at index 4 (3 steps away).
The nearest 2 from index 2 is at index 2 itself (0 steps away).
The nearest 1 from index 6 is at index 3 (3 steps away).

Example 2:
Input: colors = [1,2], queries = [[0,3]]
Output: [-1]
Explanation: There is no 3 in the array.

Constraints:
1 <= colors.length <= 5*10^4
1 <= colors[i] <= 3
1 <= queries.length <= 5*10^4
queries[i].length == 2
0 <= queries[i][0] < colors.length
1 <= queries[i][1] <= 3
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        vector<vector<int>> left(4, vector<int>(n, INT_MAX));
        vector<vector<int>> right(4, vector<int>(n, INT_MAX));

        left[colors[0]][0] = 0;
        right[colors[n - 1]][n - 1] = 0;
        for (int i = 1; i < n; ++i) {
            int clr = colors[i];
            left[1][i] = clr == 1 ? 0 : (left[1][i - 1] == INT_MAX ? INT_MAX : left[1][i - 1] + 1);
            left[2][i] = clr == 2 ? 0 : (left[2][i - 1] == INT_MAX ? INT_MAX : left[2][i - 1] + 1);
            left[3][i] = clr == 3 ? 0 : (left[3][i - 1] == INT_MAX ? INT_MAX : left[3][i - 1] + 1);

            int j = n - 1 - i;
            clr = colors[j];
            right[1][j] = clr == 1 ? 0 : (right[1][j + 1] == INT_MAX ? INT_MAX : right[1][j + 1] + 1);
            right[2][j] = clr == 2 ? 0 : (right[2][j + 1] == INT_MAX ? INT_MAX : right[2][j + 1] + 1);
            right[3][j] = clr == 3 ? 0 : (right[3][j + 1] == INT_MAX ? INT_MAX : right[3][j + 1] + 1);
        }

        int len = queries.size();
        vector<int> result(len, -1);
        for (int i = 0; i < len; ++i) {
            int idx = queries[i][0];
            int clr = queries[i][1];
            result[i] = min(left[clr][idx], right[clr][idx]);
            result[i] = result[i] == INT_MAX ? -1 : result[i];
        }
        return result;
    }
};

class Solution1 { // O(logn) 50%
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        unordered_map<int, vector<int>> pos;
        for (int i = 0; i < n; ++i) {
            pos[colors[i]].push_back(i);
        }

        int len = queries.size();
        vector<int> result(len, INT_MAX);
        for (int i = 0; i < len; ++i) {
            int idx = queries[i][0];
            int clr = queries[i][1];
            if (pos.find(clr) == pos.end()) {
                result[i] = -1;
                continue;
            }

            auto it = lower_bound(pos[clr].begin(), pos[clr].end(), idx);
            if (it != pos[clr].end()) {
                result[i] = (*it) - idx;
            }
            else {
                result[i] = idx - pos[clr].back();
                continue;
            }

            if (it != pos[clr].begin()) {
                result[i] = min(result[i], idx - (*prev(it)));
            }
        }
        return result;
    }
};
