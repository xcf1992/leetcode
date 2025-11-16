/*
981. Time Based Key-Value Store
https://leetcode.com/problems/time-based-key-value-store/

Create a timebased key-value store class TimeMap,
that supports two operations.

1. set(string key, string value, int timestamp)
Stores the key and value, along with the given timestamp.

2. get(string key, int timestamp)
Returns a value such that set(key, value, timestamp_prev) was called previously, with timestamp_prev <= timestamp.
If there are multiple such values, it returns the one with the largest timestamp_prev.
If there are no values, it returns the empty string ("").

Example 1:
Input: inputs = ["TimeMap","set","get","get","set","get","get"], inputs =
[[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]] Output:
[null,null,"bar","bar",null,"bar2","bar2"] Explanation: TimeMap kv; kv.set("foo", "bar", 1); // store the key "foo" and
value "bar" along with timestamp = 1 kv.get("foo", 1);  // output "bar" kv.get("foo", 3); // output "bar" since there is
no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 ie "bar"
kv.set("foo", "bar2", 4);
kv.get("foo", 4); // output "bar2"
kv.get("foo", 5); //output "bar2"

Example 2:
Input: inputs = ["TimeMap","set","set","get","get","get","get","get"], inputs =
[[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]] Output:
[null,null,null,"","high","high","low","low"]

Note:
All key/value strings are lowercase.
All key/value strings have length in the range [1, 100]
The timestamps for all TimeMap.set operations are strictly increasing.
1 <= timestamp <= 10^7
TimeMap.set and TimeMap.get functions will be called a total of 120000 times (combined) per test case.
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

class TimeMap {
private:
    unordered_map<string, map<int, string>> key_time_store_;

public:
    /* Initialize your data structure here.*/
    TimeMap() {
        key_time_store_.clear();
    }

    void set(string key, string value, int timestamp) {
        key_time_store_[key][timestamp] = value;
    }

    string get(string key, int timestamp) {
        // If the 'key' does not exist in map we will return empty string.
        if (key_time_store_.find(key) == key_time_store_.end()) {
            return "";
        }

        auto it = key_time_store_[key].upper_bound(timestamp);
        // If iterator points to first element it means, no time <= timestamp exists.
        if (it == key_time_store_[key].begin()) {
            return "";
        }

        // Return value stored at previous position of current iterator.
        return prev(it)->second;
    }
};

/*
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

// TLE
class TimeMap1 {
private:
    unordered_map<string, vector<pair<int, string>>> timeBasedMap;

public:
    /* Initialize your data structure here.*/
    TimeMap1() {
        timeBasedMap.clear();
    }

    void set(string key, string value, int timestamp) {
        timeBasedMap[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (timeBasedMap.find(key) == timeBasedMap.end()) {
            return "";
        }

        vector<pair<int, string>> timedValues = timeBasedMap[key];
        auto it = lower_bound(timedValues.begin(), timedValues.end(), timestamp,
                              [](pair<int, string>& a, int t) { return a.first < t; });

        if (it == timedValues.end()) {
            return timedValues.back().second;
        }
        if (it->first == timestamp) {
            return it->second;
        }
        if (it == timedValues.begin()) {
            return "";
        }
        return (--it)->second;
    }
};