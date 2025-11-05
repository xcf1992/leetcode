/*
984. String Without AAA or BBB
https://leetcode.com/problems/string-without-aaa-or-bbb/

Given two integers A and B, return any string S such that:
S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
The substring 'aaa' does not occur in S;
The substring 'bbb' does not occur in S.

Example 1:
Input: A = 1, B = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.

Example 2:
Input: A = 4, B = 1
Output: "aabaa"

Note:
0 <= A <= 100
0 <= B <= 100
It is guaranteed such an S exists for the given A and B.
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

class Solution {
public:
    string strWithout3a3b(int A, int B) {
        string result = "";
        while (A > 0 or B
        >
        0
        )
        {
            bool writeA = false;
            int n = result.size();
            if (n >= 2 and result[n - 1]
            ==
            result[n - 2]
            )
            {
                if (result[n - 1] == 'b') {
                    writeA = true;
                }
            }
            else
            {
                if (A >= B) {
                    writeA = A > 0;
                }
            }

            if (writeA) {
                result.push_back('a');
                A -= 1;
            } else {
                result.push_back('b');
                B -= 1;
            }
        }
        return result;
    }
};

class Solution1 {
public:
    string strWithout3a3b(int A, int B) {
        string result = "";
        while (A > 0 or B
        >
        0
        )
        {
            if (A > B) {
                if (result.back() == 'a') {
                    if (B > 0) {
                        result.push_back('b');
                        B -= 1;
                    }
                    if (A > 0) {
                        result.push_back('a');
                        A -= 1;
                        if (A > 0) {
                            result.push_back('a');
                            A -= 1;
                        }
                    }
                } else {
                    if (A > 0) {
                        result.push_back('a');
                        A -= 1;
                        if (A > 0) {
                            result.push_back('a');
                            A -= 1;
                        }
                    }
                    if (B > 0) {
                        result.push_back('b');
                        B -= 1;
                    }
                }
            } else {
                if (result.back() == 'b') {
                    if (A > 0) {
                        result.push_back('a');
                        A -= 1;
                    }
                    if (B > 0) {
                        result.push_back('b');
                        B -= 1;
                        if (B > 0) {
                            result.push_back('b');
                            B -= 1;
                        }
                    }
                } else {
                    if (B > 0) {
                        result.push_back('b');
                        B -= 1;
                        if (B > 0) {
                            result.push_back('b');
                            B -= 1;
                        }
                    }
                    if (A > 0) {
                        result.push_back('a');
                        A -= 1;
                    }
                }
            }
        }
        return result;
    }
};