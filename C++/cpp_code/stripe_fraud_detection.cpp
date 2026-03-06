/*
Question 1
The fraud detection team at Stripe aims to reduce merchant fraud risk for Stripe with minimal pain to good merchants
through machine learning. To provide initial data for training this machine learning model, you are tasked with
developing a system to assess the fraud risk associated with transactions made to various merchants. Description You are
given transactions_list which is a list of transactions for a certain day, merchants_list which is a list of merchants,
and rules_list which is a list of rules corresponding to each transaction (more information below). A transaction
denotes a payment made by a customer to a merchant. Each merchant in merchants_list is assigned a base_score. Your task
is to assign each merchant a fraud score based on their transaction(s), where each transaction can have different risk
factors based on certain categories (e.g., transaction amount, frequency of similar transactions, user activity). To do
this:

Initialize a merchant's current_score as their base_score
For each transaction in the transactions_list, calculate and update the merchant's current_score. This should be done in
separate passes over the entire list for each step:

If the transaction amount is greater than the corresponding rule's min_transaction_amount, multiply current_score by the
corresponding rule's multiplicative_factor If the same customer_id has made three or more transactions to that
merchant_id (including the current transaction), add all the corresponding rules' additive_factors to current_score,
cumulatively (e.g., if the merchant's score at the third transaction is X which include the first, second, and third
additive_factors the fourth transaction should be X + the fourth transaction's additive_factor). If a transaction is the
third or more from the same customer_id in the same hour for the same merchant_id (including current transaction), do
the following:

If the hour is between 12 to 17 (inclusive): Add the penalty each time (this includes the first and second transaction
as well as all the ones after the third). If the hour is between 9 to 11, or 18 to 21 (inclusive): Subtract the penalty
each time (this includes the first and second transaction as well as all the ones after the third). If the hour falls
outside the above ranges, don't do anything.





Input
Note: You may assume that there won't be any integer overflows.

transactions_list: A list of length n (1 ≤ n ≤ 1000) where each transaction is represented as a comma-separated string.

A string merchant_id (length > 0) of the merchant who receives payment
An integer amount of the payment
A string customer_id (length > 0) of the customer who makes payment
An integer hour (0 ≤ hour ≤ 23) representing the hour of the transaction


rules_list: A list of length n (1 ≤ n ≤ 1000) where each rule is represented as a comma-separated string (and
corresponds to each transaction in transactions_list)

An integer min_transaction_amount of the corresponding transaction to consider fraudulent
An integer multiplicative_factor
An integer additive_factor
An integer penalty


merchants_list: A list of length m (1 ≤ m ≤ 1000) where each item is a merchant profile (comma-separated string) that
gives additional context for the score.

A string merchant_id (length > 0) of the merchant who receives payment
An integer base_score (1 ≤ base_score ≤ 50). Represents the base risk score of the merchant.



Output
Return a list of comma-separated strings denoting the merchants (in lexicographical order) and their fraud scores.
Example
# Example input
n = 6
transactions_list = [
    "merchant1,1200,customer1,10",
    "merchant1,500,customer1,10",
    "merchant2,2400,customer1,15",
    "merchant1,800,customer1,16",
    "merchant1,1000,customer2,17",
    "merchant1,1400,customer1,10",
]
rules_list = [
    "1000,2,8,15",
    "1400,5,3,19",
    "2300,3,17,3",
    "1800,2,9,6",
    "1000,4,8,2",
    "1200,3,11,7",
]
m = 2
merchants_list = [
    "merchant1,10",
    "merchant2,20",
]

# Example output
[
    "merchant1,50",  # 10 -> 10*2=20 -> 20*3=60 -> 60+8+3+9+11=91 -> 91-15-19-7=50
    "merchant2,60"   # 20 -> 20*3=60
]
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

/*
Problem Description
The fraud detection team at Stripe aims to reduce merchant fraud risk. You are given transactions_list (a list of
transactions for a certain day), merchants_list (a list of merchants), and rules_list (a list of rules corresponding to
each transaction). A transaction denotes a payment made by a customer to a merchant. Each merchant in merchants_list is
assigned a base_score. Your task is to assign each merchant a fraud score based on their transaction(s), where each
transaction can have different risk factors based on certain categories. To do this:

Initialize a merchant's current_score as their base_score.
For each transaction in the transactions_list, calculate and update the merchant's current_score. This should be done in
separate passes over the entire list for each step:

Pass 1: If the transaction amount is greater than the corresponding rule's min_transaction_amount, multiply
current_score by the corresponding rule's multiplicative_factor. Pass 2: If the same customer_id has made three or more
transactions to that merchant_id (including the current transaction), add all the corresponding rules' additive_factors
to current_score, cumulatively. (e.g., if the merchant's score at the third transaction is X which include the first,
second, and third additive_factors, the fourth transaction should be X + the fourth transaction's additive_factor). Pass
3: If a transaction is the third or more from the same customer_id in the same hour for the same merchant_id (including
current transaction), do the following:

If the hour is between 12 to 17 (inclusive): Add the penalty each time (this includes the first and second transaction
as well as all the ones after the third). If the hour is between 9 to 11, or 18 to 21 (inclusive): Subtract the penalty
each time (this includes the first and second transaction as well as all the ones after the third). If the hour falls
outside the above ranges, don't do anything.





Input

transactions_list: A list of length n (1 ≤ n ≤ 1000) where each transaction is a comma-separated string: merchant_id,
amount (integer), customer_id, hour (integer, 0 ≤ hour ≤ 23). rules_list: A list of length n (1 ≤ n ≤ 1000) where each
rule is a comma-separated string (corresponds to each transaction): min_transaction_amount (integer),
multiplicative_factor (integer), additive_factor (integer), penalty (integer). merchants_list: A list of length m (1 ≤ m
≤ 1000) where each item is a comma-separated string: merchant_id, base_score (integer, 1 ≤ base_score ≤ 50).

Output
Return a list of comma-separated strings denoting the merchants (in lexicographical order) and their fraud scores.
Example
n = 6
transactions_list = [
    "merchant1,1200,customer1,10",
    "merchant1,500,customer1,10",
    "merchant2,2400,customer1,15",
    "merchant1,800,customer1,16",
    "merchant1,1000,customer2,17",
    "merchant1,1400,customer1,10",
]
rules_list = [
    "1000,2,8,15",
    "1400,5,3,19",
    "2300,3,17,3",
    "1800,2,9,6",
    "1000,4,8,2",
    "1200,3,11,7",
]
m = 2
merchants_list = [
    "merchant1,10",
    "merchant2,20",
]

# Output:
["merchant1,50", "merchant2,60"]
# merchant1: 10 -> 10*2=20 -> 20*3=60 -> 60+8+3+9+11=91 -> 91-15-19-7=50
# merchant2: 20 -> 20*3=60
Now let me solve it:Created a file, ran a commandCreated a file, ran a commandThe output matches the expected result.
Let me trace through the example to verify my understanding: merchant1 (base=10):

Pass 1 (multiplicative): Transaction 0: 1200 > 1000 → 10×2=20. Transaction 1: 500 ≤ 1400, skip. Transaction 3: 800 ≤
1800, skip. Transaction 4: 1000 ≤ 1000, skip. Transaction 5: 1400 > 1200 → 20×3=60. Pass 2 (additive):
customer1→merchant1 hits count 3 at transaction 3 (idx 0,1,3). Add 8+3+9=20 → 80. At transaction 5 (4th), add 11 → 91.
customer2 only has 1 transaction, skip. Pass 3 (same hour penalty): customer1→merchant1→hour10 has 3 transactions (idx
0,1,5). At the 3rd (idx 5), apply for all 3: hour=10 is in [9,11] → subtract. 91 - 15 - 19 - 7 = 50.

merchant2 (base=20):

Pass 1: Transaction 2: 2400 > 2300 → 20×3=60. No other passes apply.

Let me copy the file to outputs:Ran a command, read a fileRan a command, read a fileThe solution passes the example test
case (merchant1,50 and merchant2,60). Key design points:

Three separate passes over the transaction list, as required by the problem.
Pass 1 (Multiplicative): If amount > min_transaction_amount, multiply the merchant's score by multiplicative_factor.
Pass 2 (Additive): Track (merchant_id, customer_id) counts. When the count reaches 3, retroactively add all prior
additive_factors for that pair. For count > 3, just add the current one. Pass 3 (Same-hour penalty): Track (merchant_id,
customer_id, hour) counts. When count reaches 3, retroactively apply penalties for all prior transactions in that group.
Hours 12–17 add penalty, hours 9–11 and 18–21 subtract penalty, others do nothing. Output is sorted lexicographically
using std::map's natural ordering.
 */
