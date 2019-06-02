/*
402. Remove K Digits
 Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.
 
 Note:
 The length of num is less than 10002 and will be ≥ k.
 The given num does not contain any leading zero.
 Example 1:
 
 Input: num = "1432219", k = 3
 Output: "1219"
 Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
 Example 2:
 
 Input: num = "10200", k = 1
 Output: "200"
 Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
 Example 3:
 
 Input: num = "10", k = 2
 Output: "0"
 Explanation: Remove all the digits from the number and it is left with nothing which is 0.
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

// k keeps track of how many characters we can remove
// if the previous character in stk is larger than the current one
// then removing it will get a smaller number
// but we can only do so when k is larger than 0
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (k >= n) {
            return "0";
        }
        
        string result = "";
        for (int i = 0; i < n; ++i) {
            while (!result.empty() and num[i] < result.back() and k > 0) {
                result.pop_back();
                k -= 1;
            }
            if (!result.empty() or num[i] != '0') {
                result.push_back(num[i]);
            }
        }
        
        while (!result.empty() and k > 0) {
            result.pop_back();
            k -= 1;
        }
        return result == "" ? "0" : result;
    }
};
