/*
1118. Number of Days in a Month
Given a year Y and a month M, return how many days there are in that month.



Example 1:

Input: Y = 1992, M = 7
Output: 31
Example 2:

Input: Y = 2000, M = 2
Output: 29
Example 3:

Input: Y = 1900, M = 2
Output: 28


Note:

1583 <= Y <= 2100
1 <= M <= 12
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

class Solution {
public:
    int numberOfDays(int Y, int M) {
        if (M == 2) {
            return Y % 4 == 0 and (Y % 100 != 0 or Y % 400 == 0) ? 29 : 28;
        }
        if (M < 8) {
            return M % 2 == 0 ? 30 : 31;
        }
        return M % 2 == 1 ? 30 : 31;
    }
};