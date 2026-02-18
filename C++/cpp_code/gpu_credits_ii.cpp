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
#include <climits>
using namespace std;

struct Grant {
    int end;
    int amount;
    Grant(int end, int amount) : end(end), amount(amount) {}
};

struct ActiveGrant {
    int end;
    int remain;
    ActiveGrant(int end, int remain) : end(end), remain(remain) {}
};

struct ActiveGrantComp {
    bool operator()(const ActiveGrant& a, const ActiveGrant& b) {
        return a.end > b.end;
    }
};

class CreditSystem {
private:
    map<int, vector<Grant>> start_to_grants_;
    map<int, int> time_to_sub_;

public:
    CreditSystem() {
    }

    void grantCredit(string id, int amount, int startTime, int expirationTime) {
        if (start_to_grants_.find(startTime) == start_to_grants_.end()) {
            start_to_grants_[startTime] = vector<Grant>();
        }
        start_to_grants_[startTime].push_back(Grant(expirationTime, amount));
    }

    void subtract(int amount, int timestamp) {

    }

    int getBalance(int timestamp) {
        int total = 0;
        for (auto& [time, amount] : time_to_credit_change_) {
            if (time <= timestamp) {
                total += amount;
            } else {
                break;
            }
        }

        if (time_to_credit_sub_.find(timestamp) == time_to_credit_sub_.end()) {
            return total;
        }

        int sub = time_to_credit_sub_[timestamp];
        return total >= sub ? total - sub : -1;
    }
};