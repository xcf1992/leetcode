/*
635. Design Log Storage System
https://leetcode.com/problems/design-log-storage-system/

You are given several logs that each log contains a unique id and timestamp.
Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second,
for example, 2017:01:01:23:59:59.
All domains are zero-padded decimal numbers.

Design a log storage system to implement the following functions:

void Put(int id, string timestamp):
Given a log's unique id and timestamp, store the log in your storage system.

int[] Retrieve(String start, String end, String granularity):
Return the id of logs whose timestamps are within the range from start to end.

Start and end all have the same format as timestamp.
However, granularity means the time level for consideration.
For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", granularity = "Day",
it means that we need to find the logs within the range from Jan. 1st 2017 to Jan. 2nd 2017.

Example 1:
put(1, "2017:01:01:23:59:59");
put(2, "2017:01:01:22:59:59");
put(3, "2016:01:01:00:00:00");
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year");
// return [1,2,3], because you need to return all logs within 2016 and 2017.

retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour");
// return [1,2], because you need to return all logs start from 2016:01:01:01 to 2017:01:01:23,
where log 3 is left outside the range.

Note:
There will be at most 300 operations of Put or Retrieve.
Year ranges from [2000,2017]. Hour ranges from [00,23].
Output for Retrieve has no order required.
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
#include <map>
#include <climits>
using namespace std;

class LogSystem {
private:
    multimap<string, int> timeToId;
    string low = "2000:00:00:00:00:00";
    string high = "2017:12:31:23:59:59";
    unordered_map<string, int> digits = {{"Year", 4},  {"Month", 7},   {"Day", 10},
                                         {"Hour", 13}, {"Minute", 16}, {"Second", 19}};

public:
    LogSystem() {
    }

    void put(int id, string timestamp) {
        timeToId.emplace(timestamp, id);
    }

    vector<int> retrieve(string s, string e, string gra) {
        int len = digits[gra];
        string start = s.substr(0, len) + low.substr(len);
        string end = e.substr(0, len) + high.substr(len);

        vector<int> result;
        for (auto it = timeToId.lower_bound(start); it != timeToId.upper_bound(end); it++) {
            result.push_back(it->second);
        }
        return result;
    }
};

/*
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */