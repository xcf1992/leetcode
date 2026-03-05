/*
https://www.hack2hire.com/companies/stripe/coding-questions/69767fdf5ed12b33b05f0efe/practice?questionId=6976850c5ed12b33b05f0f0f
Shipping Route Cost Paths
A logistics company operates an international parcel delivery service, and you are tasked with developing a function to
help customers discover all possible shipping paths between countries. The company's data is provided as a list of
available shipping routes, where each route is a string in the format:

"<source>:<target>:<method>:<cost>"
source and target are country codes consisting of uppercase letters.
method is a string identifying the shipping carrier for that route.
cost is a positive integer representing the price to ship along that carrier between the two countries.
Given a list of such routes as routes, and two countries source and target, return all possible shipping paths from
source to target using at most one transfer (that is, via at most one intermediate country and any shipping methods).

Each valid path should be represented in one of the following formats:

For direct routes:

"A->B;M;C"
where A is the source, B is the target, M is the carrier, and C is the cost.

For one-transfer routes:

"A->B->C;M1->M2;T"
where A is the source, B is the intermediate country, C is the target, M1 and M2 are the carriers used, and T is the sum
of both costs.

Your implementation should return all such valid formatted strings in any order. If there is no way to reach the target
from the source with at most one transfer, return an empty list.

Constraints:

1 ≤ routes.length ≤ 10⁴
All country and method names are non-empty uppercase strings.
source and target are always different.
No route connects a country to itself.
Example 1:

Input: routes = ["US:UK:FEDEX:5", "US:CA:UPS:1", "CA:FR:DHL:3", "UK:FR:DHL:2"], source = "US", target = "FR"
Output: ["US->CA->FR;UPS->DHL;4", "US->UK->FR;FEDEX->DHL;7"]
Explanation: There is no direct route from the US to FR. Two transfer options exist: US->CA->FR (UPS, DHL, cost 4) and
US->UK->FR (FEDEX, DHL, cost 7).

Example 2:

Input: routes = ["US:UK:FEDEX:10"], source = "US", target = "UK"
Output: ["US->UK;FEDEX;10"]

Example 3:

Input: routes = ["US:CA:UPS:5", "CA:UK:DHL:3"], source = "US", target = "UK"
Output: ["US->CA->UK;UPS->DHL;8"]
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
using namespace std;

struct Edge {
    string to;
    string method;
    int cost;

    Edge(string to, string method, int cost) : to(to), method(method), cost(cost) {
    }
};

class Solution {
public:
    vector<string> getShippingPaths(vector<string> routes, string source, string target) {
        unordered_map<string, vector<Edge>> outMap;

        for (const string& route : routes) {
            stringstream ss(route);
            string from, to, method, costStr;

            getline(ss, from, ':');
            getline(ss, to, ':');
            getline(ss, method, ':');
            getline(ss, costStr);

            int cost = stoi(costStr);

            if (outMap.find(from) == outMap.end()) {
                outMap[from] = vector<Edge>();
            }
            outMap[from].push_back(Edge(to, method, cost));
        }

        vector<string> result;
        if (outMap.find(source) == outMap.end()) {
            return result;
        }

        for (const Edge& edge1 : outMap[source]) {
            string mid = edge1.to;
            if (mid == target) {
                string path = source + "->" + target + ";" + edge1.method + ";" + to_string(edge1.cost);
                result.push_back(path);
            }

            if (outMap.find(mid) == outMap.end()) {
                continue;
            }

            for (const Edge& edge2 : outMap[mid]) {
                if (edge2.to == target) {
                    int totalCost = edge1.cost + edge2.cost;
                    string path = source + "->" + mid + "->" + target + ";" + edge1.method + "->" + edge2.method + ";" +
                                  to_string(totalCost);
                    result.push_back(path);
                }
            }
        }
        return result;
    }
};

/*
Follow-up 1:
In this follow-up, instead of returning all possible shipping paths, return the cheapest shipping path from source to
target using at most one transfer. It is guaranteed that exactly one cheapest shipping path exists among all valid
paths. If no valid path exists, return an empty string.

The output should follow these formats (same as the previous question):

Direct route: "A->B;M;C"
One-transfer route: "A->B->C;M1->M2;T"
where A is the source, B the intermediate country (if any), C the target, M, M1, and M2 are the shipping carriers, and
C, T the total cost.

Example 1:

Input: routes = ["US:UK:FEDEX:5", "US:CA:UPS:1", "CA:FR:DHL:3", "UK:FR:DHL:2"], source = "US", target = "FR"
Output: "US->CA->FR;UPS->DHL;4"
Explanation: The cheapest option is to ship from US to CA using UPS (cost 1), then from CA to FR using DHL (cost 3),
total cost 4.

Example 2:

Input: routes = ["US:UK:FEDEX:10"], source = "US", target = "UK"
Output: "US->UK;FEDEX;10"

Example 3:

Input: routes = ["US:CA:UPS:5", "CA:UK:DHL:3"], source = "US", target = "UK"
Output: "US->CA->UK;UPS->DHL;8"
 */

