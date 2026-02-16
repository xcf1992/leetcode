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
    vector<string> symbols; // To preserve original inventory order

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
            invMap[symbol] += 100; // Firm buys 1 whole share from market
        }
        while (invMap[symbol] >= 100) {
            invMap[symbol] -= 100; // Firm sells 1 whole share to market
        }
    }

    // 4. Format Output
    vector<InvItem> result;
    for (const string& s : symbols) {
        result.push_back({s, to_string(invMap[s])});
    }
    return result;
}

int main() {
    // Example: Buy $42 worth of AAPL at price 100 (0.42 shares)
    // Starting inventory 50 (0.50 shares)
    // Result: 50 - 42 = 8
    vector<Order> orders = {{"AAPL", "B", "$42", "100"}};
    vector<InvItem> inventory = {{"AAPL", "50"}};

    auto finalInv = solveInventory(orders, inventory);

    for (auto& item : finalInv) {
        cout << item[0] << ": " << item[1] << endl;
    }

    return 0;
}