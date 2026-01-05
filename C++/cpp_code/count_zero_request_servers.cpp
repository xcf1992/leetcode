/*
https://leetcode.com/problems/count-zero-request-servers/description/
2747. Count Zero Request Servers

You are given an integer n denoting the total number of servers and a 2D 0-indexed integer array logs, where logs[i] =
[server_id, time] denotes that the server with id server_id received a request at time time.

You are also given an integer x and a 0-indexed integer array queries.

Return a 0-indexed integer array arr of length queries.length where arr[i] represents the number of servers that did not
receive any requests during the time interval [queries[i] - x, queries[i]].

Note that the time intervals are inclusive.



Example 1:

Input: n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
Output: [1,2]
Explanation:
For queries[0]: The servers with ids 1 and 2 get requests in the duration of [5, 10]. Hence, only server 3 gets zero
requests. For queries[1]: Only the server with id 2 gets a request in duration of [6,11]. Hence, the servers with ids 1
and 3 are the only servers that do not receive any requests during that time period.

Example 2:

Input: n = 3, logs = [[2,4],[2,1],[1,2],[3,1]], x = 2, queries = [3,4]
Output: [0,1]
Explanation:
For queries[0]: All servers get at least one request in the duration of [1, 3].
For queries[1]: Only server with id 3 gets no request in the duration [2,4].



Constraints:

1 <= n <= 105
1 <= logs.length <= 105
1 <= queries.length <= 105
logs[i].length == 2
1 <= logs[i][0] <= n
1 <= logs[i][1] <= 106
1 <= x <= 105
x < queries[i] <= 106
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        vector<pair<int, int>> time_server_log;
        for (auto it : logs) {
            time_server_log.push_back({it[1], it[0]});
        }
        sort(time_server_log.begin(), time_server_log.end(),
             [](pair<int, int>& a, pair<int, int>& b) { return a.first < b.first; });

        int q = queries.size();
        unordered_map<int, int> active_svr_cnt;  // to store the unique server ids in the current window
        vector<int> rst(q, 0);
        vector<pair<int, int>> query_time_idx(q);
        // store the indices of queries to store the answer in correct manner
        for (int i = 0; i < q; i++) {
            query_time_idx[i] = {queries[i], i};  // time,index
        }
        sort(query_time_idx.begin(), query_time_idx.end(),
             [](pair<int, int>& a, pair<int, int>& b) { return a.first < b.first; });  // sort on basis of time

        int start_log = 0, end_log = 0;  // i is the start of window and j is the end of window
        int log_cnt = logs.size();
        for (auto& [end_time, query_idx] : query_time_idx) {
            int start_time = max(0, end_time - x);  // finding the start time (like queries[i]-x), cant be less than 0

            // move j until the value of time in logs is not more than end
            while (end_log < log_cnt && time_server_log[end_log].first <= end_time) {
                active_svr_cnt[time_server_log[end_log].second] += 1;
                end_log += 1;
            }

            // move i until the value is not >= start
            while (start_log < log_cnt and time_server_log[start_log].first < start_time) {
                // removing out of window elements
                if (active_svr_cnt[time_server_log[start_log].second] == 1) {
                    active_svr_cnt.erase(time_server_log[start_log].second);
                } else {
                    active_svr_cnt[time_server_log[start_log].second] -= 1;
                }
                start_log += 1;
            }

            rst[query_idx] = n - active_svr_cnt.size();
        }
        return rst;
    }
};

// TLE
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        vector<set<int>> server_req_times(n, set<int>{});
        for (vector<int>& log : logs) {
            server_req_times[log[0] - 1].insert(log[1]);
        }

        vector<int> rst;
        for (int end_time : queries) {
            int start_time = end_time - x;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                auto start_it = lower_bound(server_req_times[i].begin(), server_req_times[i].end(), start_time);
                if (start_it == server_req_times[i].end()) {
                    continue;
                }
                if (*start_it >= start_time && *start_it <= end_time) {
                    cnt += 1;
                }
            }
            rst.push_back(n - cnt);
        }
        return rst;
    }
};