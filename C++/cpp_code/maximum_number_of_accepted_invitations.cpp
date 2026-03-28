/*
https://leetcode.com/problems/maximum-number-of-accepted-invitations/description/
1820. Maximum Number of Accepted Invitations

There are m boys and n girls in a class attending an upcoming party.

You are given an m x n integer matrix grid, where grid[i][j] equals 0 or 1. If grid[i][j] == 1, then that means the ith
boy can invite the jth girl to the party. A boy can invite at most one girl, and a girl can accept at most one
invitation from a boy.

Return the maximum possible number of accepted invitations.



Example 1:

Input: grid = [[1,1,1],
               [1,0,1],
               [0,0,1]]
Output: 3
Explanation: The invitations are sent as follows:
- The 1st boy invites the 2nd girl.
- The 2nd boy invites the 1st girl.
- The 3rd boy invites the 3rd girl.
Example 2:

Input: grid = [[1,0,1,0],
               [1,0,0,0],
               [0,0,1,0],
               [1,1,1,0]]
Output: 3
Explanation: The invitations are sent as follows:
-The 1st boy invites the 3rd girl.
-The 2nd boy invites the 1st girl.
-The 3rd boy invites no one.
-The 4th boy invites the 2nd girl.


Constraints:

grid.length == m
grid[i].length == n
1 <= m, n <= 200
grid[i][j] is either 0 or 1.
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
private:
    bool find_partner(vector<vector<int>>& grid, vector<int>& partner, vector<int>& visited, int b) {
        int girl_count = grid[0].size();
        for (int g = 0; g < girl_count; ++g) {
            if (grid[b][g] == 1 && visited[g] == -1) {
                visited[g] = 1;
                if (partner[g] == -1 || find_partner(grid, partner, visited, partner[g])) {
                    partner[g] = b;
                    return true;
                }
            }
        }

        return false;
    }

public:
    int maximumInvitations(vector<vector<int>>& grid) {
        int boy_count = grid.size();
        int girl_count = grid[0].size();
        vector<int> partner(girl_count, -1);
        int rst = 0;
        for (int b = 0; b < boy_count; ++b) {
            vector<int> visited(girl_count, -1);
            if (find_partner(grid, partner, visited, b)) {
                rst += 1;
            }
        }
        return rst;
    }
};

/*
这其实是匈牙利算法（Hungarian algorithm），不是注释里写的 Hopcroft-Karp（那个更复杂，用 BFS 分层）。
核心思路是：对每个男生，尝试用 DFS 给他找一个女生配对。如果女生已经被别的男生占了，就递归地尝试给那个男生换一个女生。
用具体例子走一遍：
grid = [[1,1,1],
        [1,0,1],
        [0,0,1]]
第一轮：男生 0 找配对

看女生 0，没人占 → 配对成功。partner = [0, -1, -1]

第二轮：男生 1 找配对

看女生 0，已被男生 0 占了 → 递归：能给男生 0 换一个吗？

男生 0 看女生 1（女生 0 已 visited 跳过），没人占 → 男生 0 换到女生 1


女生 0 空出来了 → 男生 1 配对女生 0。partner = [1, 0, -1]

第三轮：男生 2 找配对

看女生 2，没人占 → 配对成功。partner = [1, 0, 2]

结果：3 对。
visited 数组的作用是防止同一轮 DFS 中重复访问同一个女生，避免死循环。每轮为一个新男生找配对时，visited 重新初始化。
dfsHelper 的逻辑就一句话：对于男生 b，遍历每个女生 g，如果能配对（grid[b][g]==1）且这轮没访问过，那么要么女生 g
没人占直接配，要么递归让占了女生 g 的男生去找别人。只要递归成功，就把 partner[g] = b，沿着递归链一路"换座位"。
时间复杂度 O(M * M * N)：M 个男生，每个男生的 DFS 最多遍历 M*N。这样为什么能确保找到最优的匹配树木8:39
PM关键在于：每次成功匹配一个男生，总匹配数严格 +1，且永远不会减少。 为什么不会减少？看 dfsHelper 的递归过程：当男生 1
想要女生 0，而女生 0 已被男生 0 占了，算法不是"抢走"配对，而是尝试给男生 0
找一个替代。只有替代成功了，才会换座位。如果整条递归链上找不到替代，男生 1 这轮就失败，现有配对不变。
所以每轮的结果只有两种：匹配数 +1，或者不变。永远不会 -1。
那为什么最终结果是最大匹配？这可以用增广路径的理论来理解。dfsHelper
本质上在找一条增广路径：一条从未匹配男生出发，沿着"未匹配边 → 已匹配边 → 未匹配边 →
..."交替走，最终到达一个未匹配女生的路径。找到后，把路径上所有边的匹配/未匹配状态翻转，匹配数就 +1。
二部图匹配的一个经典定理（Berge 定理）是：当且仅当不存在增广路径时，当前匹配是最大匹配。
算法对每个男生都尝试找增广路径，如果找不到就跳过。当所有男生都试过之后，不可能再存在增广路径了，所以结果就是最大匹配。
顺序会不会影响结果？不会。虽然不同的处理顺序可能产生不同的匹配方案，但最终匹配数量一定相同。因为只要还存在增广路径，后面的男生就能通过递归"重新安排"之前的配对来找到它。
 */
