/*
1766. Tree of Coprimes
https://leetcode.com/problems/tree-of-coprimes/

There is a tree
(i.e., a connected, undirected graph that has no cycles)
consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
Each node has a value associated with it, and the root of the tree is node 0.

To represent this tree,
you are given an integer array nums and a 2D array edges.
Each nums[i] represents the ith node's value,
and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.

Two values x and y are coprime if gcd(x, y) == 1
where gcd(x, y) is the greatest common divisor of x and y.

An ancestor of a node i is any other node on the shortest path from node i to the root.
A node is not considered an ancestor of itself.

Return an array ans of size n,
where ans[i] is the closest ancestor to node i such that nums[i]
and nums[ans[i]] are coprime,
or -1 if there is no such ancestor.

Example 1:
Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
Output: [-1,0,0,1]
Explanation: In the above figure, each node's value is in parentheses.
- Node 0 has no coprime ancestors.
- Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3) == 1).
- Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime (gcd(3,3) == 3), but node 0's
  value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
- Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1 (gcd(3,2) == 1), so node 1 is its
  closest valid ancestor.
Example 2:
Input: nums = [5,6,10,2,3,6,15], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
Output: [-1,0,-1,0,0,0,-1]

Constraints:
nums.length == n
1 <= nums[i] <= 50
1 <= n <= 105
edges.length == n - 1
edges[j].length == 2
0 <= uj, vj < n
uj != vj
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
#include <numeric>
#include <bitset>
using namespace std;
/*
So, we need to write our code in a way that we do not check more that 50 ancestors for each node. Or else - TLE.

First, we collect all unique numbers in our tree.
Then, for each number, we save all of its co-primes into cops.
Now, it's a simple tree traversal (be sure to pass the parent so you won't go back).
For each value n[i], we enumerate all of its co-primes, and check if a cop is within our ancestors.
If it is - pick the most recent ancestor, and get its level and index.
Assign the index of the closest ancestor (by tracking the highest level) to the result.
Add {level, i} to the list of ancestors for value n[i].
Traverse children (do not go back to parent).
Remove last ancestor for value n[i].
*/
class Solution {
public:
    unordered_map<int, vector<int>> cops;
    unordered_map<int, vector<pair<int, int>>> ancestors;

    void traverse(vector<int>& n, vector<vector<int>>& al, int i, int parent, int level, vector<int>& res) {
        int max_level = -1;
        for (auto cop : cops[n[i]]) {
            auto& v = ancestors[cop];
            if (!v.empty() && v.back().first > max_level) {
                max_level = v.back().first;
                res[i] = v.back().second;
            }
        }

        ancestors[n[i]].push_back({level, i});
        for (auto child : al[i])
            if (child != parent)
                traverse(n, al, child, i, level + 1, res);

        ancestors[n[i]].pop_back();
    }

    vector<int> getCoprimes(vector<int>& n, vector<vector<int>>& edges) {
        unordered_set<int> s(begin(n), end(n));
        for (auto n1 : s) {
            for (auto n2 : s)
                if (__gcd(n1, n2) == 1)
                    cops[n1].push_back(n2);
        }

        vector<vector<int>> al(n.size());
        vector<int> res(n.size(), -1);
        for (auto& e : edges) {
            al[e[0]].push_back(e[1]);
            al[e[1]].push_back(e[0]);
        }

        traverse(n, al, 0, 0, 0, res);
        return res;
    }
};