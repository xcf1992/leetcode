/*
https://leetcode.com/problems/detonate-the-maximum-bombs/description/
2101. Detonate the Maximum Bombs

You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in
the shape of a circle with the center as the location of the bomb.

The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the
X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.

You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range.
These bombs will further detonate the bombs that lie in their ranges.

Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only
one bomb.



Example 1:


Input: bombs = [[2,1,3],[6,1,4]]
Output: 2
Explanation:
The above figure shows the positions and ranges of the 2 bombs.
If we detonate the left bomb, the right bomb will not be affected.
But if we detonate the right bomb, both bombs will be detonated.
So the maximum bombs that can be detonated is max(1, 2) = 2.
Example 2:


Input: bombs = [[1,1,5],[10,10,5]]
Output: 1
Explanation:
Detonating either bomb will not detonate the other bomb, so the maximum number of bombs that can be detonated is 1.
Example 3:


Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
Output: 5
Explanation:
The best bomb to detonate is bomb 0 because:
- Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb 0.
- Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
- Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.
Thus all 5 bombs are detonated.


Constraints:

1 <= bombs.length <= 100
bombs[i].length == 3
1 <= xi, yi, ri <= 105
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

/*
We can represent bombs using a directed graph - when a bomb i can detonate bomb j, there is an edge from i to j. Note
that the opposite may not be true.

We generate this graph (al), and, starting from each node, we run BFS (or DFS) and find out how many nodes we can reach.
 */
class Solution {
    bool affected(int i, int j, vector<vector<int>>& bombs) {
        long long xi = bombs[i][0];
        long long yi = bombs[i][1];
        long long ri = bombs[i][2];
        long long xj = bombs[j][0];
        long long yj = bombs[j][1];
        return ri * ri >= (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);
    }

public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>> detonated(n, vector<int>());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!affected(i, j, bombs)) {
                    continue;
                }
                detonated[i].push_back(j);
            }
        }

        vector<int> cnt(n, 0);
        int rst = 0;
        for (int i = 0; i < n && rst < n; i++) {
            queue<int> bfs;
            bfs.push(i);
            unordered_set<int> visited;
            visited.insert(i);
            while (!bfs.empty()) {
                int cur_size = bfs.size();
                for (int j = 0; j < cur_size; j++) {
                    int cur = bfs.front();
                    bfs.pop();

                    for (int next : detonated[cur]) {
                        if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            bfs.push(next);
                        }
                    }
                }
            }

            rst = max(rst, (int)visited.size());
        }
        return rst;
    }
};