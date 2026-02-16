/*
Full Problem Description
Title: Sequential Portfolio Builder
Initial State: Start with $1000 in cash and an empty portfolio (0 shares of any stock).
Input: A list of trades, where each trade is ["timestamp", "symbol", "direction", "quantity", "price"].
Rules:

Buy (B):

Cash = Cash - (Quantity * Price)

Shares[Symbol] = Shares[Symbol] + Quantity

Sell (S):

Cash = Cash + (Quantity * Price)

Shares[Symbol] = Shares[Symbol] - Quantity

Removal: If a stock's quantity reaches 0 after a transaction, it should be removed from the portfolio representation.

Output: Return the final cash balance and the final portfolio (symbols and quantities).
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

struct Trade {
    std::string timestamp;
    std::string symbol;
    char direction; // 'B' or 'S'
    int quantity;
    double price;
};

void processTrades(const std::vector<std::vector<std::string>>& rawTrades) {
    double cash = 1000.0;
    std::map<std::string, int> portfolio;

    for (const auto& rawTrade : rawTrades) {
        // Parse the input strings
        std::string symbol = rawTrade[1];
        char direction = rawTrade[2][0];
        int qty = std::stoi(rawTrade[3]);
        double price = std::stod(rawTrade[4]);

        double totalValue = qty * price;

        if (direction == 'B') {
            cash -= totalValue;
            portfolio[symbol] += qty;
        } else if (direction == 'S') {
            cash += totalValue;
            portfolio[symbol] -= qty;

            // Rule: Remove stock if quantity reaches 0
            if (portfolio[symbol] == 0) {
                portfolio.erase(symbol);
            }
        }
    }

    // Output Final State
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Final Cash: $" << cash << std::endl;
    std::cout << "Portfolio Holdings:" << std::endl;
    if (portfolio.empty()) {
        std::cout << "  Empty" << std::endl;
    } else {
        for (auto const& [symbol, qty] : portfolio) {
            std::cout << "  " << symbol << ": " << qty << " shares" << std::endl;
        }
    }
}

int main() {
    // Example Input
    std::vector<std::vector<std::string>> trades = {
        {"10:00", "AAPL", "B", "10", "150.00"}, // Buy 10 AAPL @ 150 = -$1500 (Cash: -500)
        {"10:05", "GOOG", "B", "5", "100.00"},  // Buy 5 GOOG @ 100 = -$500 (Cash: -1000)
        {"10:10", "AAPL", "S", "10", "160.00"}  // Sell 10 AAPL @ 160 = +$1600 (Cash: +600)
    };

    processTrades(trades);
    return 0;
}