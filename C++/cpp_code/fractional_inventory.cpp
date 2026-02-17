/*
Robinhood allows customers to buy/sell fractional shares, but the market only trades in whole shares. To facilitate
this, the firm maintains an inventory of stock fractions.Rounding/Format: All inputs are integers representing
hundredths (e.g., 100 is $1.00$ share, 42 is $0.42$ shares).Order Types:Buy (B): Customer wants stock. Robinhood gives
it from inventory. If inventory is insufficient, Robinhood buys whole shares from the market to cover the need, keeping
the remainder in inventory.Sell (S): Customer sells stock to Robinhood. Robinhood adds it to inventory. If inventory
reaches or exceeds 1.00, Robinhood sells whole shares back to the market to keep inventory below $1.00$.Quantity
Variants:"42": A direct fractional share quantity ($0.42$)."$42": A dollar amount. You must convert this to shares
using: $Shares = \frac{Dollar Amount}{Unit Price}$.Constraints:Inventory must always be $\ge 0$ and $< 1$ after
processing an order.This "flattening" (buying/selling whole shares to the market) happens automatically to ensure the
inventory stays in the valid range.
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

typedef vector<string> Order;
typedef vector<string> InvItem;

vector<InvItem> solveInventory(vector<Order> orders, vector<InvItem> inventory) {
    // Map to store current inventory (Symbol -> Quantity in hundredths)
    unordered_map<string, int> invMap;
    vector<string> symbols;  // To preserve original inventory order

    for (auto& item : inventory) {
        invMap[item[0]] = stoi(item[1]);
        symbols.push_back(item[0]);
    }

    for (auto& order : orders) {
        string symbol = order[0];
        string type = order[1];
        string qtyStr = order[2];
        int unitPrice = stoi(order[3]);

        int orderQtyHundredths = 0;

        // 1. Handle Quantity Conversion
        if (qtyStr[0] == '$') {
            // Formula: (DollarAmt * 100) / UnitPrice
            long long dollarAmt = stoll(qtyStr.substr(1));
            orderQtyHundredths = (int)(dollarAmt * 100 / unitPrice);
        } else {
            orderQtyHundredths = stoi(qtyStr);
        }

        // Ensure symbol exists in our tracker
        if (invMap.find(symbol) == invMap.end()) {
            invMap[symbol] = 0;
            symbols.push_back(symbol);
        }

        // 2. Update Inventory based on Order Type
        if (type == "B") {
            // Customer takes from inventory
            invMap[symbol] -= orderQtyHundredths;
        } else {
            // Customer adds to inventory
            invMap[symbol] += orderQtyHundredths;
        }

        // 3. "Flatten" Inventory to stay between [0, 100)
        // This simulates buying/selling whole shares to the market
        while (invMap[symbol] < 0) {
            invMap[symbol] += 100;  // Firm buys 1 whole share from market
        }
        while (invMap[symbol] >= 100) {
            invMap[symbol] -= 100;  // Firm sells 1 whole share to market
        }
    }

    // 4. Format Output
    vector<InvItem> result;
    for (const string& s : symbols) {
        result.push_back({s, to_string(invMap[s])});
    }
    return result;
}

/*
If Robinhood has 0 shares of AAPL and then a customer wishes to purchase 1.5 AAPL shares, Robinhood will need to request
2 shares from the exchange and hold on to the remaining 0.5 shares. If another customer requests to purchase 0.4 shares
of AAPL, Robinhood can use its inventory (0.5 shares) instead of going out to the exchange and will have 0.1 shares of
AAPL remaining. If the third customer requests 0.5 shares, Robinhood can fill 0.1 shares out of inventory but will need
to go to the exchange for an additional share leaving Robinhood’s inventory at 0.6 shares. If a customer requests a
dollar based order, we need to convert it to the relevant number of shares and run through the above steps. Always
ensure the firm has a positive quantity in inventory and has under one share after handling an order. There’s no need
for us to hold onto whole shares! Steps:

Handle buying fractional shares.
Handle selling fractional shares.
Ensure inventory is less than 1 after each order.
e.g. Customer sells AAPL for 0.75 and then another sells AAPL for 0.50 – we have 1.25 inventory. We can sell 1 share to
the market and keep our inventory small at 0.25. Ensure inventory is always non-negative after each order. e.g.
Inventory is 0.2 and the customer buys 0.5 shares: ensure we end up with 0.7 shares in inventory. Always “flatten”!
(steps 3+4) The final 2 digits of every integer is the decimal. e.g. 1000 = 10.00, 20 = 0.20, 100 = 1.

Example scenario:

Input:
// One AAPL buy order for 0.42 shares. AAPL is currently worth $1.
orders: ["AAPL/B/42/100"]

// Inventory for AAPL is currently 0.99 shares.
inventory: ["AAPL/99"]

Expected Output:
// The users buys 0.42 shares from inventory, leaving us with 0.57 shares.
["AAPL/57"]
Another example scenario:

Input:
// One AAPL buy order for 0.42.AAPLiscurrentlyworth1, so that's 0.42 shares.
orders: ["AAPL/B/$42/100"]
// Existing AAPL inventory is 0.50 shares.
inventory: ["AAPL/50"]

Expected Output:
// 0.50 - 0.42 = 0.08 shares leftover.
["AAPL/8"]
Input Format

orders Array of strings, each string would be in the format of $SYMBOL/$BUY_OR_SELL/$QUANTITY/$CURRENT_PRICE

$SYMBOL: Can be “AAPL”, “GOOGL”, “MEOOOOOW” or anything really.
$BUY_OR_SELL: “B” or “S”. B for BUY, S for SELL.
$QUANTITY: Can be a number or a dollar amount (prefixed with $). e.g. “100” for 1 quantity or “$150” for $1.50.
$CURRENT_PRICE: Current price of the symbol with no $ sign. e.g. “1000” for $10.
inventory array of strings, each string would be in the foramt of $SYMBOL/$QUANTITY
An example for AAPL of 0.50 shares and GOOGL of 0.75 shares would be: ["AAPL/50", "GOOGL/75"]

Output Format

Output the final inventory after executing all orders. This is expected to be in the same order and format as the
inventory input, e.g.: ["AAPL/50", "GOOGL/75"] Follow-up

Build an inventory log for all orders from the perspective of the Inventory. The new output would be an array of two
lists where the first value is the current inventory list and the second value is the new list of order logs.

The inventory log is an ordered list of type [symbol, quantity, side, contra] from the perspective of the inventory. For
example:

[“AAPL/100/B/MARKET”], [“AAPL/42/S/CUSTOMER”]
This list means that we first bought 1 share of AAPL from the market, then sold 0.42 shares of AAPL to the customer.

[], [<new_order_log_list>]
*/
struct InventoryState {
    int quantity;
    int orderIndex; // To maintain original output order
};

