/*
https://leetcode.com/problems/most-profitable-path-in-a-tree/description/
2467. Most Profitable Path in a Tree

There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array
edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:

the price needed to open the gate at node i, if amount[i] is negative, or,
the cash reward obtained on opening the gate at node i, otherwise.
The game goes on as follows:

Initially, Alice is at node 0 and Bob is at node bob.
At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves
towards node 0. For every node along their path, Alice and Bob either spend money to open the gate at that node, or
accept the reward. Note that: If the gate is already open, no price will be required, nor will there be any cash reward.
If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words,
if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c,
both of them receive c / 2 each. If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he
stops moving. Note that these events are independent of each other. Return the maximum net income Alice can have if she
travels towards the optimal leaf node.



Example 1:


Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
Output: 6
Explanation:
The above diagram represents the given tree. The game goes as follows:
- Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
  Alice's net income is now -2.
- Both Alice and Bob move to node 1.
  Since they reach here simultaneously, they open the gate together and share the reward.
  Alice's net income becomes -2 + (4 / 2) = 0.
- Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
  Bob moves on to node 0, and stops moving.
- Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
Now, neither Alice nor Bob can make any further moves, and the game ends.
It is not possible for Alice to get a higher net income.
Example 2:


Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
Output: -7280
Explanation:
Alice follows the path 0->1 whereas Bob follows the path 1->0.
Thus, Alice opens the gate at node 0 only. Hence, her net income is -7280.


Constraints:

2 <= n <= 105
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.
1 <= bob < n
amount.length == n
amount[i] is an even integer in the range [-104, 104].
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
#include <set>
using namespace std;

class Solution {
private:
    bool calc_bob_path(vector<unordered_set<int>>& graph, vector<int>& bob_path, int cur, vector<bool>& visited) {
        if (cur == 0) {
            return true;
        }

        for (int nxt : graph[cur]) {
            if (visited[nxt]) {
                continue;
            }

            bob_path.push_back(nxt);
            visited[nxt] = true;
            if (calc_bob_path(graph, bob_path, nxt, visited)) {
                return true;
            }
            visited[nxt] = false;
            bob_path.pop_back();
        }
        return false;
    }

public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = amount.size();
        vector<unordered_set<int>> graph(n);
        for (vector<int>& edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }

        vector<int> bob_path;
        vector<bool> visited(n, false);
        bob_path.push_back(bob);
        visited[bob] = true;
        calc_bob_path(graph, bob_path, bob, visited);

        unordered_map<int, int> bob_path_ts;
        for (int i = 0; i < bob_path.size(); i++) {
            bob_path_ts[bob_path[i]] = i;
        }

        queue<tuple<int, int, int>> bfs;
        bfs.push({0, amount[0], 0});
        int rst = INT_MIN;
        while (!bfs.empty()) {
            int cur = get<0>(bfs.front());
            int cur_profit = get<1>(bfs.front());
            int cur_time = get<2>(bfs.front());
            bfs.pop();

            if (graph[cur].empty()) {
                rst = max(rst, cur_profit);
                continue;
            }

            for (int nxt : graph[cur]) {
                graph[nxt].erase(cur);

                int new_profit = cur_profit;
                if (bob_path_ts.find(nxt) == bob_path_ts.end()) {
                    new_profit += amount[nxt];
                } else if (bob_path_ts[nxt] > cur_time + 1) {
                    new_profit += amount[nxt];
                } else if (bob_path_ts[nxt] == cur_time + 1) {
                    new_profit += amount[nxt] / 2;
                }

                bfs.push({nxt, new_profit, cur_time + 1});
            }
        }
        return rst;
    }
};