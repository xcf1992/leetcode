/*
https://leetcode.com/problems/reconstruct-itinerary/description
332. Reconstruct Itinerary

You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports
of one flight. Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are
multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single
string.

For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.



Example 1:


Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
Example 2:


Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.


Constraints:

1 <= tickets.length <= 300
tickets[i].length == 2
fromi.length == 3
toi.length == 3
fromi and toi consist of uppercase English letters.
fromi != toi
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
private:
    void dfs(map<string, multiset<string>>& flights, vector<string>& result, string cur) {
        while (flights.find(cur) != flights.end() && flights[cur].size() > 0) {
            string next = *flights[cur].begin();
            flights[cur].erase(flights[cur].begin());
            dfs(flights, result, next);
        }
        result.push_back(cur);
    }

public:
    vector<string> findItinerary(vector<vector<string>> tickets) {
        map<string, multiset<string>> flights;
        for (vector<string>& t : tickets) {
            flights[t[0]].insert(t[1]);
        }

        vector<string> result;
        dfs(flights, result, "JFK");
        reverse(result.begin(), result.end());
        return result;
    }
};