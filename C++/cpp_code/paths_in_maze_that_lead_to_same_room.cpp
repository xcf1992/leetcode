/*
https://leetcode.com/problems/paths-in-maze-that-lead-to-same-room/description/
2077. Paths in Maze That Lead to Same Room

A maze consists of n rooms numbered from 1 to n, and some rooms are connected by corridors. You are given a 2D integer
array corridors where corridors[i] = [room1i, room2i] indicates that there is a corridor connecting room1i and room2i,
allowing a person in the maze to go from room1i to room2i and vice versa.

The designer of the maze wants to know how confusing the maze is. The confusion score of the maze is the number of
different cycles of length 3.

For example, 1 → 2 → 3 → 1 is a cycle of length 3, but 1 → 2 → 3 → 4 and 1 → 2 → 3 → 2 → 1 are not.
Two cycles are considered to be different if one or more of the rooms visited in the first cycle is not in the second
cycle.

Return the confusion score of the maze.



Example 1:


Input: n = 5, corridors = [[1,2],[5,2],[4,1],[2,4],[3,1],[3,4]]
Output: 2
Explanation:
One cycle of length 3 is 4 → 1 → 3 → 4, denoted in red.
Note that this is the same cycle as 3 → 4 → 1 → 3 or 1 → 3 → 4 → 1 because the rooms are the same.
Another cycle of length 3 is 1 → 2 → 4 → 1, denoted in blue.
Thus, there are two different cycles of length 3.
Example 2:


Input: n = 4, corridors = [[1,2],[3,4]]
Output: 0
Explanation:
There are no cycles of length 3.


Constraints:

2 <= n <= 1000
1 <= corridors.length <= 5 * 104
corridors[i].length == 2
1 <= room1i, room2i <= n
room1i != room2i
There are no duplicate corridors.
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
/*
The trick here is always traverse in a single monotonic direction, i.e., either from small to large or vice versa.

Then when we count up to 3 nodes in a single path, in order to know the next node could be the starting point, we need
to check if there is a path leading to it from the last node of the 3. That leads to the second trick - use HashSet
instead of List when building the graph from edges at the beginning.
 */
class Solution {
private:
    void dfs(unordered_map<int, unordered_set<int>>& adj, int& rst, int cur, int start, int cnt) {
        if (cnt == 3) {
            if (adj[cur].find(start) != adj[cur].end()) {
                rst += 1;
            }
            return;
        }

        for (int nxt : adj[cur]) {
            if (nxt < cur) {
                continue;
            }
            dfs(adj, rst, nxt, start, cnt + 1);
        }
    }

public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        unordered_map<int, unordered_set<int>> adj;
        for (vector<int>& co : corridors) {
            adj[co[0]].insert(co[1]);
            adj[co[1]].insert(co[0]);
        }

        int rst = 0;
        for (int i = 0; i < n; i++) {
            dfs(adj, rst, i, i, 1);
        }
        return rst;
    }
};
