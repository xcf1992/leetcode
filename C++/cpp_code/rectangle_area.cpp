/*
https://leetcode.com/problems/rectangle-area/description/
223. Rectangle Area
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Rectangle Area

Example:

Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
Output: 45
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
using namespace std;

/*
find the overlap in x and y accordingly;
if there is overlap in y, then it looks like below, so we find min(ax2, bx2) and max(ax1, bx1)
ax1--------ax2
      bx1--------bx2
same for the overlap for y
*/
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int area = (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1);
        // max(0, overlapRightSide-overlapLeftSide);
        int overlap_w = max(0, min(bx2, ax2) - max(bx1, ax1));
        // same but up - down
        int overlap_h = max(0, min(by2, ay2) - max(by1, ay1));
        return area - overlap_w * overlap_h;
    }
};