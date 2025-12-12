/*
https://leetcode.com/problems/count-mentions-per-user/description
3433. Count Mentions Per User

You are given an integer numberOfUsers representing the total number of users and an array events of size n x 3.

Each events[i] can be either of the following two types:

Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
This event indicates that a set of users was mentioned in a message at timestampi.
The mentions_stringi string can contain one of the following tokens:
id<number>: where <number> is an integer in range [0,numberOfUsers - 1]. There can be multiple ids separated by a single
whitespace and may contain duplicates. This can mention even the offline users. ALL: mentions all users. HERE: mentions
all online users. Offline Event: ["OFFLINE", "timestampi", "idi"] This event indicates that the user idi had become
offline at timestampi for 60 time units. The user will automatically be online again at time timestampi + 60. Return an
array mentions where mentions[i] represents the number of mentions the user with id i has across all MESSAGE events.

All users are initially online, and if a user goes offline or comes back online, their status change is processed before
handling any message event that occurs at the same timestamp.

Note that a user can be mentioned multiple times in a single message event, and each mention should be counted
separately.



Example 1:

Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]

Output: [2,2]

Explanation:

Initially, all users are online.

At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]

At timestamp 11, id0 goes offline.

At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]

Example 2:

Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]

Output: [2,2]

Explanation:

Initially, all users are online.

At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]

At timestamp 11, id0 goes offline.

At timestamp 12, "ALL" is mentioned. This includes offline users, so both id0 and id1 are mentioned. mentions = [2,2]

Example 3:

Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]

Output: [0,1]

Explanation:

Initially, all users are online.

At timestamp 10, id0 goes offline.

At timestamp 12, "HERE" is mentioned. Because id0 is still offline, they will not be mentioned. mentions = [0,1]



Constraints:

1 <= numberOfUsers <= 100
1 <= events.length <= 100
events[i].length == 3
events[i][0] will be one of MESSAGE or OFFLINE.
1 <= int(events[i][1]) <= 105
The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
0 <= <number> <= numberOfUsers - 1
It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    void process_message(vector<string>& event, vector<int>& rst, vector<int>& next_online_time) {
        int cur_time = stoi(event[1]);
        if (event[2] == "ALL") {
            for (int i = 0; i < rst.size(); i++) {
                rst[i] += 1;
            }
        } else if (event[2] == "HERE") {
            for (int i = 0; i < rst.size(); i++) {
                if (next_online_time[i] <= cur_time) {
                    rst[i] += 1;
                }
            }
        } else {
            int user_id = 0;
            for (int i = 0 ; i < event[2].size(); i++) {
                if (isdigit(event[2][i])) {
                    user_id = user_id * 10 + (event[2][i] - '0');
                }

                if (i + 1 == event[2].size() || event[2][i + 1] == ' ') {
                    rst[user_id] += 1;
                    user_id = 0;
                }
            }
        }
    }
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        sort(events.begin(), events.end(), [&](vector<string>& a, vector<string>& b) {
            int a_time = stoi(a[1]);
            int b_time = stoi(b[1]);
            if (a_time != b_time) {
                return a_time < b_time;
            }
            if (b[0] == "OFFLINE") {
                return false;
            }
            return true;
        });

        vector<int> rst(numberOfUsers, 0);
        vector<int> next_online_time(numberOfUsers, 0);
        for (vector<string>& event : events) {
            if (event[0] == "MESSAGE") {
                process_message(event, rst, next_online_time);
            } else {
                int cur_time = stoi(event[1]);
                int user_id = stoi(event[2]);
                next_online_time[user_id] = cur_time + 60;
            }
        }
        return rst;
    }
};