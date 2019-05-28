/*
 Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.
 
 For example:
 
 Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
 
 Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
 
 Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
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
#include <set>
using namespace std;

class Solution {
private:
    int findRoot(vector<int>& roots, int index) {
        while (roots[index] != -1) {
            index = roots[index];
        }
        return index;
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<int> roots(n, -1);
        for (vector<int>& edge : edges) {
            int rootX = findRoot(roots, edge[0]);
            int rootY = findRoot(roots, edge[1]);
            
            if (rootX == rootY) {
                return false;
            }
            roots[rootX] = rootY;
        }
        return edges.size() == n - 1;
    }
};
