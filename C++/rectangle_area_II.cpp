/*
 We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.
 
 Find the total area covered by all rectangles in the plane.  Since the answer may be too large, return it modulo 10^9 + 7.
 
 
 
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
using namespace std;

/*
 Explanation:
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
 */
class Solution {
private:
    int mod = 1e9 + 7;
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        return 0;
    }
};
