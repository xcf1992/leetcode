/*
1363. Largest Multiple of Three
https://leetcode.com/problems/largest-multiple-of-three/

Given an integer array of digits,
return the largest multiple of three that can be formed by concatenating some of the given digits in any order.

Since the answer may not fit in an integer data type,
return the answer as a string.

If there is no answer return an empty string.

Example 1:
Input: digits = [8,1,9]
Output: "981"

Example 2:
Input: digits = [8,6,7,1,0]
Output: "8760"

Example 3:
Input: digits = [1]
Output: ""

Example 4:
Input: digits = [0,0,0,0,0,0]
Output: "0"

Constraints:
1 <= digits.length <= 10^4
0 <= digits[i] <= 9
The returning answer must not contain unnecessary leading zeros.
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
#include <map>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;
/*
Calculate the sum of digits total = sum(A)
If total % 3 == 0, we got it directly
If total % 3 == 1 and we have one of 1,4,7 in A:
we try to remove one digit of 1,4,7
If total % 3 == 2 and we have one of 2,5,8 in A:
we try to remove one digit of 2,5,8
If total % 3 == 2:
we try to remove two digits of 1,4,7
If total % 3 == 1:
we try to remove two digits of 2,5,8
Submit
*/
class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        vector<int> cnt(10);
        int s = 0;
        for(int i : digits) {
            cnt[i]++;
            s += i;
        }

        if (s % 3 == 2 and cnt[2]) {
            cnt[2]--, s-=2;
        }
        if (s % 3 == 2 and cnt[5]) {
            cnt[5]--, s-=5;
        }
        if (s % 3 == 2 && cnt[8]) {
            cnt[8]--, s-=8;
        }

        vector<int> nums = {1,4,7,2,5,8}; // trying to lose as small values as possible
        for (int i : nums) {
            while (s % 3 > 0 && cnt[i]) {
                cnt[i]--, s-=i;
            }
        }

        if (s == 0) {
            return cnt[0] ? "0" : "";
        }

        string res;
        for (int i = 9; i >= 0; i--) {
            while (cnt[i]) {
                cnt[i]--, res+='0'+i;
            }
        }
        return res;
    }
};
