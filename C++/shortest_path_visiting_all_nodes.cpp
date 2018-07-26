/*
 An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
 
 graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
 
 Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
 
 
 
 Example 1:
 
 Input: [[1,2,3],[0],[0],[0]]
 Output: 4
 Explanation: One possible path is [1,0,2,0,3]
 Example 2:
 
 Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
 Output: 4
 Explanation: One possible path is [0,1,4,2,3]
 
 
 Note:
 
 1 <= graph.length <= 12
 0 <= graph[i].length < graph.length
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
#include <stdio.h>
#include <set>
using namespace std;

struct Path {
public:
    Path(int n, int c, int m) {
        node = n;
        cost = c;
        bitmask = m;
    }
    
    int node = 0;
    int cost = 0;
    int bitmask = 0;
};


struct PathHash {
    std::size_t operator() (const Path& path) const {
        return 97 * path.bitmask + 71 * path.node;
    }
};

struct PathComp {
    bool operator()(const Path& a, const Path& b) const{
        return (a.node == b.node) && (a.bitmask == b.bitmask);
    }
};

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        unordered_set<Path, PathHash, PathComp> visited;
        queue<Path> bfs;
        for (int i = 0; i < n; i++) {
            int mask = (1 << i);
            visited.insert(Path(i, 0, mask));
            bfs.push(Path(i, 0, mask));
        }
        
        while (!bfs.empty()) {
            Path cur = bfs.front();
            bfs.pop();
            if (cur.bitmask == (1 << n) - 1) {
                return cur.cost;
            }
            
            for (int next : graph[cur.node]) {
                int mask = (cur.bitmask | 1 << next);
                Path tuple = Path(next, cur.cost + 1, mask);
                if (visited.find(tuple) == visited.end()) {
                    visited.insert(tuple);
                    bfs.push(tuple);
                }
            }
        }
        return -1;
    }
};
