/*
https://www.hack2hire.com/companies/stripe/coding-questions/69810d31f8f2604d5eecfff3/practice?questionId=69810d3cf8f2604d5eecfff4
Account Balance Processor

Digital payment providers receive a stream of transaction logs that must be consolidated into account statements. Each
log is passed as a string with four comma-separated fields:

transaction_id: Unique identifier for the transaction (e.g., "txn_001").
account_id: Non-empty string representing the wallet, customer, or business account (e.g., "user_A", "company_X").
amount: Integer, positive for deposit (credit) and negative for withdrawal (debit).
timestamp: Integer, which may not be in chronological order.
Given a list of such strings, transactions, your goal is to calculate the final balance for every account after applying
all transactions in chronological order (by timestamp).

Return a JSON object, where:

The top-level key must be "balances".
The value is an object where each key is an account_id with a non-zero balance, and the value is the final integer
balance. Constraints:

1 ≤ transactions.length ≤ 105
Each transaction is a valid, four-field comma-separated string as described above.
All amount values are integers within the 32-bit signed range.
No two transactions for the same account share the same timestamp.
Each transaction_id is unique.
The account_id and transaction_id are non-empty strings.
Example 1:

Input: transactions = ["txn_01,user_A,1000,1",
                       "txn_02,user_A,500,2",
                       "txn_03,company_X,400,3",
                       "txn_04,company_X,-400,4"]
Output: { "balances": { "user_A": 1500 } }
Explanation: "user_A" receives two deposits: 1000 and 500, ending with 1500. "company_X" has a deposit of 400 and a
withdrawal of 400, resulting in zero, and is excluded from the output.

Example 2:

Input: transactions = ["txn_05,alice,200,1", "txn_06,bob,300,2", "txn_07,alice,100,3"]
Output: { "balances": { "alice": 300, "bob": 300 } }

Example 3:

Input: transactions = ["txn_08,acc1,5000,10",
                       "txn_09,acc2,-1500,5",
                       "txn_10,acc1,-2000,15",
                       "txn_11,acc3,7500,20",
                       "txn_12,acc2,2000,8",
                       "txn_13,acc1,-1500,12",
                       "txn_14,acc3,-3000,25",
                       "txn_15,acc4,10000,30",
                       "txn_16,acc2,-500,18",
                       "txn_17,acc4,-10000,35",
                       "txn_18,acc1,500,22"]
Output: { "balances": { "acc1": 2000, "acc3": 4500 } }
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
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

struct Transaction {
    string id;
    string account_id;
    int amount;
    int timestamp;

    Transaction();

    Transaction(string id, string account_id, string amount, string timestamp) {
        this->id = id;
        this->account_id = account_id;
        this->amount = stoi(amount);
        this->timestamp = stoi(timestamp);
    }
};

class Solution {
private:
    void parse(string& log, vector<string>& rst) {
        int pos = log.find(',');
        while (pos != string::npos) {
            rst.push_back(log.substr(0, pos));
            log = log.substr(pos + 1);
            pos = log.find(',');
        }
        rst.push_back(log);
    }

public:
    std::map<std::string, std::unordered_map<std::string, int>> processTransactions(
            const std::vector<std::string>& transactions) {
        vector<Transaction> all_trxn;
        for (string transaction : transactions) {
            vector<string> rst;
            parse(transaction, rst);
            all_trxn.push_back(Transaction(rst[0], rst[1], rst[2], rst[3]));
        }

        sort(all_trxn.begin(), all_trxn.end(),
             [](Transaction& a, Transaction& b) { return a.timestamp < b.timestamp; });

        unordered_map<string, int> account_balance;
        for (Transaction& txn : all_trxn) {
            account_balance[txn.account_id] += txn.amount;
        }

        unordered_map<string, int> non_zero_account_balance;
        for (const auto& entry : account_balance) {
            if (entry.second != 0) {
                non_zero_account_balance[entry.first] = entry.second;
            }
        }

        map<string, unordered_map<string, int>> rst;
        rst["balances"] = non_zero_account_balance;
        return rst;
    }
};

void printResult(const std::map<std::string, std::unordered_map<std::string, int>>& result) {
    std::cout << "{\"balances\": {";
    bool first = true;
    auto it = result.find("balances");
    if (it != result.end()) {
        for (const auto& entry : it->second) {
            if (!first)
                std::cout << ", ";
            std::cout << "\"" << entry.first << "\": " << entry.second;
            first = false;
        }
    }
    std::cout << "}}" << std::endl;
}

int main() {
    std::cout << "========== Test case 1: ==========" << std::endl;
    auto res1 = Solution().processTransactions(
            {"txn_01,user_A,1000,1", "txn_02,user_A,500,2", "txn_03,company_X,400,3", "txn_04,company_X,-400,4"});
    printResult(res1);
    // Expected:
    // {
    //   "balances": {
    //     "user_A": 1500
    //   }
    // }

    std::cout << "========== Test case 2: ==========" << std::endl;
    auto res2 = Solution().processTransactions({"txn_05,alice,200,1", "txn_06,bob,300,2", "txn_07,alice,100,3"});
    printResult(res2);
    // Expected:
    // {
    //   "balances": {
    //     "alice": 300,
    //     "bob": 300
    //   }
    // }

    std::cout << "========== Test case 3: ==========" << std::endl;
    auto res3 = Solution().processTransactions({"txn_08,acc1,5000,10", "txn_09,acc2,-1500,5", "txn_10,acc1,-2000,15",
                                                "txn_11,acc3,7500,20", "txn_12,acc2,2000,8", "txn_13,acc1,-1500,12",
                                                "txn_14,acc3,-3000,25", "txn_15,acc4,10000,30", "txn_16,acc2,-500,18",
                                                "txn_17,acc4,-10000,35", "txn_18,acc1,500,22"});
    printResult(res3);
    // Expected:
    // {
    //   "balances": {
    //     "acc1": 2000,
    //     "acc3": 4500
    //   }
    // }

    std::cout << "========== Test case 4: ==========" << std::endl;
    auto res4 = Solution().processTransactions(
            {"txn_19,zero1,1000,1", "txn_20,zero1,-1000,2", "txn_21,zero2,500,3", "txn_22,zero2,-500,4"});
    printResult(res4);
    // Expected: {"balances": {}}

    return 0;
}

/*
Follow-up 1:
In this follow-up question, given the same format and requirements as before, process each transaction in ascending
order of timestamp. If a transaction would cause an account's balance to go below zero, reject that transaction (do not
apply its amount) and record its transaction ID.

Return a JSON object containing:

"balances": Each account_id with a non-zero ending balance and its balance.
"rejected_transactions": A list of all rejected transaction IDs, in the order encountered.
All constraints and input formats remain unchanged from the previous question.

Example 1:

Input: transactions = ["txn_01,user_A,1000,1",
                       "txn_02,user_A,500,2",
                       "txn_03,company_X,400,3",
                       "txn_04,company_X,-500,4"]
Output: { "balances": { "user_A": 1500, "company_X": 400 }, "rejected_transactions": [ "txn_04" ] }
Explanation: "txn_04" is rejected because "company_X" has only 400 and cannot withdraw 500.

Example 2:

Input: transactions = ["txn_05,alice,100,5", "txn_06,alice,-50,2", "txn_07,alice,200,1"]
Output: { "balances": { "alice": 250 }, "rejected_transactions": [] }

Example 3:

Input: transactions = ["txn_08,acc1,1000,10",
                       "txn_09,acc2,500,5",
                       "txn_10,acc1,-1500,15",
                       "txn_11,acc3,2000,20",
                       "txn_12,acc2,-200,8",
                       "txn_13,acc1,800,12",
                       "txn_14,acc3,-500,25",
                       "txn_15,acc2,-400,18",
                       "txn_16,acc1,-500,30",
                       "txn_17,acc3,-2000,22"]
Output: { "balances": { "acc2": 300, "acc1": 300 }, "rejected_transactions": [ "txn_15", "txn_14", "txn_16" ] }
 */

