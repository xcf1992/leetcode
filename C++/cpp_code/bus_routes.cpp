/*
https://leetcode.com/problems/bus-routes/description/
815. Bus Routes

You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 ->
1 -> ... forever. You will start at the bus stop source (You are not on any bus initially), and you want to go to the
bus stop target. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.



Example 1:

Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
Example 2:

Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1

Constraints:

1 <= routes.length <= 500.
1 <= routes[i].length <= 10^5
All the values of routes[i] are unique.
sum(routes[i].length) <= 10^5
0 <= routes[i][j] < 10^6
0 <= source, target < 10^6
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
#include <map>
#include <numeric>
using namespace std;

// BFS
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        unordered_map<int, unordered_set<int>> bus_line;
        for (int i = 0; i < routes.size(); i++) {
            for (int stop : routes[i]) {
                bus_line[stop].insert(i);
            }
        }

        unordered_set<int> visited;
        queue<vector<int>> bfs;  // {busStop, distance}
        visited.insert(source);
        bfs.push({source, 0});
        while (!bfs.empty()) {
            int cur_stop = bfs.front()[0];
            int distance = bfs.front()[1];
            bfs.pop();

            if (cur_stop == target) {
                return distance;
            }

            for (int line : bus_line[cur_stop]) {
                for (int next : routes[line]) {
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        bfs.push({next, distance + 1});
                    }
                }
                // this is the key line otherwise it will TLE, it means we do not need to take the same bus again
                routes[line].clear();
            }
        }
        return -1;
    }
};
