/*
137. Single Number II
https://leetcode.com/problems/single-number-ii/

Given a non-empty array of integers,
every element appears three times except for one,
which appears exactly once.
Find that single one.

Note:
Your algorithm should have a linear runtime complexity.
Could you implement it without using extra memory?

Example 1:
Input: [2,2,3,2]
Output: 3

Example 2:
Input: [0,1,0,1,0,1,99]
Output: 99
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;
/*
https://cloud.tencent.com/developer/article/1131945

first appearence:
add num to seen_once
don't add to seen_twice because of presence in seen_once

second appearance:
remove num from seen_once
add num to seen_twice

third appearance:
don't add to seen_once because of presence in seen_twice
remove num from seen_twice
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int seenOnce = 0;
        int seenTwice = 0;
        for (int num : nums) {
            seenOnce = ~seenTwice & (seenOnce ^ num);
            seenTwice = ~seenOnce & (seenTwice ^ num);
        }
        return seenOnce;
    }
};

class Solution1 {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }

        vector <int> bits(32, 0);
        for (int num : nums) {
            for (int j = 0; j < 32; j++) {
                bits[j] += (num >> j) & 1;
            }
        }

        int result = 0;
        for (int i = 0; i < 32; ++i) {
            int digit = bits[i] % 3;
            result |= (digit << i);
        }
        return result;
    }
};