class Solution {
private:
    void parse(string& log, vector<string>& rst) {
        int pos = log.find(',');
        while (pos != string::npos) {
            rst.push_back(log.substr(0, pos));
            log = log.substr(pos + 1);
            pos = log.find(',');
        }
        rst.push_back(log);
    }

public:
    std::map<std::string, std::any> processTransactions(std::vector<std::string> transactions) {
        vector<Transaction> all_trxn;
        for (string transaction : transactions) {
            vector<string> rst;
            parse(transaction, rst);
            all_trxn.push_back(Transaction(rst[0], rst[1], rst[2], rst[3]));
        }

        sort(all_trxn.begin(), all_trxn.end(),
             [](Transaction& a, Transaction& b) { return a.timestamp < b.timestamp; });

        unordered_map<string, int> account_balance;
        vector<string> rejected_trxns;
        for (Transaction& txn : all_trxn) {
            if (account_balance[txn.account_id] + txn.amount < 0) {
                rejected_trxns.push_back(txn.id);
            } else {
                account_balance[txn.account_id] += txn.amount;
            }
        }

        map<string, int> non_zero_account_balance;
        for (const auto& entry : account_balance) {
            if (entry.second != 0) {
                non_zero_account_balance[entry.first] = entry.second;
            }
        }

        std::map<std::string, std::any> rst;
        rst["balances"] = non_zero_account_balance;
        rst["rejected_transactions"] = rejected_trxns;
        return rst;
    }
};

