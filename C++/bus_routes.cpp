/*
 We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.
 
 We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.
 
 Example:
 Input:
 routes = [[1, 2, 7], [3, 6, 7]]
 S = 1
 T = 6
 Output: 2
 Explanation:
 The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
 Note:
 
 1 <= routes.length <= 500.
 1 <= routes[i].length <= 500.
 0 <= routes[i][j] < 10 ^ 6.

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

// BFS
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        unordered_map<int, unordered_set<int>> busLine;
        for (int i = 0; i < routes.size(); i++) {
            for (int stop : routes[i]) {
                busLine[stop].insert(i);
            }
        }
        
        unordered_set<int> visited;
        queue<vector<int>> bfs; // {busStop, distance}
        visited.insert(S);
        bfs.push({S, 0});
        while (!bfs.empty()) {
            int curStop = bfs.front()[0];
            int distance = bfs.front()[1];
            bfs.pop();
            if (curStop == T) {
                return distance;
            }
            
            for (int line : busLine[curStop]) {
                for (int next : routes[line]) {
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        bfs.push({next, distance + 1});
                    }
                }
                routes[line].clear();
            }
        }
        return -1;
    }
};
