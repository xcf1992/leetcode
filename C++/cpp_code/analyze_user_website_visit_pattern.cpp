/*
1152. Analyze User Website Visit Pattern
https://leetcode.com/problems/analyze-user-website-visit-pattern/

You are given three arrays username,
timestamp and website of the same length N
where the ith tuple means that the user with name username[i] visited the website website[i] at time timestamp[i].

A 3-sequence is a list of not necessarily different websites of length 3 sorted in ascending order by the time of their
visits.

Find the 3-sequence visited at least once by the largest number of users.
If there is more than one solution,
return the lexicographically minimum solution.

A 3-sequence X is lexicographically smaller than a 3-sequence Y
if X[0] < Y[0] or X[0] == Y[0] and (X[1] < Y[1] or X[1] == Y[1] and X[2] < Y[2]).

It is guaranteed that there is at least one user who visited at least 3 websites.
No user visits two websites at the same time.

Example 1:

Input: username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], timestamp =
[1,2,3,4,5,6,7,8,9,10], website = ["home","about","career","home","cart","maps","home","home","about","career"] Output:
["home","about","career"] Explanation: The tuples in this example are:
["joe", 1, "home"]
["joe", 2, "about"]
["joe", 3, "career"]
["james", 4, "home"]
["james", 5, "cart"]
["james", 6, "maps"]
["james", 7, "home"]
["mary", 8, "home"]
["mary", 9, "about"]
["mary", 10, "career"]
The 3-sequence ("home", "about", "career") was visited at least once by 2 users.
The 3-sequence ("home", "cart", "maps") was visited at least once by 1 user.
The 3-sequence ("home", "cart", "home") was visited at least once by 1 user.
The 3-sequence ("home", "maps", "home") was visited at least once by 1 user.
The 3-sequence ("cart", "maps", "home") was visited at least once by 1 user.


Note:

3 <= N = username.length = timestamp.length = website.length <= 50
1 <= username[i].length <= 10
0 <= timestamp[i] <= 10^9
1 <= website[i].length <= 10
Both username[i] and website[i] contain only lowercase characters.
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
    vector<string> splitWeb(string web) {
        vector<string> result;
        int pos = web.find('_');
        while (pos != string::npos) {
            result.push_back(web.substr(0, pos));
            web = web.substr(pos + 1);
            pos = web.find('_');
        }
        result.push_back(web);
        return result;
    }

public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        unordered_map<string, vector<pair<int, string>>> visit;
        for (int i = 0; i < username.size(); ++i) {
            visit[username[i]].push_back({timestamp[i], website[i]});
        }

        unordered_map<string, int> count;
        for (auto& it : visit) {
            vector<pair<int, string>> timeWeb = it.second;
            if (timeWeb.size() < 3) {
                continue;
            }

            sort(timeWeb.begin(), timeWeb.end(),
                 [](pair<int, string>& a, pair<int, string>& b) { return a.first < b.first; });
            int n = timeWeb.size();
            unordered_set<string> webPattern;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    for (int k = j + 1; k < n; ++k) {
                        webPattern.insert(timeWeb[i].second + "_" + timeWeb[j].second + "_" + timeWeb[k].second);
                    }
                }
            }
            for (string pattern : webPattern) {
                count[pattern] += 1;
            }
        }

        vector<string> result;
        int maxVisit = 0;
        for (auto& it : count) {
            if (it.second > maxVisit) {
                maxVisit = it.second;
                result = splitWeb(it.first);
            } else if (it.second == maxVisit) {
                vector<string> cur = splitWeb(it.first);
                if (result[0] > cur[0] or (result[0] == cur[0] and result[1] > cur[1]) or
                    (result[0] == cur[0] and result[1] == cur[1] and result[2] > cur[2])) {
                    result = cur;
                }
            }
        }
        return result;
    }
};