void printResult(const std::map<std::string, std::any>& result) {
    auto balances = std::any_cast<std::map<std::string, int>>(result.at("balances"));
    auto rejected = std::any_cast<std::vector<std::string>>(result.at("rejected_transactions"));

    std::cout << "{balances: {";
    bool first = true;
    for (const auto& entry : balances) {
        if (!first)
            std::cout << ", ";
        std::cout << entry.first << ": " << entry.second;
        first = false;
    }
    std::cout << "}, rejected_transactions: [";
    first = true;
    for (const auto& txn : rejected) {
        if (!first)
            std::cout << ", ";
        std::cout << txn;
        first = false;
    }
    std::cout << "]}" << std::endl;
}

int main() {
    std::cout << "========== Test case 1: ==========" << std::endl;
    auto res1 = Solution().processTransactions(
            {"txn_01,user_A,1000,1", "txn_02,user_A,500,2", "txn_03,company_X,400,3", "txn_04,company_X,-500,4"});
    printResult(res1);
    // Expected:
    // {
    //   "balances": {
    //     "user_A": 1500,
    //     "company_X": 400
    //   },
    //   "rejected_transactions": ["txn_04"]
    // }

    std::cout << "========== Test case 2: ==========" << std::endl;
    auto res2 = Solution().processTransactions({"txn_05,alice,100,5", "txn_06,alice,-50,2", "txn_07,alice,200,1"});
    printResult(res2);
    // Expected:
    // {
    //   "balances": {
    //     "alice": 250
    //   },
    //   "rejected_transactions": []
    // }

    std::cout << "========== Test case 3: ==========" << std::endl;
    auto res3 = Solution().processTransactions({"txn_08,acc1,1000,10", "txn_09,acc2,500,5", "txn_10,acc1,-1500,15",
                                                "txn_11,acc3,2000,20", "txn_12,acc2,-200,8", "txn_13,acc1,800,12",
                                                "txn_14,acc3,-500,25", "txn_15,acc2,-400,18", "txn_16,acc1,-500,30",
                                                "txn_17,acc3,-2000,22"});
    printResult(res3);
    // Expected:
    // {
    //   "balances": {
    //     "acc2": 300,
    //     "acc1": 300
    //   },
    //   "rejected_transactions": ["txn_15", "txn_14", "txn_16"]
    // }

    return 0;
}

