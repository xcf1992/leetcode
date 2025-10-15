/*
1169. Invalid Transactions
A transaction is possibly invalid if:

the amount exceeds $1000, or;
if it occurs within (and including) 60 minutes of another transaction with the same name in a different city.

Each transaction string transactions[i] consists of comma separated values representing the name,
time (in minutes), amount, and city of the transaction.

Given a list of transactions, return a list of transactions that are possibly invalid.
You may return the answer in any order.

Example 1:

Input: transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
Output: ["alice,20,800,mtv","alice,50,100,beijing"]
Explanation: The first transaction is invalid because the second transaction occurs within a difference of 60 minutes, have the same name and is in a different city. Similarly the second one is invalid too.
Example 2:

Input: transactions = ["alice,20,800,mtv","alice,50,1200,mtv"]
Output: ["alice,50,1200,mtv"]
Example 3:

Input: transactions = ["alice,20,800,mtv","bob,50,1200,mtv"]
Output: ["bob,50,1200,mtv"]


Constraints:

transactions.length <= 1000
Each transactions[i] takes the form "{name},{time},{amount},{city}"
Each {name} and {city} consist of lowercase English letters, and have lengths between 1 and 10.
Each {time} consist of digits, and represent an integer between 0 and 1000.
Each {amount} consist of digits, and represent an integer between 0 and 2000.
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
using namespace std;

class Solution {
private:
    vector<string> split(string& transaction) {
        vector<string> result;
        string cur = "";
        for (char c: transaction) {
            if (c == ',') {
                result.push_back(cur);
                cur = "";
            }
            else {
                cur.push_back(c);
            }
        }
        result.push_back(cur);
        result.push_back(transaction);
        return result;
    }

    bool isValid(vector<string>& tran, vector<vector<string>>& trans) {
        if (stoi(tran[2]) > 1000) {
            return false;
        }

        for (int i = 0; i < trans.size(); ++i) if (tran[3] != trans[i][3]) {
            if (abs(stoi(tran[1]) - stoi(trans[i][1])) <= 60) {
                return false;
            }
        }
        return true;
    }
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        unordered_map<string, vector<vector<string>>> peopleTrans;
        for (string& transaction: transactions) {
            vector<string> trans = split(transaction);
            peopleTrans[trans[0]].push_back(trans);
        }

        vector<string> result;
        for (auto& it: peopleTrans) {
            vector<vector<string>> trans = it.second;
            for (vector<string>& tran: trans) {
                if (!isValid(tran, trans)) {
                    result.push_back(tran[4]);
                }
            }
        }
        return result;
    }
};
