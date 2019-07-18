/*
1124. Longest Well-Performing Interval
We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days
for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

Example 1:

Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].


Constraints:

1 <= hours.length <= 10000
0 <= hours[i] <= 16
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

/*
The point is, seen stores the FIRST (very important) appearance of each score.
If we think the initial score is 0,
the accumulative logic will then expand the scores to the two opposite directions on the number line.
Given that knowledge, you can imagine compared with other score - x,
score - 1 is closest to the origin (or say, 0) on the number line.
This means if you want to arrive score - x,
you must have already arrived score - 1 before,
because we start from 0.
Hope this can clarify some confusions.
*/
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        int result = 0;
        int diff = 0;
        unordered_map<int, int> seen;
        for (int i = 0; i < n; ++i) {
            diff += hours[i] > 8 ? 1 : -1;
            if (diff > 0) {
                result = i + 1;
                continue;
            }

            if (seen.find(diff) == seen.end()) {
                seen[diff] = i;
            }
            if (seen.find(diff - 1) != seen.end()) {
                result = max(result, i - seen[diff - 1]);
            }
        }
        return result;
    }
};