/*
Follow-up 2:
This is a follow-up to the previous transaction rejection problem, now introducing a designated platform account. You
are given an additional input, platformId, identifying which account serves as the platform.

For any non-platform account, if a withdrawal would bring its balance below zero, you may borrow the required amount
from the platform account if the platform has sufficient funds at that moment. If the platform cannot cover the deficit,
reject the transaction.

If a non-platform account borrows from the platform, the amount borrowed becomes its debt.
Any new incoming funds for a non-platform account that owes debt must be used to repay the platform first. Only after
the debt is fully repaid does the account balance increase. Besides, you need to track the maximum reserve amount
(max_reserve): the highest total outstanding borrowed amount owed to the platform by non-platform accounts at any point.

Return a JSON object with:

"max_reserve": Largest outstanding borrowed amount ever reached during processing.
"rejected_transactions": List of transaction IDs (as strings) that could not be processed due to insufficient combined
funds. "balances": Final non-zero balances for all accounts. All input formatting and parsing requirements are
unchanged.

Example 1:

Input: transactions = ["txn_01,user_A,1000,1",
                       "txn_02,company_X,400,3",
                       "txn_03,company_X,-500,4",
                       "txn_04,company_X,50,5",
                       "txn_05,company_X,70,6",
                       "txn_06,company_X,-1000,7",
                       "txn_07,user_A,50,8"],
       platformId = "user_A"
Output: { "max_reserve": 100, "rejected_transactions": [ "txn_06" ], "balances": { "user_A": 950, "company_X": 20 } }
Explanation:

On "txn_03", "company_X" withdraws 500, borrowing 100 from "user_A" (platform), so "max_reserve" becomes 100.
On "txn_04" and "txn_05", "company_X" receives a total of 120, which first pays back the 100 debt to "user_A", then
leaves "company_X" with 20. "txn_06" is rejected because "company_X" cannot withdraw 1000; combined balances are
insufficient. Example 2:

Input: transactions = ["txn_08,platform,2000,1",
                       "txn_09,alice,500,2",
                       "txn_10,alice,-700,3",
                       "txn_11,alice,300,4"],
       platformId = "platform"
Output: { "max_reserve": 200, "rejected_transactions": [], "balances": { "platform": 1800, "alice": 100 } }

Example 3:

Input: transactions = ["txn_12,bank,5000,1",
                       "txn_13,acc1,1000,5",
                       "txn_14,acc2,800,10",
                       "txn_15,acc1,-1200,15",
                       "txn_16,acc2,-1000,20",
                       "txn_17,acc1,300,25",
                       "txn_18,acc2,400,30",
                       "txn_19,acc1,-500,35"],
       platformId = "bank"
Output: { "max_reserve": 400, "rejected_transactions": [], "balances": { "bank": 4200, "acc2": 200 } }
 */

#include <sstream>
#include <any>

