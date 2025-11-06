/*
1705. Maximum Number of Eaten Apples
https://leetcode.com/problems/maximum-number-of-eaten-apples/

There is a special kind of apple tree that grows apples every day for n days.
On the ith day, the tree grows apples[i] apples that will rot after days[i] days,
that is on day i + days[i] the apples will be rotten and cannot be eaten.
On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.

You decided to eat at most one apple a day (to keep the doctors away).
Note that you can keep eating after the first n days.
Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.

Example 1:
Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
Output: 7
Explanation: You can eat 7 apples:
- On the first day, you eat an apple that grew on the first day.
- On the second day, you eat an apple that grew on the second day.
- On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day
rot.
- On the fourth to the seventh days, you eat apples that grew on the fourth day.
Example 2:
Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
Output: 5
Explanation: You can eat 5 apples:
- On the first to the third day you eat apples that grew on the first day.
- Do nothing on the fouth and fifth days.
- On the sixth and seventh days you eat apples that grew on the sixth day.

Constraints:
apples.length == n
days.length == n
1 <= n <= 2 * 104
0 <= apples[i], days[i] <= 2 * 104
days[i] = 0 if and only if apples[i] = 0.
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
    typedef pair<int, int> P;  // {last date before expiration, number of apples}
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int ans = 0;
        int n = apples.size();
        // min heap, the pair with the smallest expiration date is on the top
        priority_queue<P, vector<P>, greater<P>> que;
        int i = 0;
        while (i < n or que.size() > 0) {
            // add today's apples
            if (i < n && apples[i] > 0) {
                que.push({i + days[i] - 1, apples[i]});
            }

            // remove outdate apples
            while (que.size() && que.top().first < i) {
                que.pop();
            }

            // get the apple that can be eat today
            if (que.size()) {
                auto p = que.top();
                que.pop();

                if (p.second > 1) {
                    que.push({p.first, p.second - 1});
                }
                ++ans;
            }
            ++i;
        }
        return ans;
    }
};