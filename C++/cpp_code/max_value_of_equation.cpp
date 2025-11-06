/*
1499. Max Value of Equation
https://leetcode.com/problems/max-value-of-equation/

Given an array points containing the coordinates of points on a 2D plane,
sorted by the x-values,
where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length.
You are also given an integer k.

Find the maximum value of the equation yi + yj + |xi - xj|
where |xi - xj| <= k and 1 <= i < j <= points.length.
It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.

Example 1:
Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
Output: 4
Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 +
|1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1. No other
pairs satisfy the condition, so we return the max of 4 and 1.

Example 2:
Input: points = [[0,0],[3,0],[9,2]], k = 3
Output: 3
Explanation: Only the first two points have an absolute difference of 3 or less in the x-values, and give the value of 0
+ 0 + |0 - 3| = 3.

Constraints:
2 <= points.length <= 10^5
points[i].length == 2
-10^8 <= points[i][0], points[i][1] <= 10^8
0 <= k <= 2 * 10^8
points[i][0] < points[j][0] for all 1 <= i < j <= points.length
xi form a strictly increasing sequence.
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
#include <set>
using namespace std;
/*
Explanation
Because xi < xj,
yi + yj + |xi - xj| = (yi - xi) + (yj + xj)

So we only need to find out the maximum yi - xi.
To find out the maximum element in a sliding window,
we can use priority queue or stack.
*/
class Solution1 {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        //(y-x, x)
        priority_queue<vector<int>, vector<vector<int>>> pq;

        int ans = INT_MIN;

        for (vector<int>& point : points) {
            // current point serves as points[j]
            int x = point[0], y = point[1];

            /*
            we only need points[i] s.t. |x_i - x_j| <= k,
            and because points is already sorted by x,
            so x_i must <= x_j, the inequality can be expressed as
            x_j - x_i <= k.
            we will discard points[i] s.t. x_j - x_i > k
            */
            while (!pq.empty() && x - pq.top()[1] > k) {
                pq.pop();
            }

            if (!pq.empty()) {
                /*
                y_i + y_j + |x_i - x_j|
                = y_i + y_j + x_j - x_i
                = (y_i - x_i) + (y_j + x_j)

                in which y_j + x_j is solely determined
                by current point(it serves as points[j]),
                so what we want to find is the points[i]
                s.t. i < j and with max (y_i - x_i)
                */
                ans = max(ans, pq.top()[0] + (y + x));
            }

            pq.push({y - x, x});
        }

        return ans;
    }
};

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        //(y-x, x)
        deque<vector<int>> deq;

        int ans = INT_MIN;

        for (vector<int>& point : points) {
            int x = point[0], y = point[1];

            while (!deq.empty() && x - deq.front()[1] > k) {
                deq.pop_front();
            }

            if (!deq.empty()) {
                ans = max(ans, deq.front()[0] + (y + x));
            }

            /*
            keep the deque decreasing(fronter element has larger y-x)
            the element before current point must have larger y-x
            */
            while (!deq.empty() && deq.back()[0] <= y - x) {
                deq.pop_back();
            }

            deq.push_back({y - x, x});
        }

        return ans;
    }
};