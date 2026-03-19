/*
https://www.hack2hire.com/companies/reddit/coding-questions/695572024a0202df9569e95f/practice?questionId=695572104a0202df9569e960
Merge JSON Event Logs

You are monitoring a distributed system consisting of multiple servers, where each server generates event logs recording
actions performed at specific timestamps.

A JSON data logs is provided, in which each key is a serverId representing a unique server, and the corresponding value
is a list of events describing that server's event history. Each event includes a "time" field indicating when the event
occurred, a "type" field describing the action performed (e.g., "send", "receive", "idle"), and an optional "target"
field specifying the target server when the event involves inter-server communication.

For each server, its event list is guaranteed to be sorted by "time" in ascending order.

Your task is to merge all events from all servers into a single global timeline sorted by timestamp in ascending order,
where each event in the output should be formatted as a string:

"{time}: {serverId} {type} {target}" if target exists.
"{time}: {serverId} {type}" if target does not exist.
If multiple events occur at the same timestamp, their relative order doesn't matter.

Constraints:

1 ≤ number of servers ≤ 100
Each server's event list contains at most 1000 events
Each timestamp is an integer in the range [1, 2³¹ − 1]
Each server's event list is already sorted by time in ascending order
Example:

Input: logs =
{
 "server0": [
    {
       "time": 100,
       "type": "send",
       "target": "server1"
    },
    {
        "time": 400,
        "type": "receive",
        "target": "server1"
    }
  ],
  "server1": [
    {
        "time": 200,
        "type": "receive",
        "target": "server0"
    },
    {
       "time": 300,
        "type": "send",
        "target": "server0"
    }
  ]
}

Output:
[
  "100: server0 send server1",
  "200: server1 receive server0",
  "300: server1 send server0",
  "400: server0 receive server1"
]

Explanation:
After sorting by time, the events appear in this order:

At time 100: "server0" sends to "server1" → "100: server0 send server1"
At time 200: "server1" receives from "server0" → "200: server1 receive server0"
At time 300: "server1" sends to "server0" → "300: server1 send server0"
At time 400: "server0" receives from "server1" → "400: server0 receive server1"

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
#include <optional>
using namespace std;

struct Event {
    int time;
    string type;
    string target;
};

struct HeapItem {
    int time;
    string svr_id;
    Event event;
};

struct myComp {
    bool operator()(const HeapItem &e1, const HeapItem &e2) const {
        return e1.time > e2.time;
    }
};

class Solution {
private:
    string print_event(int time, string& svr_id, Event& event) {
        string event_type = event.type;
        if (!event.target.empty()) {
            return to_string(event.time) + ": " + svr_id + " " + event_type + " " + event.target;
        }
        return to_string(event.time) + ": " + svr_id + " " + event_type;
    }
public:
    vector<string> mergeLogs(map<string, vector<Event>>& logs) {
        unordered_map<string, int> svr_indices;
        priority_queue<HeapItem, vector<HeapItem>, myComp> pq;
        for (auto& [svr_id, events] : logs) {
            svr_indices[svr_id] = 0;
            if (!events.empty()) {
                pq.push({events[0].time, svr_id, events[0]});
            }
        }

        vector<string> rst;
        while (!pq.empty()) {
            int time = pq.top().time;
            string svr_id = pq.top().svr_id;
            Event event = pq.top().event;
            pq.pop();

            rst.push_back(print_event(time, svr_id, event));
            svr_indices[svr_id] += 1;
            if (svr_indices[svr_id] < logs[svr_id].size()) {
                Event& next_event = logs[svr_id][svr_indices[svr_id]];
                pq.push({next_event.time, svr_id, next_event});
            }
        }
        return rst;
    }
};

int main() {
    std::cout << "===== Testcase 1 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs1 = {
        {"server0", {
            {100, "send", "server1"},
            {400, "receive", "server1"}
        }},
        {"server1", {
            {200, "receive", "server0"},
            {300, "send", "server0"}
        }}
    };
    auto res = mergeLogs(logs1);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: ["100: server0 send server1", "200: server1 receive server0",
    //            "300: server1 send server0", "400: server0 receive server1"]

    std::cout << "\n===== Testcase 2 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs2 = {
        {"server0", {
            {10, "idle", std::nullopt},
            {50, "send", "server1"}
        }},
        {"server1", {
            {30, "idle", std::nullopt},
            {60, "receive", "server0"}
        }}
    };
    res = mergeLogs(logs2);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: ["10: server0 idle", "30: server1 idle",
    //            "50: server0 send server1", "60: server1 receive server0"]

    std::cout << "\n===== Testcase 3 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs3 = {
        {"server0", {
            {100, "send", "server1"},
            {400, "send", "server2"}
        }},
        {"server1", {
            {200, "receive", "server0"},
            {300, "forward", "server2"}
        }},
        {"server2", {
            {350, "receive", "server1"},
            {500, "receive", "server0"}
        }}
    };
    res = mergeLogs(logs3);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: ["100: server0 send server1", "200: server1 receive server0",
    //            "300: server1 forward server2", "350: server2 receive server1",
    //            "400: server0 send server2", "500: server2 receive server0"]

    std::cout << "\n===== Testcase 4 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs4 = {
        {"server0", {
            {10, "idle", std::nullopt},
            {20, "idle", std::nullopt},
            {30, "idle", std::nullopt}
        }}
    };
    res = mergeLogs(logs4);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: ["10: server0 idle", "20: server0 idle", "30: server0 idle"]

    std::cout << "\n===== Testcase 5 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs5 = {};
    res = mergeLogs(logs5);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: []

    std::cout << "\n===== Testcase 6 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs6 = {
        {"server0", {
            {100, "send", "server1"}
        }},
        {"server1", {}}
    };
    res = mergeLogs(logs6);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: ["100: server0 send server1"]

    std::cout << "\n===== Testcase 7 =====" << std::endl;
    std::map<std::string, std::vector<Event>> logs7 = {
        {"server0", {
            {100, "start", std::nullopt},
            {500, "end", std::nullopt}
        }},
        {"server1", {
            {200, "start", std::nullopt},
            {600, "end", std::nullopt}
        }},
        {"server2", {
            {300, "start", std::nullopt},
            {700, "end", std::nullopt}
        }},
        {"server3", {
            {400, "start", std::nullopt},
            {800, "end", std::nullopt}
        }}
    };
    res = mergeLogs(logs7);
    for (const auto& line : res) {
        std::cout << "\"" << line << "\"" << (line != res.back() ? ", " : "");
    }
    std::cout << std::endl;
    // Expected: ["100: server0 start", "200: server1 start", "300: server2 start",
    //            "400: server3 start", "500: server0 end", "600: server1 end",
    //            "700: server2 end", "800: server3 end"]

    return 0;
}

