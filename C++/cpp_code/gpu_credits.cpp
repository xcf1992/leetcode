/*
https://www.hack2hire.com/companies/openai/coding-questions/69117144869dd6a56c434053/practice?questionId=69117148869dd6a56c434054
GPU Credits

You are designing a system to manage GPU credits. Each credit grant has a unique ID and is valid during a specific time
window. Credit grants may overlap in time.

Because of network delays, events such as adding or consuming credits may arrive and be processed out of order with
respect to their timestamp. At any time, you may query the system for the total available credits at a particular
timestamp or attempt to revoke credits at a specified time.

Implement the CreditSystem class:

CreditSystem() Initializes the credit system.
void grantCredit(String id, int amount, int startTime, int expirationTime) Adds a new credit grant identified by id,
with amount units. The credit is active for all times in the interval [startTime, expirationTime - 1] inclusively.

void subtract(int amount, int timestamp) Revoke amount credits from all currently available credits at the specified
timestamp only. This operation does not affect any available credit in the future timestamp.

int getBalance(int timestamp) Returns the number of credits available at the given timestamp. If usage at the given time
exceeds the total available credits, return -1.

Constraints:

No two operations (grantCredit or subtract) share the same timestamp.
All grants, usage events, and queries may arrive in any order.
All amount, startTime, and expirationTime are in the range [0, 1000].
Example:

Input:
["CreditSystem", "grantCredit", "getBalance", "grantCredit", "subtract", "subtract", "getBalance", "getBalance",
"getBalance", "getBalance", "getBalance", "getBalance"]
[[], ["a", 3, 10, 60], [10], ["b", 2, 20, 40], [1, 30], [3, 50], [10], [20], [30], [35], [40], [50]]

Output:
[null, null, 3, null, null, null, 3, 5, 4, 5, 3, 0]

Explanation:

CreditSystem cs = new CreditSystem();
cs.grantCredit("a", 3, 10, 60); // Grants 3 credits for time [10, 59].
cs.getBalance(10); // Returns 3.
cs.grantCredit("b", 2, 20, 40); // Grants 2 credits for time [20, 39].
cs.subtract(1, 30); // Revoke 1 credit at t = 30.
cs.subtract(3, 50); // Revoke 3 credits at t = 50.
cs.getBalance(10); // Returns 3. Only grant "a" active at t = 10.
cs.getBalance(20); // Returns 5. Both "a" and "b" are active at t = 20.
cs.getBalance(30); // Returns 4. Only 1 credit was revoked at t = 30.
cs.getBalance(35); // Returns 5. Both "a" and "b" are active at t = 35.
cs.getBalance(40); // Returns 3. Only "a" is active at t = 40.
cs.getBalance(50); // Returns 0. The remaining 3 credits are revoked.
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

class CreditSystem {
private:
    map<int, int> time_to_credit_change_;
    unordered_map<int, int> time_to_credit_sub_;
public:
    CreditSystem() {
        time_to_credit_change_ = map<int, int>();
        time_to_credit_sub_ = unordered_map<int, int>();
    }

    void grantCredit(string id, int amount, int startTime, int expirationTime) {
        time_to_credit_change_[startTime] += amount;
        time_to_credit_change_[expirationTime] -= amount;
    }

    void subtract(int amount, int timestamp) {
        time_to_credit_sub_[timestamp] += amount;
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