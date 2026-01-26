/*
https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/description/
3047. Find the Largest Area of Square Inside Two Rectangles

There exist n rectangles in a 2D plane with edges parallel to the x and y axis. You are given two 2D integer arrays
bottomLeft and topRight where bottomLeft[i] = [a_i, b_i] and topRight[i] = [c_i, d_i] represent the bottom-left and
top-right coordinates of the ith rectangle, respectively.

You need to find the maximum area of a square that can fit inside the intersecting region of at least two rectangles.
Return 0 if such a square does not exist.



Example 1:


Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]

Output: 1

Explanation:

A square with side length 1 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting
region of rectangles 1 and 2. Hence the maximum area is 1. It can be shown that a square with a greater side length can
not fit inside any intersecting region of two rectangles.

Example 2:


Input: bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]

Output: 4

Explanation:

A square with side length 2 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting
region of rectangles 1 and 2. Hence the maximum area is 2 * 2 = 4. It can be shown that a square with a greater side
length can not fit inside any intersecting region of two rectangles.

Example 3:


Input: bottomLeft = [[1,1],[2,2],[1,2]], topRight = [[3,3],[4,4],[3,4]]

Output: 1

Explanation:

A square with side length 1 can fit inside the intersecting region of any two rectangles. Also, no larger square can, so
the maximum area is 1. Note that the region can be formed by the intersection of more than 2 rectangles.

Example 4:


Input: bottomLeft = [[1,1],[3,3],[3,1]], topRight = [[2,2],[4,4],[4,2]]

Output: 0

Explanation:

No pair of rectangles intersect, hence, the answer is 0.



Constraints:

n == bottomLeft.length == topRight.length
2 <= n <= 103
bottomLeft[i].length == topRight[i].length == 2
1 <= bottomLeft[i][0], bottomLeft[i][1] <= 107
1 <= topRight[i][0], topRight[i][1] <= 107
bottomLeft[i][0] < topRight[i][0]
bottomLeft[i][1] < topRight[i][1]
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
#include <climits>
#include <map>
#include <numeric>
using namespace std;
/*
https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/solutions/7500723/draft-by-la_castille-ufww/
Any square that lies inside the intersection of at least two rectangles must be fully contained within the overlapping
region of at least two rectangles (see 223. Rectangle Area).

Therefore, the only candidates for the largest square are the intersections formed by every possible pair of rectangles.

This algorithm requires at least O(n
2
 ) runtime.


The challenging part is finding that square.

Procedure
First, Let's isolate two pairs of rectangle and determine the boundaries of the overlapping rectangle.

Minimum x

Maximum x

Minimum y

Maximum y

Then find the length of the smaller dimension of the overlapping rectangle:


The Largest Square:
Finally, if we take the square of the smaller length, we can see the largest square contained within this specific pair:


Repeat this process for all pairs of rectangles, and track the maximum square side found.
The final answer is the square of the maximum side length.


Non-overlapping pairs
If a pair of rectangles does not overlap, at least one of the computed dimensions becomes zero or negative.

This directly indicates that no valid square can be formed from this pair. Since such values cannot increase the maximum
side length, they are naturally ignored by the process.

To slightly optimize the runtime, we can entirely ignore non-overlapping pair of rectangles by checking if the
rectangular side length/s are negative.

The code should beat at least 80%−90% of the users (depending on the language).
Try to optimize it further if you like.

Time Complexity: O(n
2
 )
Space Complexity: O(1)
*/
class Solution {
public:
    using ll = long long;

    ll largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        ll square_len = 0;
        int n = bottomLeft.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ll min_x = max(bottomLeft[i][0], bottomLeft[j][0]);
                ll max_x = min(topRight[i][0], topRight[j][0]);
                ll min_y = max(bottomLeft[i][1], bottomLeft[j][1]);
                ll max_y = min(topRight[i][1], topRight[j][1]);
                if (min_x < max_x && min_y < max_y) {
                    square_len = max(square_len, min(max_x - min_x, max_y - min_y));
                }
            }
        }
        return square_len * square_len;
    }
};
