/*
https://github.com/JesseZhuang/InCodeLearning-Python3/blob/main/algorithm/ood/banking_system.py
https://www.linkjob.ai/interview-questions/coinbase-codesignal-assessment-insider-guide/
https://www.youtube.com/watch?v=dflijSS_AjI
https://github.com/AlejandroAldana99/Go-codes/blob/main/In-Memory-DB/bank/bank.go

code signal: banking system
Requirements
Your task is to implement a simplified version of a banking system. Plan your design according to the level
specifications below:
• Level 1: The banking system should support creating new accounts and depositing money into and withdrawing/paying
 money from accounts.
• Level 2: The banking system should support ranking accounts based on the total value of transactions.
• Level 3: The banking system should support scheduling transfers and checking the scheduled transfer status.
• Level 4: The banking system should support merging two accounts while retaining the balances and transaction
histories of the original accounts.
To move to the next level, you should pass all the tests at the current level.
Note
You will receive a list of queries to the system, and the final output should be an array of strings representing
the returned values of all queries. Each query will only call one operation.
All queries will have a timestamp parameter — a string field timestamp in milliseconds. It is
guaranteed that all timestamps are unique and are in a range from 1 to 10^9.
Queries will be given in the order of strictly increasing timestamps.

Level 1:
1, CREATE_ACCOUNT<timestamp><accountId>, returns true if not present and create account, false otherwise
2, DEPOSIT <timestamp><accountId><amount>, deposit given amount of money to the specific account. returns a string
representing total money in the account (balance). If account does not exist, return empty string.
3, PAY <timestamp> <accountId> <amount>, withdraw from the account. returns a string representing account balance
after processing the query. If account does not exist or insufficient fund, return empty string.

Level 2:
The banking system should support ranking accounts based on total number of transactions.
1, TOP_ACTIVITY <timestamp> <n> return the top n accounts with the highest total value of transactions in descending
order. A string representing an array of accounts and transaction values in this format
"<accountId1>(<transactionValue1>)".
* Total value of transactions is defined as the sum of all transactions for an account (regardless of how the
 transaction affects account balance), including the amount of money deposited, withdrawn,
 and/or successfully transferred (transfers will be introduced on level 3, so you can ignore them for now).
* If less than n accounts exist in the system, return all active accounts (in the described format).

Level 3
The banking system should allow scheduling payments and checking the status of scheduled payments.
1, TRANSFER <timestamp> <sourceAccountId> ‹targetAccountId> <amount> - should initiate a transfer between accounts.
The given amount of money should be withdrawn from the source account sourceAccountId and held until the transfer
 is accepted by the target account targetAccountId, or until the transfer expires. The withheld money is added
 back to the source account's balance if the transfer expires. After the query is processed:
• Returns an empty string if sourceAccountId is equal to targetAccountId.
• Returns an empty string if sourceAccountId or targetAccountId doesn't exist.
• Returns an empty string if the source account sourceAccountId has insufficient funds to perform the transfer.
• The expiration period is 24 hours, which is equal to 24 • 60 • 60 • 1000 = 86400000 milliseconds.
A transfer expires at the beginning of the next millisecond after the expiration period ends.
• A valid TransFer should return a string containing a unique transfer ID in the following format
"transfer[ordinal number of the transfer]", e.g., "transfer1","transfer2", etc.
• For transfers, transaction history for source and target accounts is only updated when the transfer is accepted.
• Transfers count toward the total value of transactions of both source and target accounts.

2, ACCEPT_TRANSFER ‹timestamp> <accountId> <transferId> - Should accept the transfer with the given transferId.
• Returns "true" if the transfer was successfully accepted or "false" otherwise.
• Returns "false" if a transfer with transferId does not exist, was already accepted, or has expired.
• Returns "false" if the given accountId was not the target account for the transfer.

Level 3  (Variant Java)
The system should allow scheduling payments and checking the status of scheduled payments.
• Optional<String> schedulePayment(int timestamp, String accountId, int amount, int delay) - should schedule a payment
 which will be performed at timestamp + delay . Returns a string with a unique identifier for the scheduled payment
 in the following format: "payment [ordinal number of the scheduled payment across all accounts] - e.g., "payment i",
 "payment2", etc. If accountId doesn't exist, should return Optional.empty. The payment is skipped if the specified
  account has insufficient funds when the payment is performed. Additional conditions:
• Successful payments should be considered outgoing transactions and included when ranking accounts using the
 operation.
• Scheduled payments should be processed before any other transactions at the given timestamp.
• If an account needs to perform several scheduled payments simultaneously, they should be processed in order of
 creation - e.g., "payment1" should be processed before "payment2"
• boolean cancelPayment(int timestamp, String accountId, String paymentId) - should cancel the scheduled payment
with paymentId. Returns true if the scheduled payment is successfully canceled. If paymentId does not exist or
was already canceled, or if accountId is different from the source account for the scheduled payment, returns false.
 Note that scheduled payments must be performed before any cancelPayment operations at the given timestamp.

Level 3 (Variant-Python)
pay (self, timestamp: int, account_id: str, amount: int) -> str | None
- Should withdraw the given amount of money from the specified account. All withdraw transactions provide a 2% cashback
 - 2% of the withdrawn amount (rounded down to the nearest integer) will be refunded to the account 24 hours after
  the withdrawal. If the withdrawal is successful (i.e., the account holds sufficient funds to withdraw
   the given amount), returns a string with a unique identifier for the payment transaction in this format:
    "payment(ordinal number of withdraws from all accounts]" -e.g., "payment1", "payment2", etc.
Additional conditions:
• Returns None if account_id doesn't exist.
• Returns None if account_id has insufficient funds to perform the payment.
• top_spenders should now also account for the total amount of money withdrawn from accounts.
• The waiting period for cashback is 24 hours, equal to 24 * 60 * 60 * 1000 = 86400000 milliseconds
  (the unit for timestamps). So, cashback will be processed at timestamp, timestamp + 86400000 .
• When it's time to process cashback for a withdrawal, the amount must be refunded to the account before any other
  transactions are performed at the relevant timestamp.

get_payment_status (self, timestamp: int, account_id: str, payment: str) -> str | None -
Should return the status of the payment transaction for the given payment.
Specifically:
• Returns None if account_id doesn't exist.
• Returns None if the given payment doesn't exist for the specified account.
• Returns None if the payment transaction was for an account with a different identifier from account_id
• Returns a string representing the payment status: "IN_PROGRESS" or "CASHBACK_RECEIVED".

The system should allow scheduling payments and checking the status of scheduled payments.
• SCHEDULE_PAYMENT < timestamp> < accountId> ‹amount > ‹delay> - should schedule a payment which will be performed
at timestamp + delay. Returns a string with a unique identifier for the scheduled payment in the following format:
"payment [ordinal number of the scheduled payment across all accounts]" - e.g.,
"payment1", "payment2", etc. If account id doesn't exist, should return an empty string. The payment is skipped if the
specified account has insufficient funds when the payment is performed.
Additional conditions:
• Successful payments should be considered outgoing transactions and included when ranking accounts using the
TOP_SPENDERS operation.
• Scheduled payments should be processed before any other transactions at the given timestamp.
• If an account needs to perform several scheduled payments simultaneously, they should be processed in order
 of creation - e.g., "payment1" should be processed before "payment2"

CANCEL_PAYMENT < timestamp> <accountId> <paymentId> - should cancel the scheduled payment with paymentId.
Returns "true" if the scheduled payment is successfully canceled. If payment id does not exist or was already canceled,
 or if account id is different from the source account for the scheduled payment, returns
"false" . Note that scheduled payments must be performed before any CANCEL_PAYMENT operations at the given timestamp.

Level 4

The banking system should support merging two accounts while retaining both accounts' balance and transaction histories

merge_accounts (self, timestamp: int, account_id_1: str, account_id_2: str) -> bool
- Should merge account_id_2 into the account_id_1.
Returns True if accounts were successfully merged, or False otherwise.
Specifically:
• Returns False If account_id_1 is equal to account_id_2.
• Returns False if account_id_1 or account_id_2 doesn't exist.
• All pending cashback refunds for account_id_2 should still be processed, but refunded to account_id_1 instead.
• After the merge, it must be possible to check the status of payment transactions for account_id_2 with payment
identifiers by replacing account_id_2 with account_id_1
• The balance of account_sa_2 should be added to the balance for account_id_1
• top_spenders operations should recognize merged accounts - the total outgoing transactions for merged accounts
should be the sum of all money transferred and/or withdrawn in both accounts.
• account_id_2 should be removed from the system after the merge.

get_balance(self, timestamp: int, account_id: str, time_at: int) -> int | None
 - Should return the total amount of money in the account account_id at the given timestamp tine_at.
 If the specified account did not exist at a given time time_at, returns None
• If queries have been processed at timestamp time_at, get_balance must reflect the account balance after the query
has been processed.
• If the account was merged into another account, the merged account should inherit its balance history.

Note: Not clear what to return for a get_balance query of a deleted account in the merge. This version returns
the balance by tracing to the target account in the merge.

Variants:
- Level 3: schedule payment, cancel payment
- support payment, user get cashback after 24 hours of spending
- level 4: merge two accounts, need to merge accounts in the transfer system too. The banking system should support
 merging two accounts while retaining both accounts' balance and transaction histories.
- get balance, need to support timestamp, get the history balance of the specified account at a given timeAt
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
#include <numeric>
using namespace std;

class Account {
public:
    string id_;
    int balance_;
    int total_send_;
    int total_receive_;
    int created_at_;
    map<int, int> balance_at_;
    string merged_into_;

    Account() : id_(""), balance_(0), total_send_(0), total_receive_(0), created_at_(0), merged_into_("") {
    }

    Account(string& id, int cur_ts)
            : id_(id), balance_(0), total_send_(0), total_receive_(0), created_at_(cur_ts), merged_into_("") {
    }
};

struct Transfer {
    string id;
    string source_id;
    string target_id;
    int amount;
    int expires_at;
    bool status_resolved = false; // true if accepted or expired
};

struct ScheduledEvent {
    enum Type { PAYMENT, CASHBACK };

    Type type_;
    string id_;
    string account_id_;
    int amount_;
    int executed_at_;
    bool cancelled_;

    ScheduledEvent() : type_(PAYMENT), id_(""), account_id_(""), amount_(0), executed_at_(0), cancelled_(false) {
    }

    ScheduledEvent(string id, string acc_id, int amount, int timestamp, Type t)
            : type_(t), id_(id), account_id_(acc_id), amount_(amount), executed_at_(timestamp), cancelled_(false) {
    }
};

class Bank {
public:
    unordered_map<string, Account> accounts_;
    vector<ScheduledEvent> event_q_;
    unordered_map<string, Transfer> transfers_;

    int global_payment_idx_ = 0;
    int global_transfer_idx_ = 0;

    bool create_account(int cur_ts, string account_id) {
        process_events(cur_ts);

        if (accounts_.find(account_id) != accounts_.end()) {
            return false;
        }

        Account new_acc = Account(account_id, cur_ts);
        return true;
    }

    string deposit(int timestamp, string account_id, int amount) {
        process_events(timestamp);

        string active_id = get_active_id(account_id);
        if (!accounts_.count(active_id))
            return "";

        accounts_[active_id].balance_ += amount;
        accounts_[active_id].total_receive_ += amount;
        accounts_[active_id].balance_at_[timestamp] = accounts_[active_id].balance_;
        return to_string(accounts_[active_id].balance_);
    }

    // Level 2 & 3 Variant: Pay with Cashback
    string pay(int timestamp, string account_id, int amount) {
        process_events(timestamp);

        string active_id = get_active_id(account_id);
        if (!accounts_.count(active_id) || accounts_[active_id].balance_ < amount)
            return "";

        Account& acc = accounts_[active_id];
        acc.balance_ -= amount;
        acc.total_send_ += amount;
        acc.balance_at_[timestamp] = acc.balance_;

        // Schedule Cashback (24h later)
        string p_id = "payment" + to_string(global_payment_idx_);
        int cashback_amt = amount * 0.02;  // 2% rounded down
        ScheduledEvent event =
                ScheduledEvent(p_id, active_id, cashback_amt, timestamp + 86400000, ScheduledEvent::PAYMENT);
        event_q_.push_back(event);
        global_payment_idx_++;

        return p_id;
    }

    string schedule_payment(int timestamp, string account_id, int amount, int delay) {
        process_events(timestamp);
        if (!accounts_.count(account_id)) return "";

        string p_id = "payment" + to_string(global_payment_idx_);
        process_events[p_id] = {p_id, account_id, amount, timestamp + delay};
        global_payment_idx_++;
        return p_id;
    }

    string cancel_payment(int timestamp, string account_id, string payment_id) {
        // Requirement: Payments scheduled at THIS timestamp happen BEFORE cancellation
        process_state(timestamp);

        if (!scheduled_payments_.count(payment_id)) return "false";

        ScheduledPayment& p = scheduled_payments_[payment_id];
        if (p.account_id != account_id || p.canceled) return "false";

        p.canceled = true;
        scheduled_payments_.erase(payment_id);
        return "true";
    }

    // --- Level 3 Variant: Status Checking ---

    string check_payment_status(int timestamp, string account_id, string payment_id) {
        process_state(timestamp);
        // This checks if the payment is still in the pending queue or already processed
        // In a real system, you'd move processed payments to a history log.
        if (!accounts_.count(account_id)) return "";

        // If it's still in the map and not canceled, it's IN_PROGRESS
        if (scheduled_payments_.count(payment_id)) {
            return "IN_PROGRESS";
        }

        // If it's gone from the map (and we assume it was successful/not canceled),
        // it's COMPLETED or CASHBACK_RECEIVED depending on specific variant requirements.
        return "COMPLETED";
    }

    string transfer(int timestamp, string source_id, string target_id, int amount) {
        process_events(timestamp);

        if (source_id == target_id) return "";
        if (!accounts_.count(source_id) || !accounts_.count(target_id)) return "";
        if (accounts_[source_id].balance_ < amount) return "";

        // Withhold money
        accounts_[source_id].balance_ -= amount;

        string t_id = "transfer" + to_string(global_transfer_idx_);
        transfers_[t_id] = {t_id, source_id, target_id, amount, timestamp + 86400000};
        global_transfer_idx_ += 1;

        return t_id;
    }

    string accept_transfer(int timestamp, string account_id, string transfer_id) {
        process_events(timestamp);
        if (!transfers_.count(transfer_id)) return "false";

        Transfer& t = transfers_[transfer_id];
        if (t.status_resolved || t.target_id != account_id) return "false";

        // Complete the transaction
        accounts_[t.target_id].balance_ += t.amount;

        // Update transaction totals for ranking
        accounts_[t.source_id].total_send_ += t.amount;
        accounts_[t.target_id].total_receive_ += t.amount;

        t.status_resolved = true;
        return "true";
    }

    string top_activity(int timestamp, int n) {
        process_events(timestamp);

        vector<Account*> active_accs;
        for (auto& pair : accounts_) {
            if (pair.second.merged_into_.empty())
                active_accs.push_back(&pair.second);
        }

        sort(active_accs.begin(), active_accs.end(), [](Account* a, Account* b) {
            return a->total_receive_ + a->total_send_ > b->total_receive_ + b->total_send_;
        });

        string res = "";
        for (int i = 0; i < min((int)active_accs.size(), n); ++i) {
            res += active_accs[i]->id_ + "(" + to_string(active_accs[i]->total_receive_ + active_accs[i]->total_send_) +
                   ")" + (i == min((int)active_accs.size(), n) - 1 ? "" : ", ");
        }
        return res;
    }

    // Level 4: Merge Accounts
    string merge_accounts(int timestamp, string id1, string id2) {
        process_events(timestamp);

        if (id1 == id2 || !accounts_.count(id1) || !accounts_.count(id2)) return "false";

        string active1 = get_active_id(id1);
        string active2 = get_active_id(id2);
        if (active1 == active2) return "false";

        Account& acc1 = accounts_[active1];
        Account& acc2 = accounts_[active2];

        acc1.balance_ += acc2.balance_;
        acc1.total_receive_ += acc2.total_receive_;
        acc1.total_send_ += acc2.total_send_;
        acc1.balance_at_[timestamp] = acc1.balance_;

        acc2.merged_into_ = active1; // Mark as merged
        return "true";
    }

    // Level 4: Get Balance at TimeAt
    string get_balance(int timestamp, string account_id, int time_at) {
        process_events(timestamp);

        // Find the account's state at time_at. Note: We use the account's history.
        // If it was merged later, the requirements say the target account inherits the history.
        string active_acc = get_active_id(account_id);
        if (!accounts_.count(active_acc)) return "";

        auto& history = accounts_[active_acc].balance_at_;
        auto it = history.upper_bound(time_at);
        if (it == history.begin()) return ""; // Didn't exist yet

        return to_string(prev(it)->second);
    }
private:
    string get_active_id(string& account_id) {
        while (accounts_.find(account_id) != accounts_.end() && !accounts_[account_id].merged_into_.empty()) {
            account_id = accounts_[account_id].merged_into_;
        }
        return account_id;
    }

    void process_events(int cur_ts) {
        if (event_q_.empty()) {
            return;
        }

        vector<ScheduledEvent> temp;
        for (ScheduledEvent& event : event_q_) {
            if (event.cancelled_) {
                continue;
            }

            if (event.executed_at_ <= cur_ts) {
                string acc_id = get_active_id(event.account_id_);
                if (accounts_.find(acc_id) == accounts_.end()) {
                    continue;
                }

                Account& cur_acc = accounts_[acc_id];
                if (event.type_ == ScheduledEvent::PAYMENT) {
                    if (cur_acc.balance_ <= event.amount_) {
                        continue;
                    }

                    cur_acc.balance_ -= event.amount_;
                    cur_acc.total_send_ += event.amount_;
                    cur_acc.balance_at_[event.executed_at_] = cur_acc.balance_;
                } else {
                    cur_acc.balance_ += event.amount_;
                    cur_acc.total_receive_ += event.amount_;
                    cur_acc.balance_at_[event.executed_at_] = cur_acc.balance_;
                }
            } else {
                temp.push_back(event);
            }
        }

        event_q_ = temp;
    }
};
