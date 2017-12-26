#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <stdio.h>
using namespace std;

class LogSystem {
private:
    multimap<string, int> timeToId;

    string low = "2000:00:00:00:00:00";
    string high = "2017:12:31:23:59:59";
    unordered_map<string, int> map = {{"Year", 4}, {"Month", 7}, {"Day", 10}, {"Hour", 13}, {"Minute", 16}, {"Second", 19}};
public:
    LogSystem() {}

    void put(int id, string timestamp) {
        timeToId.emplace(timestamp, id);
    }

    vector<int> retrieve(string s, string e, string gra) {
        int len = map[gra];
        string start = s.substr(0, len) + low.substr(len);
        string end = e.substr(0, len) + high.substr(len);
        vector<int> result;
        for (auto it = timeToId.lower_bound(start); it != timeToId.upper_bound(end); it++) {
            result.push_back(it -> second);
        }
        return result;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */