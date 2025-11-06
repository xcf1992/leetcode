/*
481. Magical String

A magical string S consists of only '1' and '2' and obeys the following rules:

The string S is magical because concatenating the number of contiguous occurrences of characters '1' and '2'
generates the string S itself.

The first few elements of string S is the following: S = "1221121221221121122……"

If we group the consecutive '1's and '2's in S, it will be:

1 22 11 2 1 22 1 22 11 2 11 22 ......

and the occurrences of '1's or '2's in each group are:

1 2 2 1 1 2 1 2 2 1 2 2 ......

You can see that the occurrence sequence above is the S itself.

Given an integer N as input,
return the number of '1's in the first N number in the magical string S.

Note: N will not exceed 100,000.

Example 1:
Input: 6
Output: 3
Explanation: The first 6 elements of magical string S is "12211" and it contains three 1's, so return 3.
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
public:
    int magicalString(int n) {
        string magic = "122";
        int cur = 2;
        while (magic.size() < n) {
            magic.append(magic[cur] - '0',
                         magic.back() ^ 3);  // append (size_t n, char c); 10 ^ 11 -> 01, 01 ^ 11 -> 10
            cur += 1;
        }
        return count(magic.begin(), magic.begin() + n, '1');
    }
};

class Solution1 {
public:
    int magicalString(int n) {
        string s1 = "122";
        string s2 = "12";

        while (s1.size() < n) {
            s2.push_back(s1[s2.size()]);
            if (s2.back() == '1') {
                s1 += s1.back() == '1' ? '2' : '1';
            } else if (s2.back() == '2') {
                s1 += s1.back() == '1' ? "22" : "11";
            }
        }

        string magicalString = s1.substr(0, n);
        return count(magicalString.begin(), magicalString.end(), '1');
    }
};