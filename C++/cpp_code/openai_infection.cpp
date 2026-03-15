/*
给定一个 m x n 的二维矩阵，表示植物园。每个格子有三种可能状态：

"X" ：已经感染

"." ：健康植物

"I" ：免疫植物（不会被感染）

感染传播规则：

每一天，所有 已感染的植物 会感染 周围 8 个方向的邻居（包括对角线）。

如果健康植物 "." 接触到感染植物 "X"，第二天会变成 "X"。

"I" 永远不会被感染。

所有感染传播 同时发生。

问题分为四个部分：

第一问

只有 "X" 和 "."
问：多少天后系统达到平衡态（不再有新的感染发生）

第二问

加入 "I"（免疫植物）
问：多少天后达到平衡态

第三问

加入恢复机制：

每个 "X" 在感染 D 天后恢复

恢复后变为 "I"（免疫）

问：多少天后系统达到稳定

第四问

如果矩阵 非常大（例如 10⁹ × 10⁹），但感染点很少，如何优化？
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
#include <sstream>
#include <sstream>
using namespace std;

class Solution12 {
private:
    vector<pair<int, int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

public:
    int days_to_stable(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> bfs;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'X') {
                    bfs.push(pair<int, int>(i, j));
                }
            }
        }

        if (bfs.empty()) {
            return 0;
        }

        int rst = -1;
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; i++) {
                int cur_r = bfs.front().first;
                int cur_c = bfs.front().second;
                bfs.pop();

                for (auto& [diff_r, diff_c] : dirs) {
                    int new_r = cur_r + diff_r;
                    int new_c = cur_c + diff_c;
                    if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n) {
                        continue;
                    }

                    if (grid[new_r][new_c] != '.') {
                        continue;
                    }

                    grid[new_r][new_c] = 'X';
                    bfs.push({new_r, new_c});
                }
            }
            rst += 1;
        }
        return rst;
    }
};

class Solution3 {
private:
    vector<pair<int, int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

public:
    int days_to_stable(vector<vector<char>>& grid, int D) {
        int m = grid.size();
        int n = grid[0].size();

        queue<tuple<int, int, int>> infection;
        queue<tuple<int, int, int>> recovery;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'X') {
                    infection.push({i, j, 0});
                    recovery.push({i, j, D});
                }
            }
        }

        if (infection.empty()) {
            return 0;
        }

        int cur_day = 0;
        while (!infection.empty()) {
            cur_day += 1;
            // process recovery first
            while (!recovery.empty()) {
                auto [cur_r, cur_c, date] = recovery.front();
                if (date > cur_day) {
                    break;
                }

                recovery.pop();
                grid[cur_r][cur_c] = 'I';
            }

            int cur_size = infection.size();
            for (int i = 0; i < cur_size; i++) {
                auto [cur_r, cur_c, date] = infection.front();
                infection.pop();

                if (grid[cur_r][cur_c] != 'X') {
                    continue;
                }

                for (auto& [diff_r, diff_c] : dirs) {
                    int new_r = cur_r + diff_r;
                    int new_c = cur_c + diff_c;
                    if (new_r < 0 || new_r >= m || new_c < 0 || new_c >= n) {
                        continue;
                    }

                    if (grid[new_r][new_c] != '.') {
                        continue;
                    }

                    grid[new_r][new_c] = 'X';
                    infection.push({new_r, new_c, cur_day});
                    recovery.push({new_r, new_c, cur_day + D});
                }
            }
        }

        int rst = cur_day;
        while (!recovery.empty()) {
            auto [cur_r, cur_c, date] = recovery.front();
            recovery.pop();
            rst = max(rst, date);
        }
        return rst;
    }
};