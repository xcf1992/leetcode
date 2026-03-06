/*
https://www.hack2hire.com/companies/stripe/coding-questions/69753e1a17272b5c868d5eb2/practice?questionId=69753e2817272b5c868d5eb3
Compute Server Load Scores
A cloud infrastructure provider is developing a load-balancing system to monitor server stress levels and optimize
resource allocation. To support this goal, you are given a dataset representing all incoming requests for a single day,
along with a load rule for each request and a list of servers with their base load scores. Your task is to compute the
load score for every server after processing all requests according to specific rules.

Each server's load score is calculated by applying three independent categories of stress evaluation to every request:

Heavy Payload Multiplication:
For a given request, if the payloadSize is greater than the corresponding rule's minimum payload size (minPayloadSize),
multiply the server's current score by the rule's CPU multiplier (cpuMultiplier).

Sticky Session Overhead:
For every server-client pair, once the third or subsequent request occurs (counting all such requests made by the same
client to the same server on that day), add the corresponding rule's memory overhead (memoryOverhead) to the server's
score for each request made so far for that pair, including the current request. When the third request occurs, the
memory overheads from the first, second, and third requests are applied together. After that, each additional request
increases the score by only its own memory overhead.

Traffic Burst Adjustment:
For every server-client-hour group, when the third or subsequent request occurs within the same hour, apply the rule's
bandwidthPenalty as follows:

If the hour is between 12 and 17 (inclusive), add the penalty for each request in this group so far (representing peak
traffic surge). If the hour is between 9 and 11 (inclusive) or 18 and 21 (inclusive), subtract the penalty for each
request in this group so far (representing optimization during maintenance windows). If the hour is outside these
ranges, no penalty is applied. All categories are applied to every request, and each server's score is updated in the
order described above.

The input data contains:

requestsList: Each element is a comma-separated string "<serverId>,<payloadSize>,<clientId>,<hour>" with the following
fields:

serverId: ID of the server receiving the request
payloadSize: Size of the request payload (integer).
clientId: ID of the client making the request.
hour: Hour of the request (integer).
rulesList: Each element corresponds to a request in requestsList and is a comma-separated string formatted as:
"<minPayloadSize>,<cpuMultiplier>,<memoryOverhead>,<bandwidthPenalty>".

minPayloadSize: Minimum payload size to trigger the multiplier rule (integer).
cpuMultiplier: Multiplicative factor used in the rule (integer).
memoryOverhead: Additive factor used in the rule (integer).
bandwidthPenalty: Penalty/adjustment applied if the rule conditions are met (integer).
serversList: Each element is a string formatted as: "<serverId>,<baseScore>".

serverId: ID of the server as mentioned above.
baseScore: Base load score of the server (integer).
Return a list of comma-separated strings, where each string is in the format "<serverId>,<loadScore>". The result must
be ordered by serverId in lexicographical order.

Constraints:

1 ≤ requestsList.length, rulesList.length, serversList.length ≤ 1000
1 ≤ baseScore ≤ 50
0 ≤ hour ≤ 23
No integer overflow will occur.
All server and client IDs are non-empty strings. All sizes, factors, and penalties are integers.
Example 1:

Input: requestsList = ["server1,1200,client1,10",
                       "server1,500,client1,10",
                       "server2,2400,client1,15",
                       "server1,800,client1,16",
                       "server1,1000,client2,17",
                       "server1,1400,client1,10"],
rulesList = ["1000,2,8,15", "1400,5,3,19", "2300,3,17,3", "1800,2,9,6", "1000,4,8,2", "1200,3,11,7"],
serversList = ["server1,10", "server2,20"]
Output: ["server1,50", "server2,60"]
Explanation: "server1" starts with a base score of 10 and "server2" with 20. As each request is processed, the rules are
applied to update their scores according to the three stress categories described above.

Example 2:

Input: requestsList = ["server1,1200,client1,10"], rulesList = ["1000,2,8,15"], serversList = ["server1,10"]
Output: ["server1,20"]

Example 3:

Input: requestsList = ["server1,500,client1,10", "server1,500,client1,10", "server1,500,client1,10"], rulesList =
["1000,2,5,10", "1000,2,5,10", "1000,2,5,10"], serversList = ["server1,10"] Output: ["server1,-5"]
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
using namespace std;

struct Request {
    string svr_id;
    int payload_size;
    string cli_id;
    int hour;

    Request(string serverId, int payloadSize, string clientId, int hour)
            : svr_id(serverId), payload_size(payloadSize), cli_id(clientId), hour(hour) {
    }
};

struct LoadRule {
    int min_payload_size;
    int cpu_multiplier;
    int memo_overhead;
    int bandwidth_penalty;

    LoadRule(int minPayloadSize, int cpuMultiplier, int memoryOverhead, int bandwidthPenalty)
            : min_payload_size(minPayloadSize),
              cpu_multiplier(cpuMultiplier),
              memo_overhead(memoryOverhead),
              bandwidth_penalty(bandwidthPenalty) {
    }
};

class Solution {
public:
    vector<string> serverLoadScoreCheck(vector<string> requestsList, vector<string> rulesList,
                                        vector<string> serversList) {
        int n = requestsList.size();
        vector<Request> requests;
        vector<LoadRule> rules;
        for (int i = 0; i < n; i++) {
            vector<string> requestParts = split(requestsList[i], ',');
            requests.push_back(Request(requestParts[0], stoi(requestParts[1]), requestParts[2], stoi(requestParts[3])));

            vector<string> ruleParts = split(rulesList[i], ',');
            rules.push_back(LoadRule(stoi(ruleParts[0]), stoi(ruleParts[1]), stoi(ruleParts[2]), stoi(ruleParts[3])));
        }

        // Initialize server scores
        map<string, long long> scores;
        for (const string& server : serversList) {
            vector<string> parts = split(server, ',');
            scores[parts[0]] = stoll(parts[1]);
        }

        // Heavy Payload Multiplication (payloadSize > minPayloadSize)
        for (int i = 0; i < n; i = i + 1) {
            Request req = requests[i];
            LoadRule rule = rules[i];
            if (req.payload_size > rule.min_payload_size) {
                long long curScore = scores[req.svr_id];
                scores[req.svr_id] = curScore * rule.cpu_multiplier;
            }
        }

        // Sticky Session Overhead (3+ requests per server-client pair)
        unordered_map<string, int> overhead_cnt;
        unordered_map<string, long long> overhead_pending;
        for (int i = 0; i < n; i = i + 1) {
            Request req = requests[i];
            LoadRule rule = rules[i];
            string key = req.svr_id + ":" + req.cli_id;

            overhead_cnt[key] += 1;
            if (overhead_cnt[key] < 3) {
                // Accumulate pending memory overheads
                overhead_pending[key] += rule.memo_overhead;
            } else if (overhead_cnt[key] == 3) {
                scores[req.svr_id] += overhead_pending[key] + rule.memo_overhead;
            } else {
                // Apply only current request
                scores[req.svr_id] += rule.memo_overhead;
            }
        }

        // Traffic Burst Adjustment
        unordered_map<string, int> burst_cnt;
        unordered_map<string, long long> burst_pending;
        for (int i = 0; i < n; i = i + 1) {
            Request req = requests[i];
            LoadRule rule = rules[i];
            string key = req.svr_id + ":" + req.cli_id + ":" + to_string(req.hour);
            burst_cnt[key] += 1;

            // Determine penalty effect based on hour
            int effect = get_traffic_adjustment_effect(req.hour);
            if (effect == 0) {
                continue;
            }
            long long adj_val = rule.bandwidth_penalty * effect;

            if (burst_cnt[key] < 3) {
                // Accumulate pending adjustments
                burst_pending[key] += adj_val;
            } else if (burst_cnt[key] == 3) {
                // Apply pending sum + current
                scores[req.svr_id] += burst_pending[key] + adj_val;
            } else {
                // Apply only current request
                scores[req.svr_id] += adj_val;
            }
        }

        vector<string> rst;
        for (const auto& entry : scores) {
            rst.push_back(entry.first + "," + to_string(entry.second));
        }
        return rst;
    }

private:
    // Returns: 1 for add penalty (peak), -1 for subtract penalty (off-peak), 0 for no-op
    int get_traffic_adjustment_effect(int hour) {
        if (hour >= 12 && hour <= 17) {
            return 1;
        }
        if ((hour >= 9 && hour <= 11) || (hour >= 18 && hour <= 21)) {
            return -1;
        }
        return 0;
    }

    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};
