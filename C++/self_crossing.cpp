/*
 335. Self Crossing

 You are given an array x of n positive numbers.
 You start at point (0,0) and moves x[0] metres to the north,
 then x[1] metres to the west, x[2] metres to the south,
 x[3] metres to the east and so on. In other words,
 after each move your direction changes counter-clockwise.

 Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.

 Example 1:

 Input: [2,1,1,2]

 ?????
 ?   ?
 ???????>
 ?

 Input: true
 Explanation: self crossing
 Example 2:

 Input: [1,2,3,4]

 ????????
 ?      ?
 ?
 ?
 ?????????????>

 Output: false
 Explanation: not self crossing
 Example 3:

 Input: [1,1,1,1]

 ?????
 ?   ?
 ?????>

 Output: true
 Explanation: self crossing
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

// Categorize the self-crossing scenarios, there are 3 of them:
// 1. Fourth line crosses first line and works for fifth line crosses second line and so on...
// 2. Fifth line meets first line and works for the lines after
// 3. Sixth line crosses first line and works for the lines after
class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        int n = x.size();
        if (n <= 3) {
            return 0;
        }

        for (int i = 3; i < n; i++) {
            //Fourth line crosses first line and onward // gap 3
            if (x[i] >= x[i - 2] and x[i - 1] <= x[i - 3]) {
                return true;
            }

            // Fifth line meets first line and onward // gap 4
            if (i >= 4 and x[i - 1] == x[i - 3] and x[i] + x[i - 4] >= x[i - 2]) {
                return true;
            }

            // Sixth line crosses first line and works for the lines after // gap 5
            if (i >= 5 and x[i - 2] >= x[i - 4] and x[i] + x[i - 4] >= x[i - 2] and x[i - 1] <= x[i - 3] and x[i - 1] + x[i - 5] >= x[i - 3]) {
                return true;
            }
        }
        return false;
    }
};
