/*
886. Possible Bipartition
Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.

Each person may dislike some other people, and they should not go into the same group.

Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.

Return true if and only if it is possible to split everyone into two groups in this way.

Example 1:

Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4], group2 [2,3]
Example 2:

Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Example 3:

Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false


Note:

1 <= N <= 2000
0 <= dislikes.length <= 10000
1 <= dislikes[i][j] <= N
dislikes[i][0] < dislikes[i][1]
There does not exist i != j for which dislikes[i] == dislikes[j].
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
#include <numeric>
using namespace std;

class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<int> group(N + 1, 0); // there are 2 colors 1 & -1
        unordered_map<int, vector<int>> hate;
        for (vector<int>& d : dislikes) {
            hate[d[0]].push_back(d[1]);
            hate[d[1]].push_back(d[0]);
        }

        queue<int> bfs;
        for (auto cur : hate) {
            if (group[cur.first] != 0) {
                continue;
            }

            group[cur.first] = 1;
            bfs.push(cur.first);
            while (!bfs.empty()) {
                int s = bfs.front();
                bfs.pop();

                for (int next : hate[s]) { // all neighbors of s
                    if (group[next] == 0) {
                        group[next] = -1 * group[s];
                        bfs.push(next);
                    }
                    else if (group[next] != -1 * group[s]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

class Solution { // dfs
private:
    bool check(unordered_map<int, vector<int>>& hate, vector<int>& group, int index, int color) {
        if (group[index] != 0) {
            return group[index] == color;
        }

        group[index] = color;
        for (int nxt : hate[index]) {
            if (!check(hate, group, nxt, 0 - color)) {
                return false;
            }
        }
        return true;
    }
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        unordered_map<int, vector<int>> hate;
        for (vector<int>& d : dislikes) {
            hate[d[0]].push_back(d[1]);
            hate[d[1]].push_back(d[0]);
        }

        vector<int> group(N + 1, 0); // there are 2 colors 1 & -1
        for (int i = 0; i < N; ++i) {
            if (group[i] == 0 and !check(hate, group, i, 1)) {
                return false;
            }
        }
        return true;
    }
};