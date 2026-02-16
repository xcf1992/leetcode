/*
Full Problem DescriptionInput:A string or list of pairs [timestamp, price].Input is typically guaranteed to be sorted by
timestamp.Timestamps and prices are non-negative integers.Task:Group the prices into fixed intervals of 10 time units
(e.g., $[0, 10)$, $[10, 20)$, $[20, 30)$, ...). If an interval has no data points, it is often skipped, though some
variations ask you to "carry over" the last price. For each interval that contains data, calculate:Start Time: The
multiple of 10 that begins the interval (e.g., if a tick is at time 12, its start time is 10).Open: The price of the
earliest timestamp in that 10-unit window.Close: The price of the latest timestamp in that 10-unit window.High: The
maximum price recorded in that window.Low: The minimum price recorded in that window.Output Format:Usually a string of
formatted blocks: {start,open,close,high,low} or a vector of objects.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <climits>

struct Candlestick {
    int startTime;
    int open;
    int close;
    int high;
    int low;
    int firstTimestamp;  // Helper to track earliest price
    int lastTimestamp;   // Helper to track latest price
};

std::string computeCandlesticks(std::vector<std::pair<int, int>>& prices) {
    if (prices.empty())
        return "";

    // Map: intervalStart -> Candlestick data
    std::map<int, Candlestick> intervals;

    for (const auto& p : prices) {
        int time = p.first;
        int price = p.second;
        int start = (time / 10) * 10;  // Round down to nearest 10

        if (intervals.find(start) == intervals.end()) {
            // Initialize new interval
            intervals[start] = {start, price, price, price, price, time, time};
        } else {
            Candlestick& cs = intervals[start];
            // Update High/Low
            cs.high = std::max(cs.high, price);
            cs.low = std::min(cs.low, price);

            // Update Open (if this timestamp is earlier than what we have)
            if (time < cs.firstTimestamp) {
                cs.firstTimestamp = time;
                cs.open = price;
            }
            // Update Close (if this timestamp is later than what we have)
            if (time >= cs.lastTimestamp) {
                cs.lastTimestamp = time;
                cs.close = price;
            }
        }
    }

    // Format output string
    std::string result = "";
    for (auto const& [start, cs] : intervals) {
        result += "{" + std::to_string(cs.startTime) + "," + std::to_string(cs.open) + "," + std::to_string(cs.close) +
                  "," + std::to_string(cs.high) + "," + std::to_string(cs.low) + "}";
    }

    return result;
}

int main() {
    // Example Input: [[0, 1], [10, 3], [12, 2], [19, 4], [35, 5]]
    std::vector<std::pair<int, int>> input = {{0, 1}, {10, 3}, {12, 2}, {19, 4}, {35, 5}};

    std::cout << computeCandlesticks(input) << std::endl;
    // Expected Output: {0,1,1,1,1}{10,3,4,4,2}{30,5,5,5,5}
    return 0;
}