// Helper to split strings by a delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void solve() {
    // Example Input
    vector<string> orderStrings = {"AAPL/B/$42/100"};
    vector<string> inventoryStrings = {"AAPL/50"};

    unordered_map<string, int> invMap;
    vector<string> symbolOrder;
    vector<string> logs;

    // Initialize Inventory
    for (const string& s : inventoryStrings) {
        vector<string> parts = split(s, '/');
        invMap[parts[0]] = stoi(parts[1]);
        symbolOrder.push_back(parts[0]);
    }

    // Process Orders
    for (const string& ordStr : orderStrings) {
        vector<string> parts = split(ordStr, '/');
        string symbol = parts[0];
        string side = parts[1]; // "B" or "S"
        string qtyStr = parts[2];
        int price = stoi(parts[3]);

        int orderQty = 0;
        if (qtyStr[0] == '$') {
            long long dollars = stoll(qtyStr.substr(1));
            orderQty = (int)(dollars * 100 / price);
        } else {
            orderQty = stoi(qtyStr);
        }

        if (invMap.find(symbol) == invMap.end()) {
            invMap[symbol] = 0;
            symbolOrder.push_back(symbol);
        }

        if (side == "B") {
            // 1. Customer buys from Firm (Firm SELLS to Customer)
            invMap[symbol] -= orderQty;
            logs.push_back(symbol + "/" + to_string(orderQty) + "/S/CUSTOMER");

            // 2. Flatten: If inventory negative, Firm buys whole shares from MARKET
            while (invMap[symbol] < 0) {
                invMap[symbol] += 100;
                logs.push_back(symbol + "/100/B/MARKET");
            }
        } else {
            // 1. Customer sells to Firm (Firm BUYS from Customer)
            invMap[symbol] += orderQty;
            logs.push_back(symbol + "/" + to_string(orderQty) + "/B/CUSTOMER");

            // 2. Flatten: If inventory >= 1 share, Firm sells whole shares to MARKET
            while (invMap[symbol] >= 100) {
                invMap[symbol] -= 100;
                logs.push_back(symbol + "/100/S/MARKET");
            }
        }
    }

    // Final Inventory Output
    cout << "--- Final Inventory ---" << endl;
    for (const string& sym : symbolOrder) {
        cout << sym << "/" << invMap[sym] << endl;
    }

    // Log Output
    cout << "\n--- Inventory Logs ---" << endl;
    for (const string& log : logs) {
        cout << "[" << log << "]" << endl;
    }
}