class Solution {
public:
    std::map<std::string, std::any> processTransactions(std::vector<std::string> transactions, std::string platformId) {
        std::map<std::string, int> account_balance_;
        std::map<std::string, int> account_debt_;
        std::vector<std::string> rejected_trxns;
        int max_reserve = 0;
        int current_reserve = 0;

        std::vector<Transaction> parsedTxns;
        for (const std::string& transaction : transactions) {
            std::stringstream ss(transaction);
            std::string txnId, accountId, amountStr, timestampStr;

            std::getline(ss, txnId, ',');
            std::getline(ss, accountId, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, timestampStr, ',');

            int amount = std::stoi(amountStr);
            int timestamp = std::stoi(timestampStr);
            parsedTxns.emplace_back(txnId, accountId, amount, timestamp);
        }

        std::sort(parsedTxns.begin(), parsedTxns.end(),
                  [](const Transaction& a, const Transaction& b) { return a.timestamp < b.timestamp; });

        account_balance_[platformId] = 0;
        account_debt_[platformId] = 0;

        // Process transactions
        for (const Transaction& txn : parsedTxns) {
            const std::string& accountId = txn.accountId;
            int amount = txn.amount;

            account_balance_.try_emplace(accountId, 0);
            account_debt_.try_emplace(accountId, 0);

            if (amount > 0) {
                // Repay debt first if exists
                if (accountId != platformId && account_debt_[accountId] > 0) {
                    int repay = std::min(amount, account_debt_[accountId]);
                    account_debt_[accountId] -= repay;
                    current_reserve -= repay;
                    account_balance_[accountId] += (amount - repay);
                } else {
                    account_balance_[accountId] += amount;
                }
            } else {
                int newBalance = account_balance_[accountId] + amount;
                if (newBalance >= 0) {
                    account_balance_[accountId] = newBalance;
                } else if (accountId != platformId && account_balance_[platformId] >= -newBalance) {
                    // Borrow from platform
                    int deficit = -newBalance;
                    account_balance_[accountId] = 0;
                    account_balance_[platformId] -= deficit;
                    account_debt_[accountId] += deficit;
                    current_reserve += deficit;
                    max_reserve = std::max(max_reserve, current_reserve);
                } else {
                    rejected_trxns.push_back(txn.txnId);
                }
            }
        }

        std::map<std::string, int> nonZeroBalances;
        for (const auto& [k, v] : account_balance_) {
            if (v != 0)
                nonZeroBalances[k] = v;
        }

        std::map<std::string, std::any> result;
        result["max_reserve"] = max_reserve;
        result["rejected_transactions"] = rejected_trxns;
        result["balances"] = nonZeroBalances;
        return result;
    }
};

void printResult(const std::map<std::string, std::any>& res) {
    auto balances = std::any_cast<std::map<std::string, int>>(res.at("balances"));
    auto rejected = std::any_cast<std::vector<std::string>>(res.at("rejected_transactions"));
    int maxReserve = std::any_cast<int>(res.at("max_reserve"));

    std::cout << "{\n";
    std::cout << "  max_reserve: " << maxReserve << ",\n";
    std::cout << "  balances: {";
    bool first = true;
    for (const auto& [k, v] : balances) {
        if (!first)
            std::cout << ", ";
        std::cout << k << ": " << v;
        first = false;
    }
    std::cout << "},\n  rejected_transactions: [";
    first = true;
    for (const auto& r : rejected) {
        if (!first)
            std::cout << ", ";
        std::cout << r;
        first = false;
    }
    std::cout << "]\n}\n";
}

int main() {
    std::cout << "========== Test case 1 ==========\n";
    printResult(Solution().processTransactions(
            {"txn_01,user_A,1000,1", "txn_02,company_X,400,3", "txn_03,company_X,-500,4", "txn_04,company_X,50,5",
             "txn_05,company_X,70,6", "txn_06,company_X,-1000,7", "txn_07,user_A,50,8"},
            "user_A"));

    std::cout << "========== Test case 2 ==========\n";
    printResult(Solution().processTransactions(
            {"txn_08,platform,2000,1", "txn_09,alice,500,2", "txn_10,alice,-700,3", "txn_11,alice,300,4"}, "platform"));

    std::cout << "========== Test case 3 ==========\n";
    printResult(Solution().processTransactions(
            {"txn_12,bank,5000,1", "txn_13,acc1,1000,5", "txn_14,acc2,800,10", "txn_15,acc1,-1200,15",
             "txn_16,acc2,-1000,20", "txn_17,acc1,300,25", "txn_18,acc2,400,30", "txn_19,acc1,-500,35"},
            "bank"));

    std::cout << "========== Test case 4 ==========\n";
    printResult(Solution().processTransactions({"txn_20,reserve,500,1", "txn_21,client,100,2", "txn_22,client,-700,3"},
                                               "reserve"));

    std::cout << "========== Test case 5 ==========\n";
    printResult(Solution().processTransactions(
            {"txn_23,main,1000,1", "txn_24,user,200,2", "txn_25,main,-500,3", "txn_26,user,-100,4"}, "main"));

    return 0;
}
