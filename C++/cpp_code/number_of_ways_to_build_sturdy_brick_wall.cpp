/*
https://leetcode.com/problems/number-of-ways-to-build-sturdy-brick-wall/description/
2184. Number of Ways to Build Sturdy Brick Wall

You are given integers height and width which specify the dimensions of a brick wall you are building. You are also
given a 0-indexed array of unique integers bricks, where the ith brick has a height of 1 and a width of bricks[i]. You
have an infinite supply of each type of brick and bricks may not be rotated.

Each row in the wall must be exactly width units long. For the wall to be sturdy, adjacent rows in the wall should not
join bricks at the same location, except at the ends of the wall.

Return the number of ways to build a sturdy wall. Since the answer may be very large, return it modulo 109 + 7.



Example 1:


Input: height = 2, width = 3, bricks = [1,2]
Output: 2
Explanation:
The first two walls in the diagram show the only two ways to build a sturdy brick wall.
Note that the third wall in the diagram is not sturdy because adjacent rows join bricks 2 units from the left.
Example 2:

Input: height = 1, width = 1, bricks = [5]
Output: 0
Explanation:
There are no ways to build a sturdy wall because the only type of brick we have is longer than the width of the wall.


Constraints:

1 <= height <= 100
1 <= width <= 10
1 <= bricks.length <= 10
1 <= bricks[i] <= 10
All the values of bricks are unique.
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

// dfs + dp
class Solution {
private:
    void dfs(vector<vector<int>>& valid_row, vector<int>& cur_row, int width, vector<int>& brick, int cur_width) {
        if (cur_width == width) {
            valid_row.push_back(cur_row);
            return;
        }

        if (cur_width > width) {
            return;
        }

        for (int b : brick) {
            cur_row.push_back(b);
            dfs(valid_row, cur_row, width, brick, cur_width + b);
            cur_row.pop_back();
        }
    }

    bool can_be_adjacent(vector<int>& a, vector<int>& b, int width) {
        int sum_a = 0;
        int sum_b = 0;
        int i = 0;
        int j = 0;
        int cnt_a = a.size();
        int cnt_b = b.size();
        while (i < cnt_a && j < cnt_b) {
            if (sum_a < sum_b) {
                sum_a += a[i];
                i += 1;
            } else {
                sum_b += b[j];
                j += 1;
            }

            if (sum_a == sum_b && sum_a < width) {
                return false;
            }
        }
        return true;
    }

    int mod = 1e9+7;
public:
    int buildWall(int height, int width, vector<int>& bricks) {
        vector<vector<int>> valid_row;
        vector<int> cur_row;
        dfs(valid_row, cur_row, width, bricks, 0);

        int cnt = valid_row.size();
        vector<vector<int>> adj_row_idx(cnt, vector<int>());
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < cnt; j++) {
                if (can_be_adjacent(valid_row[i], valid_row[j], width)) {
                    adj_row_idx[i].push_back(j); // it is possible we can put the same row next to itself
                    // adj_row_idx[j].push_back(i);
                }
            }
        }

        vector<int> dp(cnt, 1);
        for (int h = 1; h < height; h++) {
            vector<int> dp_new(cnt, 0);
            for (int i = 0; i < cnt; i++) {
                for (int adj : adj_row_idx[i]) {
                    dp_new[i] = (dp_new[i] + dp[adj]) % mod;
                }
            }
            dp = dp_new;
        }

        int rst = 0;
        for (int i = 0; i < cnt; i++) {
            rst = (rst + dp[i]) % mod;
        }
        return rst;
    }
};

int main() {
    Solution s;
    vector<int> a({1,2,3});
    s.buildWall(3, 5, a);
}