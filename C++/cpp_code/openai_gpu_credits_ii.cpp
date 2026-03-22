/*
https://www.hack2hire.com/companies/openai/coding-questions/6913b4290ac116974ccedd12/practice?questionId=6913b4310ac116974ccedd13
GPU Credits II

You are designing a system to manage GPU credits. Each credit grant has a unique ID and is valid during a specific time
window. Credit grants may overlap in time.

Because of network delays, events such as adding or consuming credits may arrive and be processed out of order with
respect to their timestamp. At any time, you may query the system for the total available credits at a particular
timestamp or attempt to consume credits at a specified time.

Implement the CreditSystem class:

CreditSystem() Initializes the credit system.
void grantCredit(String id, int amount, int startTime, int expirationTime) Adds a new credit grant identified by id,
with amount units. The credit is active in the interval [startTime, expirationTime - 1] inclusively.

void subtract(int amount, int timestamp) Deduct amount credits from all credits available at the specified timestamp.

Credits should be subtracted starting with grants that expire the soonest (i.e., those with the earliest expiration
time). If the total available credits at that time are less than the requested amount, use up all available credits. int
getBalance(int timestamp) Returns the number of credits available at the given timestamp.

Constraints:

No two operations (grantCredit or subtract) share the same timestamp.
All grants, usage events, and queries may arrive in any order.
All time windows are inclusive at both ends.
All amount, startTime, and expirationTime are in the range [0, 1000].
Example:

Input:
["CreditSystem", "grantCredit", "getBalance", "grantCredit", "subtract", "subtract", "getBalance", "getBalance",
"getBalance", "getBalance", "getBalance", "getBalance"]
[[], ["a", 3, 10, 60], [10], ["b", 2, 20, 40], [1, 30], [3, 50], [10], [20], [30], [35], [40], [50]]

Output:
[null, null, 3, null, null, null, 3, 5, 4, 4, 3, 0]

Explanation:

CreditSystem cs = new CreditSystem();
cs.grantCredit("a", 3, 10, 60); // Grants 3 credits for time [10, 59].
cs.getBalance(10); // Returns 3.
cs.grantCredit("b", 2, 20, 40); // Grants 2 credits for time [20, 39].
cs.subtract(1, 30); // Consumes 1 credit at t=30, deducted from the earliest-expiring grant ("b").
cs.subtract(3, 50); // Consumes 3 credits at t=50, only grant "a" is available.
cs.getBalance(10); // Returns 3. Only grant "a" active at t = 10.
cs.getBalance(20); // Returns 5. Both "a" and "b" are active at t = 20.
cs.getBalance(30); // Returns 4. Only 1 credit has been consumed at t = 30.
cs.getBalance(35); // Returns 4.
cs.getBalance(40); // Returns 3. Only "a" is active at t = 40.
cs.getBalance(50); // Returns 0. The remaining 3 credits are consumed.

*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
using namespace std;

struct Grant {
    int end;
    int amount;
    Grant(int end, int amount) : end(end), amount(amount) {}
};

struct GrantComp {
    bool operator()(const Grant& a, const Grant& b) {
        return a.end > b.end;
    }
};

class CreditSystem {
private:
    map<int, vector<Grant>> start_to_grants_;
    map<int, int> time_to_sub_;

public:
    CreditSystem() {
        start_to_grants_ = map<int, vector<Grant>>();
        time_to_sub_ = map<int, int>();
    }

    void grantCredit(string id, int amount, int startTime, int expirationTime) {
        if (start_to_grants_.find(startTime) == start_to_grants_.end()) {
            start_to_grants_[startTime] = vector<Grant>();
        }
        start_to_grants_[startTime].push_back(Grant(expirationTime, amount));
    }

    void subtract(int amount, int timestamp) {
        time_to_sub_[timestamp] += amount;
    }

    int getBalance(int timestamp) {
        set<int> all_times;
        for (auto& [start_time, grants] : start_to_grants_) {
            if (start_time <= timestamp) {
                all_times.insert(start_time);
            }
        }

        for (auto& [time, sub] : time_to_sub_) {
            if (time <= timestamp) {
                all_times.insert(time);
            }
        }

        priority_queue<Grant, vector<Grant>, GrantComp> pq;
        for (int time : all_times) {
            while (!pq.empty() && pq.top().end <= time) {
                pq.pop();
            }

            if (start_to_grants_.find(time) != start_to_grants_.end()) {
                for (Grant& grant : start_to_grants_[time]) {
                    pq.push(Grant(grant.end, grant.amount));
                }
            }

            if (time_to_sub_.find(time) != time_to_sub_.end()) {
                int sub_amt = time_to_sub_[time];
                while (sub_amt > 0 && !pq.empty()) {
                    Grant cur = pq.top();
                    pq.pop();

                    int used = min(cur.amount, sub_amt);
                    cur.amount -= used;
                    sub_amt -= used;
                    if (cur.amount > 0) {
                        pq.push(cur);
                    }
                }
            }
        }

        int rst = 0;
        while (!pq.empty() && pq.top().end <= timestamp) {
            pq.pop();
        }

        while (!pq.empty()) {
            rst += pq.top().amount;
            pq.pop();
        }
        return max(rst, 0);
    }
};