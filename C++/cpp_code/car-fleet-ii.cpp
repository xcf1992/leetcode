/*
1776. Car Fleet II
https://leetcode.com/problems/car-fleet-ii/

There are n cars traveling at different speeds in the same direction along a one-lane road.
You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:

positioni is the distance between the ith car and the beginning of the road in meters.
It is guaranteed that positioni < positioni+1.
speedi is the initial speed of the ith car in meters per second.
For simplicity, cars can be considered as points moving along the number line.
Two cars collide when they occupy the same position. Once a car collides with another car,
they unite and form a single car fleet.
The cars in the formed fleet will have the same position and the same speed,
which is the initial speed of the slowest car in the fleet.

Return an array answer,
where answer[i] is the time, in seconds,
at which the ith car collides with the next car,
or -1 if the car does not collide with the next car.
Answers within 10-5 of the actual answers are accepted.

Example 1:
Input: cars = [[1,2],[2,1],[4,3],[7,2]]
Output: [1.00000,-1.00000,3.00000,-1.00000]
Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
Example 2:
Input: cars = [[3,4],[5,4],[6,3],[9,1]]
Output: [2.00000,1.00000,1.50000,-1.00000]

Constraints:
1 <= cars.length <= 105
1 <= positioni, speedi <= 106
positioni < positioni+1
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
/*
Intuition
There is some similar sense from the problem of 853. Car Fleet,
we care about the time information in front of each car.

Explanation
We care about the collision time of the cars in front us.
We iteratre from the last to the first car,
and we main a stack of car indices,
where their collision time is strict decreasing.

Imagine a,b,c on the road
if the a catches b later than b catched c,
then a won't catch b but b+c.

Complexity
Time O(n)
Space O(n)

这道题目最核心的逻辑就是如果没有从右往左的扫描的过程中，
扫到了第i个，然后往右计算是否碰撞中，
如果没法在第i + 1追上i + 2以前追上i + 1，那么其实可以把i + 2车当作i的右边第一辆车，以此类推

其实就是简单的追及问题
追不上前面一辆车就看看能否追上前面第二辆车
要么最后追上了某一辆车
要么永远追不上前面的车
而追不上的情况正好stack就空了 自己就成了后面车的塞子
*/
class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int> > &A) {
        int n = A.size();
        vector<int> stack;
        vector<double> res(n, -1);
        for (int i = n - 1; i >= 0; --i) {
            int p = A[i][0];
            int s = A[i][1];
            while (!stack.empty()) {
                int j = stack.back();
                int p2 = A[j][0], s2 = A[j][1];
                if (s <= s2 || (1.0 * (p2 - p) / (s - s2) >= res[j] && res[j] > 0)) {
                    stack.pop_back();
                } else {
                    break;
                }
            }

            if (!stack.empty()) {
                res[i] = 1.0 * (A[stack.back()][0] - p) / (s - A[stack.back()][1]);
            }

            stack.push_back(i);
        }
        return res;
    }
};