class Solution {
public:
    string getCheapestShippingPath(vector<string> routes, string source, string target) {
        unordered_map<string, vector<Edge>> outMap;

        for (const string& route : routes) {
            stringstream ss(route);
            string from, to, method, costStr;

            getline(ss, from, ':');
            getline(ss, to, ':');
            getline(ss, method, ':');
            getline(ss, costStr);

            int cost = stoi(costStr);

            if (outMap.find(from) == outMap.end()) {
                outMap[from] = vector<Edge>();
            }
            outMap[from].push_back(Edge(to, method, cost));
        }

        string rst;
        int min_cost = INT_MAX;
        if (outMap.find(source) == outMap.end()) {
            return rst;
        }

        for (const Edge& edge1 : outMap[source]) {
            string mid = edge1.to;
            if (mid == target) {
                string path = source + "->" + target + ";" + edge1.method + ";" + to_string(edge1.cost);
                if (rst == "" || min_cost > edge1.cost) {
                    min_cost = edge1.cost;
                    rst = path;
                }
            }

            if (outMap.find(mid) == outMap.end()) {
                continue;
            }

            for (const Edge& edge2 : outMap[mid]) {
                if (edge2.to == target) {
                    int totalCost = edge1.cost + edge2.cost;
                    string path = source + "->" + mid + "->" + target + ";" + edge1.method + "->" + edge2.method + ";" +
                                  to_string(totalCost);
                    if (rst == "" || min_cost > totalCost) {
                        min_cost = totalCost;
                        rst = path;
                    }
                }
            }
        }
        return rst;
    }
};

/*
Follow-up 2:
In this follow-up question, find the cheapest shipping path from source to target, but allow any number of transfers
(intermediate countries) in the path. You may assume there will always be exactly one cheapest shipping path among all
valid options.

Return a single string with the path in the same format as the previous task. If no valid path exists, return an empty
string.

Example 1:

Input: routes = ["US:UK:FEDEX:5", "US:CA:UPS:1", "CA:FR:DHL:3", "UK:FR:DHL:2", "FR:US:DHL:4"], source = "US", target =
"FR" Output: "US->CA->FR;UPS->DHL;4" Explanation: The cheapest path is US to CA using UPS (cost 1), then CA to FR using
DHL (cost 3), total cost 4.

Example 2:

Input: routes = ["A:B:M1:10"], source = "A", target = "B"
Output: "A->B;M1;10"

Example 3:

Input: routes = ["A:C:M1:3", "C:B:M2:5"], source = "A", target = "B"
Output: "A->C->B;M1->M2;8"
*/

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <sstream>
using namespace std;

struct Edge {
    string to;
    string method;
    int cost;

    Edge(string to, string method, int cost) : to(to), method(method), cost(cost) {
    }
};

struct State {
    string city;
    int cost;

    State(string city, int cost) : city(city), cost(cost) {
    }

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

class Solution {
public:
    string getCheapestShippingPath(vector<string> routes, string source, string target) {
        unordered_map<string, vector<Edge>> outMap;
        for (const string& route : routes) {
            size_t pos1 = route.find(':');
            size_t pos2 = route.find(':', pos1 + 1);
            size_t pos3 = route.find(':', pos2 + 1);

            string from = route.substr(0, pos1);
            string to = route.substr(pos1 + 1, pos2 - pos1 - 1);
            string method = route.substr(pos2 + 1, pos3 - pos2 - 1);
            int cost = stoi(route.substr(pos3 + 1));

            outMap[from].push_back(Edge(to, method, cost));
        }

        // Dijkstra
        unordered_map<string, int> min_cost;
        unordered_map<string, string> prev_pos;
        unordered_map<string, string> prev_method;
        priority_queue<State, vector<State>, greater<State>> pq;

        min_cost[source] = 0;
        pq.push(State(source, 0));
        while (!pq.empty()) {
            string curCity = pq.top().city;
            int curCost = pq.top().cost;
            pq.pop();

            if (curCity == target) {
                break;
            }

            // Skip if outdated
            if (min_cost.find(curCity) != min_cost.end() && curCost > min_cost[curCity]) {
                continue;
            }

            if (outMap.find(curCity) == outMap.end()) {
                continue;
            }

            for (const Edge& edge : outMap[curCity]) {
                int nextCost = curCost + edge.cost;
                if (min_cost.find(edge.to) == min_cost.end() || nextCost < min_cost[edge.to]) {
                    min_cost[edge.to] = nextCost;
                    prev_pos[edge.to] = curCity;
                    prev_method[edge.to] = edge.method;
                    pq.push(State(edge.to, nextCost));
                }
            }
        }

        if (min_cost.find(target) == min_cost.end()) {
            return "";
        }

        // Reconstruct path
        vector<string> cities;
        vector<string> methods;
        string cur = target;
        while (cur != source) {
            cities.push_back(cur);
            methods.push_back(prev_method[cur]);
            cur = prev_pos[cur];
        }
        cities.push_back(source);

        // Reverse to get source to target order
        reverse(cities.begin(), cities.end());
        reverse(methods.begin(), methods.end());

        // Format output
        string pathBuilder = "";
        for (int i = 0; i < cities.size(); i = i + 1) {
            if (i > 0) {
                pathBuilder += "->";
            }
            pathBuilder += cities[i];
        }

        pathBuilder += ";";

        for (int i = 0; i < methods.size(); i = i + 1) {
            if (i > 0) {
                pathBuilder += "->";
            }
            pathBuilder += methods[i];
        }

        pathBuilder += ";";
        pathBuilder += to_string(min_cost[target]);

        return pathBuilder;
    }
};