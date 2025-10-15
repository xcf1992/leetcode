/*
93. Restore IP Addresses

Given a string containing only digits,
restore it by returning all possible valid IP address combinations.

Example:
Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    void dfs(string s, vector<string>& result, int start, int step, string ip) {
        if (s.size() < start or step > 4) {
            return;
        }

        if (step == 4) {
            if (s.size() == start) {
                ip = ip.substr(1);
                result.push_back(ip);
            }
            return;
        }

        for (int len = 1; len <= 3 and start + len <= s.size(); ++len) {
            string tip = s.substr(start, len);
            if (len == 1 or (tip[0] != '0' and stoi(tip) <= 255)) {
                dfs(s, result, start + len, step + 1, ip + "." + tip);
            }
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.empty() or s.size() > 3 * 4 or s.size() < 4) {
            return {};
        }

        vector<string> result;
        dfs(s, result, 0, 0, "");
        return result;
    }
};
