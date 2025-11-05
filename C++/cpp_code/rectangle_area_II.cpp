/*
850. Rectangle Area II

We are given a list of (axis-aligned) rectangles.
Each rectangle[i] = [x1, y1, x2, y2] ,
where (x1, y1) are the coordinates of the bottom-left corner,
and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.

Find the total area covered by all rectangles in the plane.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: As illustrated in the picture.

Example 2:
Input: [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.

Note:
1 <= rectangles.length <= 200
rectanges[i].length = 4
0 <= rectangles[i][j] <= 10^9
The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit in a 64-bit signed integer.
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
#include <map>
#include <numeric>
using namespace std;
/*
Scan from y = 0, count the coverage of rectangles on x.
For example, at y = 0, the intervale [0, 3] is covered by rectangles.
The current sum of coverage is 3.

Then we move our scan line upper to next y.
At y = 1, we add (1 - 0) * 3 = 3 to area. Now area = 3.
And we update the sum of coverage to 2 because it's coverd on [0, 2].

Then we move our scan line upper to next y.
At y = 2, we add (2 - 1) * 2 = 2 to area. Now area = 5.
And we update the sum of coverage to 1 because it's coverd on [1, 2].

Then we move our scan line upper to next y.
At y = 3, we add (3 - 2) * 1 = 1 to area. Now area = 6.
And we update the sum of coverage to 0.

The final result is 6.

Time Complexity:
We checked every y value, and for every y, we count the coverage of x.
So this a O(N^2) solution.
In fact I expected the N to be big like 10^4. So only solution at least O(N^2) can get accepted.

Intuition

Imagine we pass a horizontal line from bottom to top over the shape.
We have some active intervals on this horizontal line,
which gets updated twice for each rectangle.
In total, there are 2 * N events, and we can update our (up to N) active horizontal intervals for each update.

Algorithm

For a rectangle like rec = [1,0,3,1],
the first update is to add [1, 3] to the active set at y = 0,
and the second update is to remove [1, 3] at y = 1.
Note that adding and removing respects multiplicity -
if we also added [0, 2] at y = 0, then removing [1, 3] at y = 1 will still leave us with [0, 2] active.

This gives us a plan:
create these two events for each rectangle,
then process all the events in sorted order of y.
The issue now is deciding how to process the events add(x1, x2) and remove(x1, x2)
such that we are able to query() the total horizontal length of our active intervals.

We can use the fact that our remove(...) operation will always be on an interval that was previously added.
Let's store all the (x1, x2) intervals in sorted order.
Then, we can query() in linear time using a technique similar to a classic LeetCode problem, Merge Intervals.
*/
class Solution {
private:
    int mod = 1e9 + 7;

public:
    int rectangleArea(vector<vector<int> > &rectangles) {
        unordered_set<int> xValues;
        for (vector<int> &rec: rectangles) {
            xValues.insert(rec[0]);
            xValues.insert(rec[2]);
        }
        // x is vector from relative order number on x-coordinate to the actual xValue
        vector<int> x(xValues.begin(), xValues.end());
        sort(x.begin(), x.end());
        // x_i from xValue to relative order numbder of all points' xValue
        unordered_map<int, int> x_i;
        for (int i = 0; i < x.size(); i++) {
            x_i[x[i]] = i;
        }

        vector<vector<int> > line;
        for (vector<int> &rec: rectangles) {
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            // first event to add active x points
            line.push_back({y1, x1, x2, 1});
            // second event to remove inactive x points
            line.push_back({y2, x1, x2, -1});
        }
        sort(line.begin(), line.end());

        long long cur_y = 0, cur_x_sum = 0, result = 0;
        // count calculate which x point is still valid right now
        vector<int> count(x.size(), 0);
        for (vector<int> &l: line) {
            long long y = l[0], x1 = l[1], x2 = l[2], sig = l[3];
            result = (result + (y - cur_y) * cur_x_sum) % mod;
            cur_y = y;

            for (int i = x_i[x1]; i < x_i[x2]; i++) {
                count[i] += sig;
            }
            /*
            * One thing needs pay attention is the calculation of count[i]:
            * given we encounter a new segment [x1, x2] the algorithm only consider the points in [x1, x2),
            * means we never deal with the end point,
            * then when check if a segment is covered or not,
            * we always check the start point : if (count[i] > 0) cur_x_sum += x[i + 1] - x[i];
            * This is how the magic happens :)
            */
            cur_x_sum = 0;
            for (int i = 0; i < x.size(); i++) {
                if (count[i] > 0) {
                    // count[i] > 0 means from x[i] to x[i + 1] there is still valid rectangle area
                    cur_x_sum += x[i + 1] - x[i];
                }
            }
        }
        return result;
    }
};