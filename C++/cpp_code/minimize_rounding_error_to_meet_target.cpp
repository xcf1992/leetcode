/*
1058. Minimize Rounding Error to Meet Target

Given an array of prices [p1,p2...,pn] and a target,
round each price pi to Roundi(pi) so that the rounded array [Round1(p1),Round2(p2)...,Roundn(pn)] sums to the given target.
Each operation Roundi(pi) could be either Floor(pi) or Ceil(pi).

Return the string "-1"
if the rounded array is impossible to sum to target.
Otherwise, return the smallest rounding error,
which is defined as Σ |Roundi(pi) - (pi)| for i from 1 to n, as a string with three places after the decimal.

Example 1:
Input: prices = ["0.700","2.800","4.900"], target = 8
Output: "1.000"
Explanation:
Use Floor, Ceil and Ceil operations to get (0.7 - 0) + (3 - 2.8) + (5 - 4.9) = 0.7 + 0.2 + 0.1 = 1.0 .

Example 2:
Input: prices = ["1.500","2.500","3.500"], target = 10
Output: "-1"
Explanation:
It is impossible to meet the target.

Note:
1 <= prices.length <= 500.
Each string of prices prices[i] represents a real number which is between 0 and 1000 and has exactly 3 decimal places.
target is between 0 and 1000000.
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
public:
    string minimizeError(vector<string> &prices, int target) {
        double floorS = 0.0;
        double ceilS = 0.0;
        int integer = 0;
        priority_queue<double, vector<double>, greater<double> > floorErr, ceilErr;
        for (string &p: prices) {
            double price = stod(p);
            floorS += floor(price);
            ceilS += ceil(price);
            if (price == floor(price)) {
                integer += 1;
                continue;
            }
            floorErr.push(price - floor(price));
            ceilErr.push(ceil(price) - price);
        }

        if (target > ceilS or target<floorS
        )
        {
            return "-1";
        }

        int floorCount = (int) ceilS - target;
        int ceilCount = prices.size() - integer - floorCount;
        double result = 0.0;
        while (floorCount > 0) {
            result += floorErr.top();
            floorErr.pop();
            floorCount -= 1;
        }
        while (ceilCount > 0) {
            result += ceilErr.top();
            ceilErr.pop();
            ceilCount -= 1;
        }
        string resultStr = to_string(result);
        return resultStr.substr(0, resultStr.size() - 3); // erase last 3 zeros
    }
};