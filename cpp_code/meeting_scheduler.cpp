/*
1229. Meeting Scheduler
https://leetcode.com/problems/meeting-scheduler/

Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration,
return the earliest time slot that works for both of them and is of duration duration.

If there is no common time slot that satisfies the requirements, return an empty array.

The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.
It is guaranteed that no two availability slots of the same person intersect with each other.
That is, for any two time slots [start1, end1] and [start2, end2] of the same person,
either start1 > end2 or start2 > end1.

Example 1:
Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
Output: [60,68]

Example 2:
Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
Output: []

Constraints:
1 <= slots1.length, slots2.length <= 10^4
slots1[i].length, slots2[i].length == 2
slots1[i][0] < slots1[i][1]
slots2[i][0] < slots2[i][1]
0 <= slots1[i][j], slots2[i][j] <= 10^9
1 <= duration <= 10^6
*/
#include <iostream>
#include <sstream>
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
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        int n1 = slots1.size();
        int n2 = slots2.size();
        if (n1 == 0 or n2 == 0) {
            return {};
        }

        sort(slots1.begin(), slots1.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });
        sort(slots2.begin(), slots2.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });

        int i = 0;
        int j = 0;
        vector<int> result;
        while (i < n1 and j < n2) {
            int start = max(slots1[i][0], slots2[j][0]);
            int end = min(slots1[i][1], slots2[j][1]);
            if (end - start >= duration) {
                return {start, start + duration};
            }

            if (i == n1 - 1) {
                j += 1;
            }
            else if (j == n2 - 1) {
                i += 1;
            }
            else if (slots1[i][1] < slots2[j][1]) {
                i += 1;
            }
            else {
                j += 1;
            }
        }
        return {};
    }
};
