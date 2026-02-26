/*
https://www.hack2hire.com/companies/reddit/coding-questions/69499eb489ec36a1b1e2c13e/practice?questionId=69499ed489ec36a1b1e2c13f
Reconstruct Billing Status

An advertising platform lost its primary database that stored advertisers' current billing status. Fortunately, the
system still retains a complete historical log of all financial transactions. Your task is to reconstruct the final
billing status for each user using this transaction history.

You are given a 2D list of unordered transactions, where each element represents a single transaction made by one user.
Each transaction may record an ad delivery charge, a payment, or both. Some monetary fields may be missing (provided as
"") and should be ignored.

Each transaction record is in the format: [<transactionId>, <userId>, <adDeliveryPennies>, <paymentPennies>,
<transactionTimestamp>]

transactionId: A unique transaction identifier.
userId: String, unique identifier of the user (e.g., "u1", "u2")
adDeliveryPennies: The ad delivery cost in pennies, or an empty string "" if not present.
paymentPennies: The payment amount in pennies, or an empty string "" if not present.
transactionTimestamp: The transaction time, represented as a string integer.
For each user, compute two totals starting from 0:

totalAdDeliveryPennies: The total ad delivery cost in pennies.
totalPaymentPennies: The total payment amount in pennies.
After processing all transactions, return each user's final billing status in the following format:[<userId>,
<totalAdDeliveryPennies>, <totalPaymentPennies>]. The output list should be ordered by userId in ascending lexicographic
order.

Constraints

1 ≤ transactions.length ≤ 10⁵
Each transaction contains exactly 5 elements.
adDeliveryPennies and paymentPennies are either empty strings or strings representing non-negative integers.
Example 1:

Input:
transactions =
[
  ["t1", "u1", "1000", "", "1"],
  ["t2", "u1", "1000", "", "2"],
  ["t3", "u1", "", "500", "3"],
  ["t4", "u1", "1000", "500", "4"]
]
Output: [["u1", "3000", "1000"]]
Explanation: All transactions belong to the same user with userId "u1". After processing all transactions, the final ad
delivery total is $3000 (1000 + 1000 + 1000), and the final payment total is $1000 (500 + 500).

Example 2:

Input:
transactions =
[
  ["t1", "u1", "500", "", "1"],
  ["t2", "u2", "300", "", "2"],
  ["t3", "u1", "", "200", "3"],
  ["t4", "u2", "", "100", "4"]
]

Output: [["u1", "500", "200"], ["u2", "300", "100"]]

Example 3:

Input:
transactions =
[
  ["t1", "u1", "5000", "1000", "1"],
  ["t2", "u2", "3000", "", "2"],
  ["t3", "u3", "", "2000", "3"],
  ["t4", "u1", "2500", "", "4"],
  ["t5", "u2", "", "1500", "5"],
  ["t6", "u3", "4000", "3000", "6"],
  ["t7", "u1", "1500", "500", "7"],
  ["t8", "u2", "2000", "1000", "8"],
  ["t9", "u3", "3500", "", "9"],
  ["t10", "u1", "", "2000", "10"]
]

Output: [["u1", "9000", "3500"], ["u2", "5000", "2500"], ["u3", "7500", "5000"]]
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

struct UserBillingStatus {
    string usr_id;
    int delivery_pennies;
    int payment_pennies;

    UserBillingStatus() {
    }

    UserBillingStatus(string id) {
        this->usr_id = id;
        this->delivery_pennies = 0;
        this->payment_pennies = 0;
    }
};

class Solution {
private:
    map<string, UserBillingStatus> billing_status_;

    unordered_map<string, vector<vector<string>>> applied_txns_;
    unordered_map<string, vector<vector<string>>> undo_txns_;
public:
    vector<vector<string>> processTransactions(vector<vector<string>> transactions) {
        sort(transactions.begin(), transactions.end(),
             [](vector<string>& a, vector<string>& b) { return stoll(a[4]) < stoll(b[4]); });

        for (vector<string>& transaction : transactions) {
            string usr_id = transaction[1];
            bool is_undo = transaction.size() > 6 && transaction[6] == "true";
            bool is_redo = transaction.size() > 7 && transaction[7] == "true";

            if (applied_txns_.find(usr_id) == applied_txns_.end()) {
                applied_txns_[usr_id] = vector<vector<string>>();
            }
            if (undo_txns_.find(usr_id) == undo_txns_.end()) {
                undo_txns_[usr_id] = vector<vector<string>>();
            }

            vector<vector<string>>& usr_applied_trxns = applied_txns_[usr_id];
            vector<vector<string>>& undo_stk = undo_txns_[usr_id];
            if (is_undo) {
                if (!usr_applied_trxns.empty()) {
                    undo_stk.push_back(usr_applied_trxns.back());
                    usr_applied_trxns.pop_back();
                }
            } else if (is_redo) {
                if (!undo_stk.empty()) {
                    usr_applied_trxns.push_back(undo_stk.back());
                    undo_stk.pop_back();
                }
            } else {
                usr_applied_trxns.push_back(transaction);
                undo_stk.clear();
            }
        }

        for (auto& [usr_id, transactions] : applied_txns_) {
            for (vector<string>& transaction : transactions) {
                string tran_id = transaction[0];
                string delivery_pennies = transaction[2];
                string payment_pennies = transaction[3];
                string time_stamp = transaction[4];
                bool overwrite = transaction[5] == "true";

                if (billing_status_.find(usr_id) == billing_status_.end()) {
                    billing_status_[usr_id] = UserBillingStatus(usr_id);
                }

                UserBillingStatus& billing_status = billing_status_[usr_id];
                if (delivery_pennies != "") {
                    billing_status.delivery_pennies += stoi(delivery_pennies);
                    if (overwrite) {
                        billing_status.delivery_pennies = stoi(delivery_pennies);
                    }
                }
                if (payment_pennies != "") {
                    billing_status.payment_pennies += stoi(payment_pennies);
                    if (overwrite) {
                        billing_status.payment_pennies = stoi(payment_pennies);
                    }
                }
            }
        }

        vector<vector<string>> rst;
        for (auto& [usr_id, status] : billing_status_) {
            rst.push_back({usr_id, to_string(status.delivery_pennies), to_string(status.payment_pennies)});
        }
        return rst;
    }
};

/*
Follow-up 1:
Now let's add a concept of an overwrite transaction, where each transaction may indicate whether its monetary values
should overwrite a user's current billing values or be added to them.

Each transaction is given in the following format: [<transactionId>, <userId>, <adDeliveryPennies>, <paymentPennies>,
<transactionTimestamp>, <overwrite>], where:

(New) overwrite: A string value "true", "false".
For a monetary field that is present in a transaction:

If overwrite is "true", the corresponding value in the user's billing status is replaced by the transaction value.
If overwrite is "false", the transaction value is added to the current total, following the same accumulation rules as
in the previous question. After processing all transactions, return each user's final billing status in the following
format:[<userId>, <totalAdDeliveryPennies>, <totalPaymentPennies>]. The output list should be ordered by userId in
ascending lexicographic order.

Example 1:

Input:
transactions =
[
  ["t1", "u1", "1000", "", "1", "false"],
  ["t2", "u2", "1000", "", "1", "false"],
  ["t3", "u1", "1000", "", "2", "false"],
  ["t4", "u2", "1000", "", "2", "false"],
  ["t5", "u2", "1000", "500", "3", "false"],
  ["t6", "u1", "", "500", "3", "false"],
  ["t7", "u2", "1000", "", "4", "false"],
  ["t8", "u1", "1000", "500", "4", "true"],
  ["t9", "u2", "", "2000", "5", "true"],
  ["t10", "u2", "", "600", "7", "false"],
  ["t11", "u1", "", "100", "13", "false"]
]
Output: [["u1", "1000", "600"], ["u2", "4000", "2600"]]
Explanation:

For user "u1":

Ad delivery values 1000 and 1000 are added first.
Payment value 500 is added.
An overwrite transaction replaces ad delivery with 1000 and payment with 500.
A later payment of 100 is added.
Final totals are ad delivery = 1000 and payment = 600.
For user "u2":

Ad delivery values 1000, 1000, and 1000 are added.
Payment value 500 is added.
An overwrite transaction replaces the payment total with 2000.
A later payment of 600 is added.
Final totals are ad delivery = 4000 and payment = 2600.
Example 2:

Input:
transactions =
[
  ["t1", "u1", "1000", "", "1", "false"],
  ["t2", "u1", "500", "", "2", "false"],
  ["t3", "u1", "2000", "", "3", "true"],
  ["t4", "u1", "", "300", "4", "false"]
]
Output: [["1", "2000", "300"]]

Example 3:

Input:
transactions =
[
  ["t1", "u1", "1000", "500", "1", "false"],
  ["t3", "u2", "500", "", "1", "false"],
  ["t2", "u1", "2000", "300", "2", "false"],
  ["t5", "u2", "", "1000", "2", "false"],
  ["t4", "u1", "100", "", "3", "true"],
  ["t7", "u2", "3000", "500", "3", "true"],
  ["t6", "u1", "", "200", "4", "false"],
  ["t8", "u1", "50", "100", "5", "false"]
]
Output: [["1", "150", "1100"], ["2", "3000", "500"]]
*/

