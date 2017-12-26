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
    void parse(const string& s, vector<string>& tokens) {
        int i = 0;
        int pos = s.find(":");
        while (pos != string::npos) {
            tokens.push_back(s.substr(i, pos - i));
            i = ++pos;
            pos = s.find(":", pos);
        }
        tokens.push_back(s.substr(i, s.length()));
    }
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> result(n, 0);
        vector<string> tokens;
        stack<pair<int, int>> execution;
        for (string log : logs) {
            tokens.clear();
            parse(log, tokens);
            int id = stoi(tokens[0]);
            bool start = tokens[1] == "start";
            int timestamp = stoi(tokens[2]);

            if (start) {
                if (!execution.empty()) {
                    result[execution.top().first] += timestamp - execution.top().second;
                    execution.top().second = timestamp - 1;
                }
                execution.push({id, timestamp});
            }
            else {
                result[id] += timestamp - execution.top().second + 1;
                execution.pop();
                if (!execution.empty()) {
                    execution.top().second = timestamp + 1;
                }
            }
        }
        return result;
    }
};