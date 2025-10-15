/*
621. Task Scheduler
Given a char array representing tasks CPU need to do.
It contains capital letters A to Z where different letters represent different tasks.
Tasks could be done without original order.
Each task could be done in one interval.
For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks,
there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.


Note:

The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].
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
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> counts(26, 0);
        int frequency = 0;
        for (char c : tasks) {
            counts[c - 'A'] += 1;
            frequency = max(frequency, counts[c - 'A']);
        }

        int result = (n + 1) * (frequency - 1);
        for (int count : counts) {
            result += count == frequency ? 1 : 0;
        }
        return max(result, (int)tasks.size());
    }
};
