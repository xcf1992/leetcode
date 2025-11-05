/*
https://www.1point3acres.com/bbs/interview/airbnb-software-engineer-277494.html

There are 10 wizards, 0-9,
you are given a list that each entry is a list of wizards known by wizard.
Define the cost between wizards and wizard as square of different of i and j.
To find the min cost between 0 and 9.

follow up: print the path
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

// if want to print the path, we can use another vector<int> to store the pre
class Solution {
public:
    int minCostWizards(vector<vector<int> > wizards) {
        vector<int> distance(10, INT_MAX);
        distance[0] = 0;
        queue<pair<int, int> > bfs;
        bfs.push({0, 0});
        while (!bfs.empty()) {
            int cur = bfs.front().first;
            int dis = bfs.front().second;
            bfs.pop();

            if (cur == 9) {
                continue;
            }

            for (int nex: wizards[cur]) {
                int cost = (nex - cur) * (nex - cur);
                if (cost + dis < distance[nex]) {
                    distance[nex] = cost + dis;
                    bfs.push({nex, dis + cost});
                }
            }
        }
        return distance[9];
    }
}