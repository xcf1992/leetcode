/*
787. Cheapest Flights Within K Stops
https://leetcode.com/problems/cheapest-flights-within-k-stops/

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

struct myComp {
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[0] > b[0];
    }
};

class Solution2 { // dijkstra
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<pair<int, int>>> prices(n);
        for (vector<int>& flight : flights) {
            prices[flight[0]].push_back({flight[1], flight[2]});
        }

        priority_queue<vector<int>, vector<vector<int>>, myComp> pq;
        pq.push({0, 0, src});
        while (!pq.empty()) {
            int curCost = pq.top()[0];
            int curStops = pq.top()[1];
            int curPos = pq.top()[2];
            pq.pop();

            if (curPos == dst) {
                return curCost;
            }
            if (curStops > K) {
                continue;
            }

            for (pair<int, int>& price : prices[curPos]) {
                pq.push({curCost + price.second, curStops + 1, price.first});
            }
        }
        return -1;
    }
};

class Solution { // bfs
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<int>> prices(n, vector<int>(n, INT_MAX));
        for (vector<int>& flight : flights) {
            prices[flight[0]][flight[1]] = flight[2];
        }

        queue<vector<int>> bfs;
        for (int next = 0; next < n; ++next) if (prices[src][next] != INT_MAX) {
            bfs.push({0, next, prices[src][next]});
        }

        vector<int> cheapest(n, INT_MAX);
        cheapest[src] = 0;
        while (!bfs.empty()) {
            int stops = bfs.front()[0];
            int city = bfs.front()[1];
            int cost = bfs.front()[2];
            bfs.pop();

            if (stops > K or cost >= cheapest[city]) {
                continue;
            }

            cheapest[city] = cost;
            for (int nxt = 0; nxt < n; ++nxt) if (prices[city][nxt] != INT_MAX) {
                bfs.push({stops + 1, nxt, cost + prices[city][nxt]});
            }
        }
        return cheapest[dst] == INT_MAX ? -1 : cheapest[dst];
    }
};

// follow up print flight path
class Solution1 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int, unordered_map<int, int>> prices;
        for (vector<int>& flight : flights) {
            prices[flight[0]][flight[1]] = flight[2];
        }

        queue<vector<int>> bfs;
        bfs.push({0, src, 0}); // {stops, cur, cost}
        vector<int> cheapest(n, INT_MAX);
        cheapest[src] = 0;
        vector<int> pre(n, -1);
        while (!bfs.empty()) {
            int stops = bfs.front()[0];
            int city = bfs.front()[1];
            int cost = bfs.front()[2];
            bfs.pop();

            if (stops > K or city == dst) {
                continue;
            }

            for (auto nxt : prices[city]) {
                int nxtCost = cost + nxt.second;
                if (nxtCost < cheapest[nxt.first]) {
                    cheapest[nxt.first] = nxtCost;
                    pre[nxt.first] = city;
                    bfs.push({stops + 1, nxt.first, nxtCost});
                }
            }
        }

        vector<int> path;
        for (int i = dst; i != -1; i = pre[i]) {
            path.push_back(i);
            cout << i << endl;
        }
        return cheapest[dst] == INT_MAX ? -1 : cheapest[dst];
    }
};
