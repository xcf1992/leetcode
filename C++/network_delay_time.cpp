/*
743. Network Delay Time
https://leetcode.com/problems/network-delay-time/

There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w),
where u is the source node, v is the target node,
and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K.
How long will it take for all nodes to receive the signal?
If it is impossible, return -1.

Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
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
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<pair<int, int>>> distance(N + 1, vector<pair<int, int>>());
        for (vector<int>& time : times) {
            distance[time[0]].push_back({time[1], time[2]});
        }

        vector<int> delay(N + 1, INT_MAX);
        queue<pair<int, int>> nodes;
        nodes.push(make_pair(K, 0));
        while (!nodes.empty()) {
            int curNode = nodes.front().first;
            int curTime = nodes.front().second;
            delay[curNode] = min(delay[curNode], curTime);
            nodes.pop();

            for (pair<int, int>& next : distance[curNode]) {
                if (delay[next.first] > curTime + next.second) {
                    nodes.push(make_pair(next.first, curTime + next.second));
                }
            }
        }

        int result = 0;
        for (int i = 1; i < delay.size(); i++) {
            if (delay[i] == INT_MAX) {
                return -1;
            }
            result = max(result, delay[i]);
        }
        return result;
    }
};
