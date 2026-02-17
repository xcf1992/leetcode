/*
A trade is defined as a fixed-width string containing the 4 properties given below separated by commas:

Symbol (4 alphabetical characters, left-padded by spaces)
Type (either "B" or "S" for buy or sell)
Quantity (4 digits, left-padded by zeros)
ID (6 alphanumeric characters)
e.g.
"AAPL,B,0100,ABC123"

which represents a trade of a buy of 100 shares of AAPL with ID "ABC123"

Given two lists of trades - called "house" and "street" trades, write code to filter out groups of matches between
trades and return a list of unmatched house and street trades sorted alphabetically. There are many ways to match
trades, the first and most important way is an exact match (Tests 1-5):

An exact match is a house_trade+street_trade pair with identical symbol, type, quantity, and ID
Note: Trades are distinct but not unique

For example, given the following input:

// house_trades:
[
"AAPL,B,0100,ABC123",
"AAPL,B,0100,ABC123",
"GOOG,S,0050,CDC333"
]

// street_trades:
[
" FB,B,0100,GBGGGG",
"AAPL,B,0100,ABC123"
]

We would expect the following output:

[
" FB,B,0100,GBGGGG",
"AAPL,B,0100,ABC123",
"GOOG,S,0050,CDC333"
]

Because the first (or second) house trade and second street trade form an exact match, leaving behind three unmatched
trades.

Follow-up 1 (Test 6,7,8,9): A "fuzzy" match is a house_trade+street_trade pair with identical symbol, type, and quantity
ignoring ID. Prioritize exact matches over fuzzy matches. Prioritize matching the earliest alphabetical house trade with
the earliest alphabetical street trade in case of ties.

Follow-up 2: (Test 10) An offsetting match is a house_trade+house_trade or street_trade+street_trade pair where the
symbol and quantity of both trades are the same, but the type is different (one is a buy and one is a sell). Prioritize
exact and fuzzy matches over offsetting matches. Prioritize matching the earliest alphabetical buy with the earliest
alphabetical sell.

[execution time limit] 4 seconds (py3)

[input] array.string house_trades

[input] array.string street_trades

[output] array.string

A list of unmatched trades both house and street, ordered alphabetically
Some Testcases:

TEST1
Input:

house_trades:
["AAPL,B,0100,ABC123",
 "GOOG,S,0050,CDC333"]
street_trades:
["  FB,B,0100,GBGGGG",
 "AAPL,B,0100,ABC123"]
Expected Output:

["  FB,B,0100,GBGGGG",
 "GOOG,S,0050,CDC333"]
TEST2
Input:

house_trades:
["AAPL,S,0010,ZYX444",
 "AAPL,S,0010,ZYX444",
 "AAPL,B,0010,ABC123",
 "GOOG,S,0050,GHG545"]
street_trades:
["GOOG,S,0050,GHG545",
 "AAPL,S,0010,ZYX444",
 "AAPL,B,0010,TTT222"]
Expected Output:

["AAPL,S,0010,ZYX444"]
TESTS2
Input:

house_trades:
["AAPL,B,0010,ABC123",
 "AAPL,S,0015,ZYX444",
 "AAPL,S,0015,ZYX444",
 "GOOG,S,0050,GHG545"]
street_trades:
["GOOG,S,0050,GHG545",
 "AAPL,S,0015,ZYX444",
 "AAPL,B,0500,TTT222"]
Expected Output:

["AAPL,B,0010,ABC123",
 "AAPL,B,0500,TTT222",
 "AAPL,S,0015,ZYX444"]
TEST3
Input:

house_trades:
["AAPL,B,0100,ABC123",
 "AAPL,B,0100,ABC123",
 "AAPL,B,0100,ABC123",
 "GOOG,S,0050,CDC333"]
street_trades:
["  FB,B,0100,GBGGGG",
 "AAPL,B,0100,ABC123"]
Expected Output:

["  FB,B,0100,GBGGGG",
 "AAPL,B,0100,ABC123",
 "AAPL,B,0100,ABC123",
 "GOOG,S,0050,CDC333"]
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

// Structure to hold parsed trade data
struct Trade {
    string full_str;
    string symbol;
    char type;
    string quantity;
    string id;

    Trade(string s) : full_str(s) {
        symbol = s.substr(0, 4);
        type = s[5];
        quantity = s.substr(7, 4);
        id = s.substr(12);
    }

    // Key for Fuzzy Match (Symbol + Type + Quantity)
    string fuzzy_key() const {
        return symbol + "," + type + "," + quantity;
    }

    // Key for Offsetting Match (Symbol + Quantity)
    string offset_key() const {
        return symbol + "," + quantity;
    }
};

vector<string> filterTrades(vector<string> house_trades, vector<string> street_trades) {
    multiset<string> house(house_trades.begin(), house_trades.end());
    multiset<string> street(street_trades.begin(), street_trades.end());

    // --- 1. Exact Matches ---
    for (auto it = house.begin(); it != house.end();) {
        auto found = street.find(*it);
        if (found != street.end()) {
            street.erase(found);
            it = house.erase(it);  // Erase returns next iterator
        } else {
            ++it;
        }
    }

    // Helper to process remaining trades into objects for fuzzy/offsetting
    auto get_remaining = [](multiset<string>& ms) {
        vector<Trade> v;
        for (const string& s : ms)
            v.push_back(Trade(s));
        return v;
    };

    vector<Trade> h_rem = get_remaining(house);
    vector<Trade> s_rem = get_remaining(street);

    vector<bool> h_used(h_rem.size(), false);
    vector<bool> s_used(s_rem.size(), false);

    // --- 2. Fuzzy Matches (House vs Street) ---
    for (int i = 0; i < h_rem.size(); ++i) {
        for (int j = 0; j < s_rem.size(); ++j) {
            if (!h_used[i] && !s_used[j] && h_rem[i].fuzzy_key() == s_rem[j].fuzzy_key()) {
                h_used[i] = s_used[j] = true;
                break;  // Match found, move to next house trade
            }
        }
    }

    // --- 3. Offsetting Matches (Within House, Within Street, or Between) ---
    // The prompt implies prioritizing internal offsets if fuzzy matches are done.
    // We combine all remaining into one pool to match Buy vs Sell for offsets.
    auto solve_offsets = [&](vector<Trade>& trades, vector<bool>& used) {
        for (int i = 0; i < trades.size(); ++i) {
            if (used[i])
                continue;
            for (int j = i + 1; j < trades.size(); ++j) {
                if (!used[j] && trades[i].offset_key() == trades[j].offset_key() && trades[i].type != trades[j].type) {
                    used[i] = used[j] = true;
                    break;
                }
            }
        }
    };

    solve_offsets(h_rem, h_used);
    solve_offsets(s_rem, s_used);

    // Collect results
    vector<string> result;
    for (int i = 0; i < h_rem.size(); ++i)
        if (!h_used[i])
            result.push_back(h_rem[i].full_str);
    for (int i = 0; i < s_rem.size(); ++i)
        if (!s_used[i])
            result.push_back(s_rem[i].full_str);

    sort(result.begin(), result.end());
    return result;
}

int main() {
    // Example from your TEST 1
    vector<string> h = {"AAPL,B,0100,ABC123", "GOOG,S,0050,CDC333"};
    vector<string> s = {"  FB,B,0100,GBGGGG", "AAPL,B,0100,ABC123"};

    vector<string> res = filterTrades(h, s);
    for (const string& str : res)
        cout << "\"" << str << "\"" << endl;

    return 0;
}