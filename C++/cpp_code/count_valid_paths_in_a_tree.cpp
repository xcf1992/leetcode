/*
https://leetcode.com/problems/count-valid-paths-in-a-tree/description/
2867. Count Valid Paths in a Tree

There is an undirected tree with n nodes labeled from 1 to n. You are given the integer n and a 2D integer array edges
of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.

Return the number of valid paths in the tree.

A path (a, b) is valid if there exists exactly one prime number among the node labels in the path from a to b.

Note that:

The path (a, b) is a sequence of distinct nodes starting with node a and ending with node b such that every two adjacent
nodes in the sequence share an edge in the tree. Path (a, b) and path (b, a) are considered the same and counted only
once.


Example 1:


Input: n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
Output: 4
Explanation: The pairs with exactly one prime number on the path between them are:
- (1, 2) since the path from 1 to 2 contains prime number 2.
- (1, 3) since the path from 1 to 3 contains prime number 3.
- (1, 4) since the path from 1 to 4 contains prime number 2.
- (2, 4) since the path from 2 to 4 contains prime number 2.
It can be shown that there are only 4 valid paths.
Example 2:


Input: n = 6, edges = [[1,2],[1,3],[2,4],[3,5],[3,6]]
Output: 6
Explanation: The pairs with exactly one prime number on the path between them are:
- (1, 2) since the path from 1 to 2 contains prime number 2.
- (1, 3) since the path from 1 to 3 contains prime number 3.
- (1, 4) since the path from 1 to 4 contains prime number 2.
- (1, 6) since the path from 1 to 6 contains prime number 3.
- (2, 4) since the path from 2 to 4 contains prime number 2.
- (3, 6) since the path from 3 to 6 contains prime number 3.
It can be shown that there are only 6 valid paths.


Constraints:

1 <= n <= 105
edges.length == n - 1
edges[i].length == 2
1 <= ui, vi <= n
The input is generated such that edges represent a valid tree.
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
using namespace std;
/*
Linear sieve to get all the prime numbers that are no larger than n.
Then do a tree DP (or simply consider it as DFS) to calculate the result.

Approach
Use linear sieve to get all prime numbers, other sieve algorithms that have higher time complexity are also acceptable.

In DFS/Tree DP, return 2 values:
(1) The number of paths from root "goes down" that has no prime numbers, say A.
(2) The number of paths from root "pass down" that has only one prime numbers, say B.

If root is a prime number then:
root_A = 0
root_B = sigma(A) via all childeren of root.

If root is not a prime number then:
root_A = sigma(A) via all childeren of root.
root_B = sigma(B) via all childeren of root.

Before updating root_A and root_B for each child
we add root_A * B + root_B * A to our final answer. That's the number of paths "pass through" and has only one prime
number.

Here "pass through" means the paths between the root's 2 descendants.
*/
class Solution {
private:
    long long mul(long long x, long long y) {
        return x * y;
    }

    pair<int, int> dfs(int cur, int prev, vector<vector<int>>& adj, vector<bool>& prime, long long& rst) {
        pair<int, int> dp_cur = {!prime[cur], prime[cur]};  // path cnt with no prime / path cnt with 1 prime
        for (int child : adj[cur]) {
            if (child == prev) {
                continue;
            }

            const pair<int, int>& dp_child = dfs(child, cur, adj, prime, rst);
            rst += mul(dp_child.first, dp_cur.second) + mul(dp_child.second, dp_cur.first);
            if (prime[cur]) {
                dp_cur.second += dp_child.first;
            } else {
                dp_cur.first += dp_child.first;
                dp_cur.second += dp_child.second;
            }
        }
        return dp_cur;
    }

public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        vector<bool> prime(n + 1, true);
        prime[1] = false;
        vector<int> all;
        for (int i = 2; i <= n; ++i) {
            if (prime[i]) {
                all.push_back(i);
            }

            for (int x : all) {
                const int temp = i * x;
                if (temp > n) {
                    break;
                }

                prime[temp] = false;
                if (i % x == 0) {
                    /*
                      Why the early break (i % x == 0) is crucial
                      When i % x == 0, this means x is a prime factor of i. Any larger prime y in the all list would
                      create i * y, but this number has a smaller prime factor than y (specifically, it would be marked
                      later by some smaller multiple). For example, at i=6 with x=2: we mark 6×2=12 and stop. We don't
                      mark 6×3=18 because 18 will be marked later as 9×2 when i=9, ensuring 18 is marked by its smallest
                      prime factor (2).
                    */
                    break;
                }
            }
        }

        vector<vector<int>> adj(n + 1);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        long long rst = 0;
        dfs(1, 0, adj, prime, rst);
        return rst;
    }
};
