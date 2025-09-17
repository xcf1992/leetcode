/*
399. Evaluate Division
https://leetcode.com/problems/evaluate-division/

Equations are given in the format A / B = k,
where A and B are variables represented as strings,
and k is a real number (floating point number).
Given some queries, return the answers.
If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.
According to the example above:
equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].

The input is always valid.
You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
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
private:
    double calculate(string first, string second, unordered_map<string, unordered_map<string, double>>& connect, unordered_set<string>& visited) {
        if (connect.find(first) == connect.end()) {
            return -1.0;
        }

        unordered_map<string, double> next = connect[first];
        if (next.find(second) != next.end()) {
            return next[second];
        }

        visited.insert(first);
        for (auto& it : next) {
            if (visited.find(it.first) != visited.end()) {
                continue;
            }

            double result = calculate(it.first, second, connect, visited);
            if (result != -1.0) {
                connect[first][second] = it.second * result;
                return connect[first][second];
            }
        }
        return -1.0;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> connect;
        for (int i = 0; i < equations.size(); ++i) {
            vector<string> equation = equations[i];
            connect[equation[0]][equation[1]] = values[i];
            connect[equation[1]][equation[0]] = 1.0 / values[i];
        }

        vector<double> result;
        for (vector<string>& query : queries) {
            string first = query[0];
            string second = query[1];
            if (connect.find(first) == connect.end() or connect.find(second) == connect.end()) {
                result.push_back(-1.0);
                continue;
            }

            if (first == second) {
                result.push_back(1.0);
                continue;
            }

            unordered_set<string> visited;
            result.push_back(calculate(first, second, connect, visited));
        }
        return result;
    }
};

class Solution1 {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, int> points;
        int index = 0;
        for (auto e : equations) {
            if (points.find(e.first) == points.end()) {
                points[e.first] = index;
                index += 1;
            }
            if (points.find(e.second) == points.end()) {
                points[e.second] = index;
                index += 1;
            }
        }

        vector<vector <double>> graph(points.size(), vector<double>(points.size(), INT_MAX));
        for (int i = 0; i < equations.size(); i++) {
            int x = points[equations[i].first];
            int y = points[equations[i].second];
            graph[x][x] = 1.0;
            graph[y][y] = 1.0;
            graph[x][y] = values[i];
            graph[y][x] = 1.0 / values[i];
        }

        for (int k = 0; k < points.size(); k++) {
            for (int i = 0; i < points.size(); i++) {
                for (int j = 0; j < points.size(); j++) {
                    if (graph[i][k] != INT_MAX and graph[k][j] != INT_MAX) {
                        graph[i][j] = min(graph[i][j], graph[i][k] * graph[k][j]);
                    }
                }
            }
        }

        vector<double> result;
        for (auto q : queries) {
            if (points.find(q.first) == points.end() or points.find(q.second) == points.end()) {
                result.push_back(-1.0);
            }
            else {
                result.push_back(graph[points[q.first]][points[q.second]] == INT_MAX ? -1.0 : graph[points[q.first]][points[q.second]]);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}