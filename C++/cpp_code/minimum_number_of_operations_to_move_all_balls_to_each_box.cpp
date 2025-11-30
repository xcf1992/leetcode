/*
1769. Minimum Number of Operations to Move All Balls to Each Box
https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/

You have n boxes. You are given a binary string boxes of length n,
where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

In one operation, you can move one ball from a box to an adjacent box.
Box i is adjacent to box j if abs(i - j) == 1. Note that after doing so,
there may be more than one ball in some boxes.

Return an array answer of size n,
where answer[i] is the minimum number of operations needed to move all the balls to the ith box.
Each answer[i] is calculated considering the initial state of the boxes.

Example 1:
Input: boxes = "110"
Output: [1,1,3]
Explanation: The answer for each box is as follows:
1) First box: you will have to move one ball from the second box to the first box in one operation.
2) Second box: you will have to move one ball from the first box to the second box in one operation.
3) Third box: you will have to move one ball from the first box to the third box in two operations, and move one ball
from the second box to the third box in one operation. Example 2: Input: boxes = "001011" Output: [11,8,5,4,3,4]

Constraints:
n == boxes.length
1 <= n <= 2000
boxes[i] is either '0' or '1'.
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
#include <bitset>
using namespace std;

class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.length();

        vector<int> left(n, 0);
        int count = boxes[0] - '0';
        for (int i = 1; i < n; i++) {
            left[i] = left[i - 1] + count;
            count += boxes[i] - '0';
        }

        vector<int> right(n, 0);
        count = boxes[n - 1] - '0';
        for (int i = n - 2; i >= 0; i--) {
            right[i] = right[i + 1] + count;
            count += boxes[i] - '0';
        }

        vector<int> result(n, 0);
        for (int i = 0; i < n; i++) {
            result[i] = left[i] + right[i];
        }
        return result;
    }
};
