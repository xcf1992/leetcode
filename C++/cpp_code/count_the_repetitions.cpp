/*
466. Count The Repetitions

Define S = [s,n] as the string S which consists of n connected strings s.
For example, ["abc", 3] ="abcabcabc".

On the other hand, we define that string s1 can be obtained from string s2
if we can remove some characters from s2 such that it becomes s1.
For example, “abc” can be obtained from “abdbec” based on our definition,
but it can not be obtained from “acbbe”.

You are given two non-empty strings s1 and s2 (each at most 100 characters long)
and two integers 0 ≤ n1 ≤ 106 and 1 ≤ n2 ≤ 106. Now consider the strings S1 and S2,
where S1=[s1,n1] and S2=[s2,n2].
Find the maximum integer M such that [S2,M] can be obtained from S1.

Example:
Input:
s1="acb", n1=4
s2="ab", n2=2
Return:
2
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
#include <climits>
#include <map>
#include <numeric>
using namespace std;
/*
Fact:
If s2 repeats in S1 R times, then S2 must repeats in S1 R / n2 times.
Conclusion:
We can simply count the repetition of s2 and then divide the count by n2.

How to denote repetition:
We need to scan s1 n1 times. Denote each scanning of s1 as an s1 segment.
After each scanning of i-th s1 segment, we will have

The accumulative count of s2 repeated in this s1 segment.
A nextIndex that s2[nextIndex] is the first letter you'll be looking for in the next s1 segment.
Suppose s1="abc", s2="bac", nextIndex will be 1; s1="abca", s2="bac", nextIndex will be 2

It is the nextIndex that is the denotation of the repetitive pattern.

Example:

Input:
s1="abacb", n1=6
s2="bcaa", n2=1

Return:
3
                    0 1    2 3 0      1    2 3 0      1    2 3 0
S1 --------------> abacb | abacb | abacb | abacb | abacb | abacb

repeatCount ----->    0  |   1   |   1   |   2   |   2   |   3

Increment of
repeatCount     ->    0  |   1   |   0   |   1   |   0   |   1

nextIndex ------->    2  |   1   |   2   |   1   |   2   |   1
                                    ^
                                    |
repetitive pattern found here (we've met 2 before)!
The pattern repeated 3 times
The nextIndex has s2.size() possible values,
ranging from 0 to s2.size() - 1.
Due to PigeonHole principle,
you must find two same nextIndex after scanning s2.size() + 1 s1 segments.

Once you meet a nextIndex you've met before,
you'll know that the following nextIndexs and increments of repeatCount will repeat a pattern.

So let's separate the s1 segments into 3 parts:
the prefix part before repetitive pattern
the repetitive part
the suffix part after repetitive pattern (incomplete repetitive pattern remnant)
All you have to do is add up the repeat counts of the 3 parts.
*/
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int l1 = s1.size();
        if (l1 == 0 or n1 == 0) {
            return 0;
        }
        int l2 = s2.size();

        vector<int> nextIndexr(l2 + 1, 0);  // nextIndex at start of each s1 block
        vector<int> countr(l2 + 1, 0);      // count of repititions till the present s1 block
        int nextIndex = 0;
        int count = 0;
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < l1; j++) {
                if (s1[j] == s2[nextIndex]) {
                    nextIndex += 1;
                }
                if (nextIndex == s2.size()) {
                    nextIndex = 0;
                    count += 1;
                }
            }

            countr[i] = count;
            nextIndexr[i] = nextIndex;
            for (int k = 0; k < i; k++)
                if (nextIndexr[k] == nextIndex) {
                    int prev_count = countr[k];  // count from [0, k]
                    int pattern_count = (countr[i] - countr[k]) * ((n1 - 1 - k) / (i - k));
                    int remain_count = countr[k + (n1 - 1 - k) % (i - k)] - countr[k];
                    return (prev_count + pattern_count + remain_count) / n2;
                }
        }
        return countr[n1 - 1] / n2;
    }
};