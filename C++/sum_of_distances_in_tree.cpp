/*
834. Sum of Distances in Tree

An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.
The ith edge connects nodes edges[i][0] and edges[i][1] together.
Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.

Example 1:
Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation:
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.

Note:
1 <= N <= 10000
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
#include <numeric>
using namespace std;
/*
Let ans be the returned answer, so that in particular ans[x] be the answer for node x.

Naively, finding each ans[x] would take O(N) time (where N is the number of nodes in the graph), which is too slow.
This is the motivation to find out how ans[x] and ans[y] are related, so that we cut down on repeated work.

Let's investigate the answers of neighboring nodes x and y.
In particular, say xy is an edge of the graph,
that if cut would form two trees XX(containing x) and Y (containing y).

Then, as illustrated in the diagram,
the answer for x in the entire tree, is the answer of x on X "x@X",
plus the answer of y on Y "y@Y",
plus the number of nodes in Y "#(Y)".
The last part "#(Y)" is specifically because for any node z in Y, dist(x, z) = dist(y, z) + 1.

By similar reasoning,
the answer for y in the entire tree is ans[y] = x@X + y@Y + #(X).
Hence, for neighboring nodes x and y, ans[x] - ans[y] = #(Y) - #(X).

When we move our root from one node to its connected node, one part of nodes get closer, one the other part get further.
If we know exactly hom many nodes in both parts, we can solve this problem.

With one single traversal in tree, we should get enough information for it and don't need to do it again and again.

Explanation:
0. Let's solve it with node 0 as root.

Initial an array of hashset tree, tree[i] contains all connected nodes to i.
Initial an array count, count[i] counts all nodes in the subtree i.
Initial an array of res, res[i] counts sum of distance in subtree i.

Post order dfs traversal, update count and res:
count[root] = sum(count[i]) + 1
res[root] = sum(res[i]) + sum(count[i])

Pre order dfs traversal, update res:
When we move our root from parent to its child i, count[i] points get 1 closer to root, n - count[i] nodes get 1 futhur to root.
res[i] = res[root] - count[i] + N - count[i]

return res, done.

Time Complexity:
dfs: O(N)
dfs2: O(N)
*/
class Solution {
private:
    void getChildCount(int root, vector<vector<int>>& connected, vector<int>& count, vector<int>& result, vector<bool>& visited) {
        visited[root] = true;
        for (int child : connected[root]) if (!visited[child]) {
            getChildCount(child, connected, count, result, visited);
            count[root] += count[child];
            result[root] += result[child] + count[child];
        }
    }

    void updateDistance(int root, vector<vector<int>>& connected, vector<int>& count, vector<int>& result, vector<bool>& visited, int N) {
        visited[root] = true;
        for (int child : connected[root]) if (!visited[child]) {
            result[child] = result[root] - count[child] + N - count[child];
            updateDistance(child, connected, count, result, visited, N);
        }
    }
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        if (N == 1) {
            return {0};
        }

        vector<vector<int>> connected(N);
        for (vector<int>& edge : edges) {
            connected[edge[0]].push_back(edge[1]);
            connected[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(N, false);
        vector<int> count(N, 1); // the count of child nodes include itself
        vector<int> result(N, 0);
        // we set 0 as root, count of child for each node, update distance accourdingly
        getChildCount(0, connected, count, result, visited);
        // after this step only the result of root 0 is correct,
        // we will update result for other nodes from root to leaves, according its distance to its parent
        visited.clear();
        visited.resize(N, false);
        updateDistance(0, connected, count, result, visited, N);
        return result;
    }
};

// memory limit exceed
class Solution1 {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> connected;
        for (vector<int>& edge : edges) {
            connected[edge[0]].push_back(edge[1]);
            connected[edge[1]].push_back(edge[0]);
        }

        vector<int> result(N, 0);
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<vector<int>> bfs;
        for (int i = 0; i < N; i++) {
            bfs.push({i, i}); // {source, cur}
            visited[i][i] = true;
        }

        int distance = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int source = bfs.front()[0];
                int cur = bfs.front()[1];
                bfs.pop();
                result[source] += distance;
                for (int next : connected[cur]) {
                    if (!visited[source][next]) {
                        visited[source][next] = true;
                        bfs.push({source, next});
                    }
                }
            }
            distance += 1;
        }
        return result;
    }
};
