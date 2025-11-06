/*
1167. Minimum Cost to Connect Sticks
https://leetcode.com/problems/minimum-cost-to-connect-sticks/

You have some sticks with positive integer lengths.
You can connect any two sticks of lengths X and Y into one stick by paying a cost of X + Y.
You perform this action until there is one stick remaining.
Return the minimum cost of connecting all the given sticks into one stick in this way.

Example 1:
Input: sticks = [2,4,3]
Output: 14

Example 2:
Input: sticks = [1,8,3,5]
Output: 30

Constraints:
1 <= sticks.length <= 10^4
1 <= sticks[i] <= 10^4
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        int n = sticks.size();
        if (n <= 1) {
            return 0;
        }

        priority_queue<int, vector<int>, greater<int>> pq(sticks.begin(), sticks.end());
        int result = 0;
        while (pq.size() > 1) {
            int s1 = pq.top();
            pq.pop();
            int s2 = pq.top();
            pq.pop();
            result += s1 + s2;
            pq.push(s1 + s2);
        }
        return result;
    }
};