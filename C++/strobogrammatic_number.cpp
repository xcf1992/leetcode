/*
246. Strobogrammatic Number
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

Example 1:

Input:  "69"
Output: true
Example 2:

Input:  "88"
Output: true
Example 3:

Input:  "962"
Output: false
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
using namespace std;

class Solution {
private:
    unordered_map<char, char> strobogrammatic{{'9', '6'}, {'1', '1'}, {'8', '8'}, {'6', '9'}, {'0', '0'}};
public:
    bool isStrobogrammatic(string num) {
        int left = 0;
        int right = num.size() - 1;
        while (left <= right) {
            if (strobogrammatic.find(num[left]) == strobogrammatic.end() || strobogrammatic[num[left]] != num[right]) {
                return false;
            }
            left += 1;
            right -= 1;
        }
        return true;
    }
};
