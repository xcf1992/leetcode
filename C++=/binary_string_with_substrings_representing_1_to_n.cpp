/*
1016. Binary String With Substrings Representing 1 To N
https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/

Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N,
return true if and only if for every integer X from 1 to N,
the binary representation of X is a substring of S.

Example 1:
Input: S = "0110", N = 3
Output: true

Example 2:
Input: S = "0110", N = 4
Output: false

Note:

1 <= S.length <= 1000
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
/*
Time Complexity
Prove I, check number of substring
Pick two indices, there are at most S^2 substrings,
so S can contains at most S^2 integers
Time complexity upper bound O(S^2)

Prove II, Check the continuous digits
Meanwhile I know the interviewer and my reader won't be satisfied,
as they want no more "cheat".
Here I have a brief demonstration to give the time complexity an acceptable upper bound.

Have a look at the number 1001 ~ 2000 and their values in binary.

1001 0b1111101001
1002 0b1111101010
1003 0b1111101011
...
1997 0b11111001101
1998 0b11111001110
1999 0b11111001111
2000 0b11111010000

The number 1001 ~ 2000 have 1000 different continuous 10 digits.
The string of length S has at most S - 9 different continuous 10 digits.
So S <= 1000, N <= 2000.

So S * 2 is a upper bound for N.
If N > S * 2, we can return false directly.

It's the same to prove with the numbers 512 ~ 1511, or even smaller range.

Time complexity upper bound O(S)

here is my explaination: S <= 1000 is len(S) <= 1000.
first, as dan39 said,only need check N/2.
so when N==2000, only need check 1000 nums.

second, because len(S) <= 1000,
so if len(S) == 1000, only can have (1000-9)=991 nums.
so N can not bigger than 991 * 2, almost 2000.

the len(S) is the topic's condition, and the condition of the N<=2000.

anther explain:
condition 1: as dan39 said,only need check N/2. so when N==2000, only need check 1000 nums.
condition 2: len(S) <= 1000, so len(S) can only have (1000-9)*2 nums
conculusion: N <= (len(S)-9) == (1000-9)*2 <= 2000, that is N <= 2000.

so why use 1000-2000 as example? it's anther problem, Mr. Lee's solution is so amazing.
because len(S) <= 1000,
if N is bigger, the nums will be less.
if N is smaller, the nums will be less.
so N = 1000, 10bit, can get the most nums.
this is beyond my think. what i think is consider if i should be a programer...
*/
class Solution {
private:
    string toBinaryString(int num) {
        if (num == 0) {
            return "0";
        }

        string result = "";
        while (num > 0) {
            result.push_back('0' + (num & 1));
            num >>= 1;
        }
        reverse(result.begin(), result.end());
        return result;
    }
public:
    bool queryString(string S, int N) {
        for (int i = N; i > N / 2; --i) {
            string bits = toBinaryString(i);
            if (S.find(bits) == string::npos) {
                return false;
            }
        }
        return true;
    }
};
