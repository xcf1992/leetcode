/*
 In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.
 
 Example:
 
 Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
 Output: True
 Explanation:
 We can transform start to end following these steps:
 RXXLRXRXL ->
 XRXLRXRXL ->
 XRLXRXRXL ->
 XRLXXRRXL ->
 XRLXXRRLX
 Note:
 
 1 <= len(start) = len(end) <= 10000.
 Both start and end will only consist of characters in {'L', 'R', 'X'}.
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
 The solution is simple and similar to others, but more detailed explanation is needed.
 
 In fact, "R" can move to the right until it is blocked by "L" while "L" can move to the left until it is blocked by "R". So one solution is to remove all "X" in the two strings and check if they are identical.
 
 Instead directly dealing with the strings, we may also count the number of "L" and "R" as follows. There are several principles during the loop:
 
 the value of l could be zero and negative, but not positive. This is becasue "L" could move to the left, so "L" may appear earlier in end than that in start. So once find l > 0, we may return false;
 the value of r could be zero and positive, but not negative. The reasons are similar to the one above. So once findr < 0, we may return false;
 When l < 0, r must be zero. This is because when l < 0, it means that one "L" appears earlier in end, so we need the next character in start should immediately be "L". But if now r>0, it actually means that the next character in start is "R" rather than "L".
 When r > 0, l must be zero. Reasons are similar.
 
 so left and right means extra L or R in the string start than end.
 */
class Solution {
public:
    bool canTransform(string start, string end) {
        int left = 0;
        int right = 0;
        for (int i = 0; i < start.size(); i++) {
            if (start[i] == 'L') {
                left += 1;
            }
            if (start[i] == 'R') {
                right += 1;
            }
            if (end[i] == 'L') {
                left -= 1;
            }
            if (end[i] == 'R') {
                right -= 1;
            }
            
            if (left > 0 || right < 0 || (right > 0 && left != 0) || (left > 0 && right != 0)) {
                return false;
            }
        }
        return left == 0 && right == 0;
    }
};