/*
Follow-up 2:
Now we add support for undoLast and redoLast operations in the billing system. These operations allow reverting or
reapplying a user's most recent regular transaction. A regular transaction is any transaction that does not set undoLast
or redoLast to be "true".

Each transaction is given in the following format: [<transactionId>, <userId>, <adDeliveryPennies>, <paymentPennies>,
<transactionTimestamp>, <overwrite>, <undoLast>, <redoLast>], where:

(New) undoLast: A string value "true" or "false". If "true", undo the last regular transaction (if any) for this user.
Undoing a transaction reverses its effect on the user's current status. (New) redoLast: A string value "true" or
"false". If "true", redo the most recently undone transaction for this user. If no transaction has been undone, this has
no effect. A transaction may also have an "overwrite" flag as described in previou question. If "overwrite" is present,
treat the transaction as a regular transaction. "undoLast" and "redo_Last" operations are mutually exclusive and
override any monetary values in the transaction.

After processing all transactions, return each user's final billing status in the following format:[<userId>,
<totalAdDeliveryPennies>, <totalPaymentPennies>]. The output list should be ordered by userId in ascending lexicographic
order.

Example 1:

Input:
transactions =
[
  ["t1", "u1", "1000", "", "1", "false", "false", "false"],
  ["t2", "u1", "", "", "2", "false", "true", "false"],
  ["t3", "u1", "", "500", "3", "false", "false", "false"],
  ["t4", "u1", "1000", "500", "4", "false", "false", "false"]
]
Output: [["u1", "1000", "1000"]]

Explanation:

Transaction "t1" applies ad delivery += 1000.
Transaction "t2" undoes the most recent regular transaction ("t1"), resetting totals to zero.
Transaction "t3" applies payment += 500.
Transaction t4 applies ad delivery += 1000 and payment += 500.
Final totals are ad delivery = 1000 and payment = 1000.
Example 2:

Input:
transactions =
[
  ["t1", "u1", "1000", "", "1", "false", "false", "false"],
  ["t2", "u1", "500", "", "2", "false", "false", "false"],
  ["t3", "u1", "", "", "3", "false", "true", "false"],
  ["t4", "u1", "", "200", "4", "false", "false", "false"]
]
Output: [["u1", "1000", "200"]]

Example 3:

Input:
transactions =
[
  ["t1", "u1", "1000", "500", "1", "false", "false", "false"],
  ["t2", "u1", "2000", "300", "2", "false", "false", "false"],
  ["t3", "u1", "", "", "3", "false", "true", "false"],
  ["t4", "u1", "", "", "4", "false", "false", "true"],
  ["t5", "u1", "", "", "5", "false", "true", "false"],
  ["t6", "u1", "", "", "6", "false", "false", "true"]
]
Output: [["u1", "3000", "800"]]


 */