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


class Logger {
private:
    unordered_map<string, int> printTimetamp;

public:
    /** Initialize your data structure here. */
    Logger() {}
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        if (printTimetamp.find(message) == printTimetamp.end()) {
            printTimetamp[message] = timestamp;
            return true;
        }

        if (timestamp - printTimetamp[message] >= 10) {
            printTimetamp[message] = timestamp;
            return true;
        }

        return false;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */

int main() {
    Solution s;
    return 0;
}