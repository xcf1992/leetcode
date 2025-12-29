/*
https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-i/description/
3199. Count Triplets with Even XOR Set Bits I
Easy
Topics
conpanies icon
Companies
Hint
Given three integer arrays a, b, and c, return the number of triplets (a[i], b[j], c[k]), such that the bitwise XOR of
the elements of each triplet has an even number of set bits.


Example 1:

Input: a = [1], b = [2], c = [3]

Output: 1

Explanation:

The only triplet is (a[0], b[0], c[0]) and their XOR is: 1 XOR 2 XOR 3 = 002.

Example 2:

Input: a = [1,1], b = [2,3], c = [1,5]

Output: 4

Explanation:

Consider these four triplets:

(a[0], b[1], c[0]): 1 XOR 3 XOR 1 = 0112
(a[1], b[1], c[0]): 1 XOR 3 XOR 1 = 0112
(a[0], b[0], c[1]): 1 XOR 2 XOR 5 = 1102
(a[1], b[0], c[1]): 1 XOR 2 XOR 5 = 1102


Constraints:

1 <= a.length, b.length, c.length <= 100
0 <= a[i], b[i], c[i] <= 100
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {
        int rst = 0;
        for (int x : a) {
            for (int y : b) {
                for (int z : c) {
                    if (__builtin_popcount(x ^ y ^ z) % 2 == 0) {
                        rst += 1;
                    }
                }
            }
        }
        return rst;
    }
};