struct Transaction {
    string merchant_id;
    int amount;
    string customer_id;
    int hour;
};

struct Rule {
    int min_transaction_amount;
    int multiplicative_factor;
    int additive_factor;
    int penalty;
};

vector<string> solve(vector<string>& transactions_list, vector<string>& rules_list, vector<string>& merchants_list) {
    int n = transactions_list.size();

    // Parse transactions
    vector<Transaction> txns(n);
    for (int i = 0; i < n; i++) {
        stringstream ss(transactions_list[i]);
        string token;
        getline(ss, token, ','); txns[i].merchant_id = token;
        getline(ss, token, ','); txns[i].amount = stoi(token);
        getline(ss, token, ','); txns[i].customer_id = token;
        getline(ss, token, ','); txns[i].hour = stoi(token);
    }

    // Parse rules
    vector<Rule> rules(n);
    for (int i = 0; i < n; i++) {
        stringstream ss(rules_list[i]);
        string token;
        getline(ss, token, ','); rules[i].min_transaction_amount = stoi(token);
        getline(ss, token, ','); rules[i].multiplicative_factor = stoi(token);
        getline(ss, token, ','); rules[i].additive_factor = stoi(token);
        getline(ss, token, ','); rules[i].penalty = stoi(token);
    }

    // Parse merchants
    map<string, long long> scores; // merchant_id -> current_score
    for (auto& m : merchants_list) {
        stringstream ss(m);
        string mid, bs;
        getline(ss, mid, ',');
        getline(ss, bs, ',');
        scores[mid] = stoi(bs);
    }

    // ===== PASS 1: Multiplicative factor =====
    // If transaction amount > rule's min_transaction_amount, multiply current_score by multiplicative_factor
    for (int i = 0; i < n; i++) {
        string& mid = txns[i].merchant_id;
        if (scores.find(mid) == scores.end()) continue;
        if (txns[i].amount > rules[i].min_transaction_amount) {
            scores[mid] *= rules[i].multiplicative_factor;
        }
    }

    // ===== PASS 2: Additive factor =====
    // If same customer_id has made 3 or more transactions to that merchant_id (including current),
    // add all corresponding rules' additive_factors cumulatively.
    // We need to count per (merchant_id, customer_id) pair as we iterate.
    {
        map<pair<string,string>, int> count; // (merchant_id, customer_id) -> count so far
        for (int i = 0; i < n; i++) {
            string& mid = txns[i].merchant_id;
            string& cid = txns[i].customer_id;
            if (scores.find(mid) == scores.end()) continue;
            count[{mid, cid}]++;
            if (count[{mid, cid}] >= 3) {
                // Add all additive_factors for this (mid, cid) pair including past ones
                // But "cumulatively" means: at the 3rd transaction, add 1st+2nd+3rd additive_factors
                // at the 4th, add just the 4th.
                // Wait, re-reading: "add all the corresponding rules' additive_factors to current_score, cumulatively"
                // "if the merchant's score at the third transaction is X which include the first, second, and third additive_factors,
                //  the fourth transaction should be X + the fourth transaction's additive_factor"
                // So at count==3, we add all 3 additive_factors (for transactions with this cid to this mid)
                // At count==4, we add just the 4th additive_factor
                // At count>=3, if it's exactly 3, add all previous + current. If >3, add just current.
                if (count[{mid, cid}] == 3) {
                    // Find all previous transactions (including this one) for this pair and add their additive_factors
                    // We need to find the indices of all transactions so far for this pair
                    for (int j = 0; j <= i; j++) {
                        if (txns[j].merchant_id == mid && txns[j].customer_id == cid) {
                            scores[mid] += rules[j].additive_factor;
                        }
                    }
                } else {
                    // count > 3, just add current
                    scores[mid] += rules[i].additive_factor;
                }
            }
        }
    }

    // ===== PASS 3: Same hour penalty =====
    // If a transaction is the 3rd or more from the same customer_id in the same hour for the same merchant_id,
    // apply penalty to ALL transactions in that group (including 1st and 2nd).
    // But we process sequentially, so when count reaches 3, we apply penalty for all 3,
    // and for each subsequent one, apply penalty for just that one.
    {
        // key: (merchant_id, customer_id, hour) -> count
        map<tuple<string,string,int>, int> count;
        for (int i = 0; i < n; i++) {
            string& mid = txns[i].merchant_id;
            string& cid = txns[i].customer_id;
            int hour = txns[i].hour;
            if (scores.find(mid) == scores.end()) continue;

            auto key = make_tuple(mid, cid, hour);
            count[key]++;

            if (count[key] >= 3) {
                if (count[key] == 3) {
                    // Apply penalty for ALL transactions in this group (1st, 2nd, 3rd)
                    for (int j = 0; j <= i; j++) {
                        if (txns[j].merchant_id == mid && txns[j].customer_id == cid && txns[j].hour == hour) {
                            int pen = rules[j].penalty;
                            if (hour >= 12 && hour <= 17) {
                                scores[mid] += pen;
                            } else if ((hour >= 9 && hour <= 11) || (hour >= 18 && hour <= 21)) {
                                scores[mid] -= pen;
                            }
                        }
                    }
                } else {
                    // count > 3, apply penalty for just this transaction
                    int pen = rules[i].penalty;
                    if (hour >= 12 && hour <= 17) {
                        scores[mid] += pen;
                    } else if ((hour >= 9 && hour <= 11) || (hour >= 18 && hour <= 21)) {
                        scores[mid] -= pen;
                    }
                }
            }
        }
    }

    // Build result in lexicographical order
    vector<string> result;
    for (auto& [mid, score] : scores) {
        result.push_back(mid + "," + to_string(score));
    }
    // map is already sorted lexicographically
    return result;
}

int main() {
    // Test with the example
    vector<string> transactions_list = {
        "merchant1,1200,customer1,10",
        "merchant1,500,customer1,10",
        "merchant2,2400,customer1,15",
        "merchant1,800,customer1,16",
        "merchant1,1000,customer2,17",
        "merchant1,1400,customer1,10",
    };
    vector<string> rules_list = {
        "1000,2,8,15",
        "1400,5,3,19",
        "2300,3,17,3",
        "1800,2,9,6",
        "1000,4,8,2",
        "1200,3,11,7",
    };
    vector<string> merchants_list = {
        "merchant1,10",
        "merchant2,20",
    };

    auto result = solve(transactions_list, rules_list, merchants_list);
    for (auto& s : result) {
        cout << s << endl;
    }
    // Expected: merchant1,50  merchant2,60

    return 0;
}
