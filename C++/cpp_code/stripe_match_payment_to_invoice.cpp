/*
https://www.hack2hire.com/companies/stripe/coding-questions/697697e35ed12b33b05f0f4b/practice?questionId=697699035ed12b33b05f0f4e
Match Payment to Invoice

A payment reconciliation system manages two types of data: payments and invoices.

Payment Record: Each payment is provided as a string in the format "<paymentId>,<paymentAmount>,<memo>". The memo field
is a note that may include a reference like "paying off:{invoiceId}", indicating which invoice the payment is for.

Invoice Record: Each invoice is given as a string in the format "<invoiceId>,<invoiceAmount>,<dueDate>".

Given a single payment string and a list of invoice strings, implement a function to link the payment to the correct
invoice and produce an event string in the following structure, using the corresponding paymentId, paymentAmount,
invoiceId, and dueDate: "<paymentId> paid <paymentAmount> for invoice <invoiceId> on date <dueDate>"

Use the following logic to match the payment to an invoice:

Memo Reference: If the payment's memo includes "paying off:<invoiceId>", extract the invoiceId. If this invoiceId
matches one in the invoice list, generate the event string for that invoice.

Amount Match: If the memo does not reference an invoice, look for invoices with an amount equal to paymentAmount. If
there are multiple matches, choose the one with the earliest dueDate ("YYYY-MM-DD" format). Generate the event string
for this invoice if found.

No Match: If neither approach finds a matching invoice, return an empty string.

Constraints:

1 ≤ payment.length ≤ 200
0 ≤ invoices.length ≤ 104
paymentAmount and every invoiceAmount are positive integers.
Each invoiceId is unique.
There is at most one matching invoice for any given payment by the described rules.
Example 1:

Input: payment = "PAY123,1000,paying off: INV123", invoices = ["INV111,500,2024-05-01", "INV123,1000,2024-06-01"]
Output: "PAY123 paid 1000 for invoice INV123 on date 2024-06-01"
Explanation: The memo contains "paying off: INV123" and invoice "INV123" exists, so the function returns the formatted
string using its due date.

Example 2:

Input: payment = "PAY456,500,partial payment", invoices = ["INV111,500,2024-05-01", "INV123,1000,2024-06-01",
"INV222,500,2024-04-20"] Output: "PAY456 paid 500 for invoice INV222 on date 2024-04-20"

Example 3:

Input: payment = "PAY999,200,unrelated", invoices = ["INV111,500,2024-05-01", "INV123,1000,2024-06-01"]
Output: ""
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

class Solution {
private:
    vector<string> split(const string& str, char delimiter, int limit = -1) {
        vector<string> result;
        stringstream ss(str);
        string item;

        if (limit > 0) {
            for (int i = 0; i < limit - 1 && getline(ss, item, delimiter); i++) {
                result.push_back(item);
            }
            if (getline(ss, item)) {
                string remaining;
                getline(ss, remaining, '\0');
                if (!remaining.empty()) {
                    item += delimiter + remaining;
                }
                result.push_back(item);
            }
        } else {
            while (getline(ss, item, delimiter)) {
                result.push_back(item);
            }
        }

        return result;
    }

    string get_invoice_id_from_memo(const string& memo) {
        string marker = "paying off:";
        size_t index = memo.find(marker);
        if (index == string::npos) {
            return "";
        }

        string tail = memo.substr(index + marker.size());
        // Trim leading whitespace
        size_t start = 0;
        while (start < tail.length() && isspace(tail[start])) {
            start++;
        }
        tail = tail.substr(start);

        if (tail.empty()) {
            return "";
        }

        size_t end = 0;
        while (end < tail.length() && !isspace(tail[end])) {
            end++;
        }
        return tail.substr(0, end);
    }

    string formatResult(const string& paymentId, int amount, const string& invoiceId, const string& dueDate) {
        return paymentId + " paid " + to_string(amount) + " for invoice " + invoiceId + " on date " + dueDate;
    }

public:
    string matchPaymentToInvoice(string payment, vector<string> invoices) {
        vector<string> payment_detail = split(payment, ',', 3);
        string pay_id = payment_detail[0];
        int pay_amount = stoi(payment_detail[1]);
        string pay_memo = payment_detail[2];

        // Check if memo contains invoice ID
        string pay_memo_id = get_invoice_id_from_memo(pay_memo);
        if (!pay_memo_id.empty()) {
            for (const string& invoice : invoices) {
                vector<string> parts = split(invoice, ',');
                string invoiceId = parts[0];
                if (invoiceId == pay_memo_id) {
                    string dueDate = parts[2];
                    return formatResult(pay_id, pay_amount, invoiceId, dueDate);
                }
            }
            return "";
        }

        // Match by amount and earliest due date
        string matchedId = "";
        string earliestDueDate = "";
        int matchedAmount = 0;

        for (const string& invoice : invoices) {
            vector<string> parts = split(invoice, ',');
            string invoiceId = parts[0];
            int amount = stoi(parts[1]);
            string dueDate = parts[2];

            if (amount == pay_amount) {
                if (earliestDueDate.empty() || dueDate < earliestDueDate) {
                    earliestDueDate = dueDate;
                    matchedId = invoiceId;
                    matchedAmount = amount;
                }
            }
        }

        if (!matchedId.empty()) {
            return formatResult(pay_id, matchedAmount, matchedId, earliestDueDate);
        }

        return "";
    }
};
/*
Follow-up:
In this follow-up, if a payment does not match any invoice by identifier or by exact amount, you are also given an
integer forgiveness.

Among all invoices where the absolute difference between invoice amount and payment amount is at most forgiveness (that
is, abs(invoiceAmount - paymentAmount) ≤ forgiveness), select the one with the earliest due date.

Return a string in the following format, including the forgiven amount: "<paymentId> paid <paymentAmount> for invoice
<invoiceId> on date <dueDate> (forgiven <forgivenAmount>)

where forgivenAmount is the absolute difference between paymentAmount and invoiceAmount.

If no such invoice exists, return an empty string.

Example 1:

Input: payment = "PAY789,510,overpayment", invoices = ["INV111,500,2024-05-01", "INV123,1000,2024-06-01"], forgiveness =
15 Output: "PAY789 paid 510 for invoice INV111 on date 2024-05-01 (forgiven 10)" Explanation: There is no invoice ID in
the memo, and no invoice with an exact amount of 510. However, invoice "INV111" has an amount of 500, which differs from
the payment amount by 10. Since 10 is less than or equal to the forgiveness limit of 15, this invoice is selected. The
forgiven amount is 10, and its due date is "2024-05-01".

Example 2:

Input: payment = "PAY123,500,paying off: INV123", invoices = ["INV111,500,2024-05-01", "INV123,1000,2024-06-01"],
forgiveness = 10 Output: "PAY123 paid 500 for invoice INV123 on date 2024-06-01"

Example 3:

Input: payment = "PAY100,300,payment", invoices = ["INV1,300,2024-03-01", "INV2,300,2024-01-01"], forgiveness = 5
Output: "PAY100 paid 300 for invoice INV2 on date 2024-01-01"
*/
class Solution {
public:
    string matchPayment(string payment, vector<string> invoices, int forgiveness) {
        vector<string> paymentParts = split(payment, ',', 3);
        string paymentId = paymentParts[0];
        int paymentAmount = stoi(paymentParts[1]);
        string memo = paymentParts[2];

        // Check if memo contains invoice ID
        string memoInvoiceId = extractInvoiceId(memo);

        if (!memoInvoiceId.empty()) {
            for (const string& invoice : invoices) {
                vector<string> parts = split(invoice, ',');
                string invoiceId = parts[0];
                if (invoiceId == memoInvoiceId) {
                    string dueDate = parts[2];
                    return formatResult(paymentId, paymentAmount, invoiceId, dueDate);
                }
            }
        }

        // Match by exact amount and earliest due date
        string matchedId = "";
        string earliestDueDate = "";
        for (const string& invoice : invoices) {
            vector<string> parts = split(invoice, ',');
            string invoiceId = parts[0];
            int invoiceAmount = stoi(parts[1]);
            string dueDate = parts[2];

            if (invoiceAmount == paymentAmount) {
                if (earliestDueDate.empty() || dueDate < earliestDueDate) {
                    earliestDueDate = dueDate;
                    matchedId = invoiceId;
                }
            }
        }

        if (!matchedId.empty()) {
            return formatResult(paymentId, paymentAmount, matchedId, earliestDueDate);
        }

        // Match by forgiveness and earliest due date
        string forgivenMatchedId = "";
        string forgivenEarliestDate = "";
        int forgivenAmount = 0;

        for (const string& invoice : invoices) {
            vector<string> parts = split(invoice, ',');
            string invoiceId = parts[0];
            int invoiceAmount = stoi(parts[1]);
            string dueDate = parts[2];

            int diff = abs(invoiceAmount - paymentAmount);
            if (diff <= forgiveness) {
                if (forgivenEarliestDate.empty() || dueDate < forgivenEarliestDate) {
                    forgivenEarliestDate = dueDate;
                    forgivenMatchedId = invoiceId;
                    forgivenAmount = diff;
                }
            }
        }

        if (!forgivenMatchedId.empty()) {
            return formatForgivenResult(paymentId, paymentAmount, forgivenMatchedId, forgivenEarliestDate,
                                        forgivenAmount);
        }

        return "";
    }

private:
    vector<string> split(const string& str, char delimiter, int limit = -1) {
        vector<string> result;
        stringstream ss(str);
        string item;

        if (limit == -1) {
            while (getline(ss, item, delimiter)) {
                result.push_back(item);
            }
        } else {
            int count = 0;
            while (count < limit - 1 && getline(ss, item, delimiter)) {
                result.push_back(item);
                count++;
            }
            if (getline(ss, item)) {
                string remaining = item;
                string temp;
                while (getline(ss, temp)) {
                    remaining += delimiter + temp;
                }
                result.push_back(remaining);
            }
        }
        return result;
    }

    string extractInvoiceId(const string& memo) {
        string marker = "paying off:";
        size_t index = memo.find(marker);
        if (index == string::npos) {
            return "";
        }

        string tail = memo.substr(index + marker.length());
        // Trim leading whitespace
        size_t start = tail.find_first_not_of(" \t\n\r");
        if (start == string::npos) {
            return "";
        }
        tail = tail.substr(start);

        if (tail.empty()) {
            return "";
        }

        size_t end = 0;
        while (end < tail.length() && tail[end] != ' ' && tail[end] != '\t' && tail[end] != '\n' && tail[end] != '\r') {
            end++;
        }
        return tail.substr(0, end);
    }

    string formatResult(const string& paymentId, int amount, const string& invoiceId, const string& dueDate) {
        return paymentId + " paid " + to_string(amount) + " for invoice " + invoiceId + " on date " + dueDate;
    }

    string formatForgivenResult(const string& paymentId, int amount, const string& invoiceId, const string& dueDate,
                                int forgivenAmount) {
        return paymentId + " paid " + to_string(amount) + " for invoice " + invoiceId + " on date " + dueDate +
               " (forgiven " + to_string(forgivenAmount) + ")";
    }
};