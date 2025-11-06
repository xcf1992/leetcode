/*
 780. Reaching Points
 A move consists of taking a point (x, y) and transforming it to either (x, x+y) or (x+y, y).

 Given a starting point (sx, sy) and a target point (tx, ty),
 return True if and only if a sequence of moves exists to transform the point (sx, sy) to (tx, ty).
 Otherwise, return False.

 Examples:
 Input: sx = 1, sy = 1, tx = 3, ty = 5
 Output: True
 Explanation:
 One series of moves that transforms the starting point to the target is:
 (1, 1) -> (1, 2)
 (1, 2) -> (3, 2)
 (3, 2) -> (3, 5)

 Input: sx = 1, sy = 1, tx = 2, ty = 2
 Output: False

 Input: sx = 1, sy = 1, tx = 1, ty = 1
 Output: True

 Note:

 sx, sy, tx, ty will all be integers in the range [1, 10^9].
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
 Basic idea:
 If we start from sx,sy, it will be hard to find tx, ty.
 If we start from tx,ty, we can find only one path to go back to sx, sy.
 I cut down one by one at first and I got TLE.
 So I came up with remainder.

 First line:
 if 2 target points are still bigger than 2 starting point, we reduce target points.
 Second line:
 check if we reduce target points to (x, y+kx) or (x+ky, y)

 Time complexity
 I will say O(logN) where N = max(tx,ty).

 Say tx > ty. We know that the next parent operations will be to subtract ty from tx,
 until such time that tx = tx % ty.
 When both tx > ty and ty > sy, we can perform all these parent operations in one step,
 replacing while tx > ty: tx -= ty with tx %= ty.

Otherwise, if say tx > ty and ty <= sy,
then we know ty will not be changing (it can only decrease).
Thus, only tx will change, and it can only change by subtracting by ty.
Hence, (tx - sx) % ty == 0 is a necessary and sufficient condition for the problem's answer to be True.

The analysis above was for the case tx > ty, but the case ty > tx is similar.
When tx == ty, no more moves can be made.
*/
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (sx < tx and sy < ty) {
            if (tx < ty) {
                ty %= tx;
            } else {
                tx %= ty;
            }
        }
        return (sx == tx and sy <= ty and (ty - sy) % sx == 0) or (sy == ty and sx <= tx and (tx - sx) % sy == 0);
    }
};

/*
Every parent point (x, y) has two children, (x, x+y) and (x+y, y).
However, every point (x, y) only has one parent candidate (x-y, y) if x >= y,
else (x, y-x). This is because we never have points with negative coordinates.
*/
class Solution1 {
    // TLE
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx >= sx and ty >= sy) {
            if (tx == sx and ty == sy) {
                return true;
            }
            if (tx > ty) {
                tx = tx - ty;
            } else {
                ty = ty - tx;
            }
        }
        return false;
    }
};