/*
1168. Optimize Water Distribution in a Village

There are n houses in a village.
We want to supply water for all the houses by building wells and laying pipes.

For each house i, we can either build a well inside it directly with cost wells[i],
or pipe in water from another well to it.
The costs to lay pipes between houses are given by the array pipes,
where each pipes[i] = [house1, house2, cost] represents the cost to connect house1 and house2 together using a pipe.
Connections are bidirectional.

Find the minimum total cost to supply water to all houses.

Example 1:
Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
Output: 3
Explanation:
The image shows the costs of connecting houses using pipes.
The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so
the total cost is 3.

Constraints:
1 <= n <= 10000
wells.length == n
0 <= wells[i] <= 10^5
1 <= pipes.length <= 10000
1 <= pipes[i][0], pipes[i][1] <= n
0 <= pipes[i][2] <= 10^5
pipes[i][0] != pipes[i][1]
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>

#include <numeric>
using namespace std;
/*
What if we model this problem as a graph problem?
A house is a node and a pipe is a weighted edge.
How to represent building wells in the graph model?
Add a virtual node, connect it to houses with edges weighted by the costs to build wells in these houses.
The problem is now reduced to a Minimum Spanning Tree problem.
*/
class Solution {
private:
    int find(int p, vector<int>& parent) {
        if (parent[p] != p) {
            parent[p] = find(parent[p], parent);
        }
        return parent[p];
    }

public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        vector<int> parent(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            pipes.push_back(
                    {0, i, wells[i - 1]});  // 0 is the virtual node we used to represent build well in house i - 1
        }

        sort(pipes.begin(), pipes.end(), [](vector<int>& p1, vector<int>& p2) { return p1[2] < p2[2]; });

        int result = 0;
        int count = n;
        for (vector<int>& pipe : pipes) {
            if (count <= 0) {
                break;
            }
            int p1 = find(pipe[0], parent);
            int p2 = find(pipe[1], parent);
            if (p1 != p2) {
                result += pipe[2];
                parent[p1] = p2;
                count -= 1;
            }
        }
        return result;
    }
};
