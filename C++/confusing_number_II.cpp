/*
1088. Confusing Number II

We can rotate digits by 180 degrees to form new digits.
When 0, 1, 6, 8, 9 are rotated 180 degrees,
they become 0, 1, 9, 8, 6 respectively.
When 2, 3, 4, 5 and 7 are rotated 180 degrees,
they become invalid.

A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.
(Note that the rotated number can be greater than the original number.)

Given a positive integer N, return the number of confusing numbers between 1 and N inclusive.

Example 1:

Input: 20
Output: 6
Explanation:
The confusing numbers are [6,9,10,16,18,19].
6 converts to 9.
9 converts to 6.
10 converts to 01 which is just 1.
16 converts to 91.
18 converts to 81.
19 converts to 61.
Example 2:

Input: 100
Output: 19
Explanation:
The confusing numbers are [6,9,10,16,18,19,60,61,66,68,80,81,86,89,90,91,98,99,100].


Note:

1 <= N <= 10^9
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
   const vector<int> rotate = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
   const vector<int> valid = {0, 1, 6, 8, 9};

    bool isConfusing(int num) {
        string numStr = to_string(num);
        int n = numStr.size();
        for (int left = 0, right = n - 1; left <= right; ++left, --right) {
            if (numStr[left] - '0' != rotate[numStr[right] - '0']) {
                return true;
            }
        }
        return false;
    }

    void dfs(long long cur, int N, int& result) {
        if (cur > N) {
            return;
        }

        if (isConfusing(cur)) {
            result += 1;
        }

        for (int d : valid) {
            dfs(cur * 10 + d, N, result);
        }
   }
public:
    int confusingNumberII(int N) {
        int result = 0;
        int cur = 0;
        for (int d : valid) {
            if (d != 0) {
                dfs(d, N, result);
            }
        }
        return result;
    }
};
