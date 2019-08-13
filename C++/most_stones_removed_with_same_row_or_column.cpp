/*
 947. Most Stones Removed with Same Row or Column
 On a 2D plane, we place stones at some integer coordinate points.
 Each coordinate point may have at most one stone.

 Now, a move consists of removing a stone that shares a column or row with another stone on the grid.

 What is the largest possible number of moves we can make?

 Example 1:

 Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
 Output: 5
 Example 2:

 Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
 Output: 5
 Example 3:

 Input: stones = [[0,0]]
 Output: 0


 Note:

 1 <= stones.length <= 1000
 0 <= stones[i][j] < 10000
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

// This problem can also be solved using Union-Find
// we need to find all stones belong to one component, which means t
class Solution {
private:
    int find(int i, vector<int>& parent) {
        if (parent[i] == -1) {
            return i;
        }
        parent[i] = find(parent[i], parent);
        return parent[i];
    }

    void uni(int i, int j, vector<int>& parent) {
        int pi = find(i, parent);
        int pj = find(j, parent);
        if (pi != pj) {
            parent[pi] = pj;
        }
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        vector<int> parent(stones.size(), -1);
        for (int i = 0; i < stones.size(); i++) {
            vector<int>& stoneI = stones[i];
            for (int j = i + 1; j < stones.size(); j++) {
                vector<int>& stoneJ = stones[j];
                if (stoneI[0] == stoneJ[0] || stoneI[1] == stoneJ[1]) {
                    uni(i, j, parent);
                }
            }
        }

        int result = stones.size();
        for (int p : parent) {
            if (p == -1) {
                result -= 1;
            }
        }
        return result;
    }
};

// let's consider each stone as a point
// if two stones are in the same row or column then they are connected
// we can remove points from the graph until one point has no connected point in its component
// we call components are points that are not connected with points outside its own component
class Solution1 {
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, unordered_set<int>> sameRow;
        unordered_map<int, unordered_set<int>> sameCol;
        for (int i = 0; i < stones.size(); i++) {
            vector<int> stone = stones[i];
            sameRow[stone[1]].insert(i);
            sameCol[stone[0]].insert(i);
        }

        int result = 0;
        vector<bool> visited(stones.size(), false);
        for (int i = 0; i < stones.size(); i++) {
            if (visited[i]) {
                continue;
            }

            visited[i] = true;
            result -= 1; // we can remove points from one component until there is only one point left
            queue<int> connected;
            connected.push(i);
            // for each unvisited stone, we do a BFS search and find all its connected point
            while (!connected.empty()) {
                int stone = connected.front();
                connected.pop();
                result += 1;
                for (int next : sameCol[stones[stone][0]]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        connected.push(next);
                    }
                }
                for (int next : sameRow[stones[stone][1]]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        connected.push(next);
                    }
                }
            }
        }
        return result;
    }
};
