/*
1812. Determine Color of a Chessboard Square
https://leetcode.com/problems/determine-color-of-a-chessboard-square/

You are given coordinates,
a string that represents the coordinates of a square of the chessboard.
Below is a chessboard for your reference.

Return true if the square is white, and false if the square is black.
The coordinate will always represent a valid chessboard square.
The coordinate will always have the letter first, and the number second.

Example 1:
Input: coordinates = "a1"
Output: false
Explanation: From the chessboard above, the square with coordinates "a1" is black, so return false.
Example 2:
Input: coordinates = "h3"
Output: true
Explanation: From the chessboard above, the square with coordinates "h3" is white, so return true.
Example 3:
Input: coordinates = "c7"
Output: false

Constraints:
coordinates.length == 2
'a' <= coordinates[0] <= 'h'
'1' <= coordinates[1] <= '8'
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

class Solution {
public:
    bool squareIsWhite(string a) {
        return a[0] % 2 != a[1] % 2;
    }
};