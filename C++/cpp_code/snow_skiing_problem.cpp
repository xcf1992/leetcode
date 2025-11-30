/*
https://www.1point3acres.com/bbs/interview/airbnb-software-engineer-444503.html
https://www.1point3acres.com/bbs/interview/airbnb-engineering-470093.html
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int getMaximumScore(unordered_map<char, int> scores, unordered_map<char, unordered_map<char, int>> edges) {
        int n = scores.size();
        unordered_map<char, int> inDegree;
        unordered_map<char, int> outDegree;
        for (auto& it : scores) {
            inDegree[it.first] = 0;
            outDegree[it.first] = 0;
        }

        for (auto& it : edges) {
            int start = it.first;
            for (auto& to : it.second) {
                char dest = to.first;
                int dis = to.second;
                inDegree[dest] += 1;
                outDegree[start] += 1;
            }
        }

        unordered_set<char> endPoints;
        for (auto& it : outDegree) {
            if (it.second == 0) {
                endPoints.insert(it.first);
            }
        }

        vector<char> bfs;
        unordered_map<char, int> result;
        for (auto& it : inDegree) {
            if (it.second == 0) {
                bfs.push_back(it.first);
                result[it.first] = scores[it.first];
            }
        }

        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int cur = bfs.front();
                bfs.pop_back();

                for (auto& it : edges[cur]) {
                    char nextP = it.first;
                    int dis = it.second;
                    if (result.find(nextP) == result.end() or result[nextP] < scores[cur] + scores[nextP] - dis) {
                        result[nextP] = scores[cur] + scores[nextP] - dis;
                    }

                    inDegree[nextP] -= 1;
                    if (inDegree[nextP] == 0) {
                        bfs.push_back(nextP);
                    }
                }
            }
        }

        int maxScore = INT_MIN;
        for (char c : endPoints) {
            if (endPoints.find(c) == endPoints.end()) {
                continue;
            }
            maxScore = max(maxScore, result[c]);
        }
        return maxScore;
    }
};