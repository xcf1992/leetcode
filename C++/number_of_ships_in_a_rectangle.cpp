/*
1274. Number of Ships in a Rectangle
https://leetcode.com/problems/number-of-ships-in-a-rectangle/

(This problem is an interactive problem.)
On the sea represented by a cartesian plane,
each ship is located at an integer point,
and each integer point may contain at most 1 ship.

You have a function Sea.hasShips(topRight, bottomLeft)
which takes two points as arguments and returns true
if and only if there is at least one ship in the rectangle represented by the two points,
including on the boundary.

Given two points, which are the top right and bottom left corners of a rectangle,
return the number of ships present in that rectangle.
It is guaranteed that there are at most 10 ships in that rectangle.

Submissions making more than 400 calls to hasShips will be judged Wrong Answer.
Also, any solutions that attempt to circumvent the judge will result in disqualification.

Example :
Input:
ships = [[1,1],[2,2],[3,3],[5,5]], topRight = [4,4], bottomLeft = [0,0]
Output: 3
Explanation: From [0,0] to [4,4] we can count 3 ships within the range.

Constraints:
On the input ships is only given to initialize the map internally.
You must solve this problem "blindfolded".
In other words, you must find the answer using the given hasShips API,
without knowing the ships position.
0 <= bottomLeft[0] <= topRight[0] <= 1000
0 <= bottomLeft[1] <= topRight[1] <= 1000
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
#include "extra_data_types.hpp"
using namespace std;

// This is Sea's API interface.
// You should not implement it, or speculate about its implementation
class Sea {
public:
    bool hasShips(vector<int> topRight, vector<int> bottomLeft);
};
/*
if current retangle has no ship, we can return 0, or if the retangle is a point, we can return hasShips result.
otherwise, we split the retangle to 4 pieces:
_______________
|  4   |   2  |
|______|______|
|  3   |   1  |
|______|______|
and count each pieces' ships, the result is sum of 4 pieces results.
*/
class Solution {
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        if (topRight[0] < bottomLeft[0] or topRight[1] < bottomLeft[1]) {
            return 0;
        }

        bool hasShip = sea.hasShips(topRight, bottomLeft);
        if (!hasShip) {
            return 0;
        }
        if (topRight[0] == bottomLeft[0] and topRight[1] == bottomLeft[1]) {
            return hasShip ? 1 : 0;
        }

        return countShips(sea, {topRight[0], (topRight[1] + bottomLeft[1]) / 2}, {(topRight[0] + bottomLeft[0]) / 2 + 1, bottomLeft[1]})
             + countShips(sea, topRight, {(topRight[0] + bottomLeft[0]) / 2 + 1, (topRight[1] + bottomLeft[1]) / 2 + 1})
             + countShips(sea, {(topRight[0] + bottomLeft[0]) / 2, (topRight[1] + bottomLeft[1]) / 2}, bottomLeft)
             + countShips(sea, {(topRight[0] + bottomLeft[0]) / 2, topRight[1]}, {bottomLeft[0], (topRight[1] + bottomLeft[1]) / 2 + 1});
    }
};
