/*
 Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.
 
 Example 1:
 Input: 5
 Output: True
 Explanation: 1 * 1 + 2 * 2 = 5
 Example 2:
 Input: 3
 Output: False
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
#include <set>
using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        int left = 0;
        int right = sqrt(c);
        while (left <= right) {
            int val = left * left + right * right;
            if (val == c) {
                return true;
            }
            
            if (val < c) {
                left += 1;
            }
            else {
                right -= 1;
            }
        }
        return false;
    }
};
