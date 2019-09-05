/*
 787. Cheapest Flights Within K Stops
 There are n cities connected by m flights.
 Each fight starts from city u and arrives at v with a price w.

 Now given all the cities and fights,
 together with starting city src and the destination dst,
 your task is to find the cheapest price from src to dst with up to k stops.
 If there is no such route, output -1.

 Example 1:
 Input:
 n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 src = 0, dst = 2, k = 1
 Output: 200
 Explanation:
 The graph looks like this:
     0
    /  \
100/    \500
  * 100  *
 1------* 2


 The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
 Example 2:
 Input:
 n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 src = 0, dst = 2, k = 0
 Output: 500
 Explanation:
 The graph looks like this:
      0
    /  \
100/    \500
  * 100  *
 1------* 2


 The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 Note:

 The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
 The size of flights will be in range [0, n * (n - 1) / 2].
 The format of each flight will be (src, dst, price).
 The price of each flight will be in the range [1, 10000].
 k is in the range of [0, n - 1].
 There will not be any duplicated flights or self cycles.
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

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<int> cheapest(n, INT_MAX);
        cheapest[src] = 0;

        vector<vector<int>> prices(n, vector<int>(n, INT_MAX));
        for (vector<int>& flight : flights) {
            prices[flight[0]][flight[1]] = flight[2];
        }

        queue<vector<int>> bfs;
        for (int next = 0; next < n; ++next) if (prices[src][next] != INT_MAX) {
            bfs.push({0, next, prices[src][next]});
        }

        while (!bfs.empty()) {
            vector<int> curFlight = bfs.front();
            bfs.pop();

            int count = curFlight[0];
            int city = curFlight[1];
            int cost = curFlight[2];
            if (cost < cheapest[city]) {
                cheapest[city] = cost;
                if (count < K) {
                    for (int nxt = 0; nxt < n; ++nxt) if (prices[city][nxt] != INT_MAX) {
                        bfs.push({count + 1, nxt, prices[city][nxt] + cost});
                    }
                }
            }
        }
        return cheapest[dst] == INT_MAX ? -1 : cheapest[dst];
    }
};
