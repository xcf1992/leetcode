/*
 Given a list of airline tickets represented by pairs of departure and arrival airports [from, to],
 reconstruct the itinerary in order.
 All of the tickets belong to a man who departs from JFK.
 Thus, the itinerary must begin with JFK.

 Note:
 If there are multiple valid itineraries,
 you should return the itinerary that has the smallest lexical order when read as a single string.
 For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 All airports are represented by three capital letters (IATA code).
 You may assume all tickets form at least one valid itinerary.

 Example 1:

 Input: tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
 Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
 Example 2:

 Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
 Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
 Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
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
private:
    bool dfs(vector<string>& result, unordered_map<string, map<string, int>>& graph, int count, string start) {
        if (count == 0) {
            return true;
        }

        for (auto it = graph[start].begin(); it != graph[start].end(); it++) {
            if (it -> second <= 0) {
                continue;
            }

            result.push_back(it -> first);
            it -> second -= 1;
            if (dfs(result, graph, count - 1, it -> first)) {
                return true;
            }
            it -> second += 1;
            result.pop_back();
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>> tickets) {
        vector<string> result;
        unordered_map<string, map<string, int>> graph;
        for (vector<string>& ticket : tickets) {
            graph[ticket[0]][ticket[1]] += 1;
        }
        result.push_back("JFK");
        dfs(result, graph, tickets.size(), "JFK");
        return result;
    }
};
