/*
https://leetcode.com/problems/maximum-earnings-from-taxi/description/
2008. Maximum Earnings From Taxi

There are n points on a road you are driving your taxi on. The n points on the road are labeled from 1 to n in the
direction you are going, and you want to drive from point 1 to point n to make money by picking up passengers. You
cannot change the direction of the taxi.

The passengers are represented by a 0-indexed 2D integer array rides, where rides[i] = [starti, endi, tipi] denotes the
ith passenger requesting a ride from point starti to point endi who is willing to give a tipi dollar tip.

For each passenger i you pick up, you earn endi - starti + tipi dollars. You may only drive at most one passenger at a
time.

Given n and rides, return the maximum number of dollars you can earn by picking up the passengers optimally.

Note: You may drop off a passenger and pick up a different passenger at the same point.



Example 1:

Input: n = 5, rides = [[2,5,4],[1,5,1]]
Output: 7
Explanation: We can pick up passenger 0 to earn 5 - 2 + 4 = 7 dollars.
Example 2:

Input: n = 20, rides = [[1,6,1],[3,10,2],[10,12,3],[11,12,2],[12,15,2],[13,18,1]]
Output: 20
Explanation: We will pick up the following passengers:
- Drive passenger 1 from point 3 to point 10 for a profit of 10 - 3 + 2 = 9 dollars.
- Drive passenger 2 from point 10 to point 12 for a profit of 12 - 10 + 3 = 5 dollars.
- Drive passenger 5 from point 13 to point 18 for a profit of 18 - 13 + 1 = 6 dollars.
We earn 9 + 5 + 6 = 20 dollars in total.


Constraints:

1 <= n <= 105
1 <= rides.length <= 3 * 104
rides[i].length == 3
1 <= starti < endi <= n
1 <= tipi <= 105
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
#include <numeric>
using namespace std;

/*
逐步解析这个解法
核心思路
dp[i] 表示：出租车到达点 i 时，能赚到的最大金额。
第一步：排序
cppsort(rides.begin(), rides.end(), ...);
把所有乘客按上车点从小到大排序。这样当我们从左往右扫描每个点时，能按顺序处理所有乘客。
第二步：逐点扫描（核心逻辑）
cppfor (int i = 1; i <= n; ++i) {
我们从点1走到点n，每到一个点做两件事：

第一件事：不载客，直接往前走
cppdp[i] = max(dp[i], dp[i - 1]);
意思是：如果我空车从点 i-1 开到点 i，不赚钱也不亏钱，所以 dp[i] 至少和 dp[i-1] 一样多。
这保证了收益是单调不减的——你不会因为往前开而变穷。

第二件事：尝试在点 i 接所有在这里上车的乘客
cppwhile (j < rides.size() && rides[j][0] == i) {
    dp[rides[j][1]] = max(dp[rides[j][1]], dp[i] + rides[j][1] - rides[j][0] + rides[j][2]);
    j++;
}
这里 j 是一个全局指针，指向当前还没处理的乘客。因为 rides 已经按上车点排好序了，所以所有在点 i 上车的乘客一定是连续的。
对于每个在点 i 上车的乘客 [start, end, tip]：

收益 = end - start + tip
如果我在点 i 接了这个人，到达 end 时的总收益 = dp[i] + (end - start + tip)
用这个值去更新 dp[end]

一个具体例子
假设 n = 5，乘客有：[1, 4, 1] 和 [2, 5, 2]
初始：dp = [0, 0, 0, 0, 0, 0]
i = 1：

dp[1] = max(dp[1], dp[0]) = 0（空车走过来）
乘客 [1, 4, 1] 在这里上车：dp[4] = max(dp[4], dp[1] + 4-1+1) = 4
dp 变成：[0, 0, 0, 0, 4, 0]

i = 2：

dp[2] = max(dp[2], dp[1]) = 0
乘客 [2, 5, 2] 在这里上车：dp[5] = max(dp[5], dp[2] + 5-2+2) = 5
dp 变成：[0, 0, 0, 0, 4, 5]

i = 3： dp[3] = max(dp[3], dp[2]) = 0，没乘客上车
i = 4： dp[4] = max(dp[4], dp[3]) = max(4, 0) = 4，没乘客上车
i = 5： dp[5] = max(dp[5], dp[4]) = max(5, 4) = 5
答案：dp[5] = 5
为什么这样能处理"同时只载一个人"？
关键在于：接乘客时，我们用的是 dp[i]（上车点的收益），更新的是 dp[end]（下车点的收益）。在 start 到 end
之间，这个车是被占用的，不会影响中间点的 dp 值。其他乘客如果上车点在这段区间内，他们会用自己上车点的 dp
值来计算，互不干扰。 一句话总结
在每个点，你做一个选择：要么空车路过（继承前一个点的收益），要么在这里接一个乘客（把收益"传送"到下车点）。最终 dp[n]
就是最优解。
*/
class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        sort(rides.begin(), rides.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); });

        vector<long long> dp(n + 1, 0);
        int j = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = max(dp[i], dp[i - 1]);
            while (j < rides.size() && rides[j][0] == i) {
                dp[rides[j][1]] = max(dp[rides[j][1]], dp[i] + rides[j][1] - rides[j][0] + rides[j][2]);
                j += 1;
            }
        }
        return dp[n];
    }
};

class Solution1 {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        sort(rides.begin(), rides.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]); });

        map<int, long long> dp;
        dp[0] = 0;
        for (const vector<int>& ride : rides) {
            long long start = ride[0];
            long long end = ride[1];
            long long tips = ride[2];
            long long cur_earning = prev(dp.upper_bound(start))->second + end - start + tips;
            if (cur_earning > dp.rbegin()->second) {
                dp[end] = cur_earning;
            }
        }
        return dp.rbegin()->second;
    }
};
