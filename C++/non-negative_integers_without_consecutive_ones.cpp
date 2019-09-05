/*
 600. Non-negative Integers without Consecutive Ones

 Given a positive integer n,
 find the number of non-negative integers less than or equal to n,
 whose binary representations do NOT contain consecutive ones.

 Example 1:
 Input: 5
 Output: 5
 Explanation:
 Here are the non-negative integers <= 5 with their corresponding binary representations:
 0 : 0
 1 : 1
 2 : 10
 3 : 11
 4 : 100
 5 : 101
 Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
 Note: 1 <= n <= 109
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

/*
 This problem can be solved using Dynamic Programming.
 Let a[i] be the number of binary strings of length i which do not contain any two consecutive 1’s and which end in 0.
 Similarly, let b[i] be the number of such strings which end in 1.
 We can append either 0 or 1 to a string ending in 0,
 but we can only append 0 to a string ending in 1.
 This yields the recurrence relation:

 a[i] = a[i - 1] + b[i - 1]
 b[i] = a[i - 1]
 The base cases of above recurrence are a[1] = b[1] = 1. The total number of strings of length i is just a[i] + b[i].
*/
class Solution {
private:
    string toBinary(int num) { // change num to its binary string, so 6 will be 0011, the most significant bit will be right-most
        string result = "";
        while (num != 0) {
            result.push_back('0' + (num & 1));
            num >>= 1;
        }
        return result;
    }
public:
    int findIntegers(int num) {
        string nStr = toBinary(num);
        int n = nStr.size();
        vector<int> end0(n, 1);
        vector<int> end1(n, 1);
        for (int i = 1; i < n; i++) {
            end0[i] = end0[i - 1] + end1[i - 1];
            end1[i] = end0[i - 1];
        }

        int result = end0[n - 1] + end1[n - 1];
        /*
         the count of valid number has n bit, some of them are bigger than num we want and we need to subtract them below
         then we subtract the solutions which is larger than num, we iterate from the MSB to LSB of num:
         if bit[i] == 1
            if bit[i + 1] == 0, there's no solutions in res that is larger than num, we go further into smaller bit and subtract.
            if bit[i + 1] == 1, we know in those res solutions it won't have any consecutive ones.
               when bit[i + 1] == 1, in one[i + 1], the i-th bit in valid solutions must be 0,
               which are all smaller than 'num', we don't need to check smaller bits and subtract, so we break the for loop.
         if bit[i] == 0
            if bit[i + 1] == 1, there's no solutions in res that is larger than num, we go further into smaller bit and subtract.
            if bit[i + 1] == 0, we know zero[i + 1] includes solutions of i-th == 0 (00***) and i-th bit == 1 (01***),
               we know the i-th bit of num is 0, so we need to subtract all the 01*** solutions
               because it is larger than num. Therefore, one[i] is subtracted from res.
        */
        for (int i = n - 2; i >= 0; i--) {
            if (nStr[i] == '1' and nStr[i + 1] == '1') {
                break;
            }
            if (nStr[i] == '0' and nStr[i + 1] == '0') {
                result -= end1[i];
            }
        }
        return result;
    }
};
