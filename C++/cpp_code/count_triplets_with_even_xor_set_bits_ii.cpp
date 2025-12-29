/*
https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-ii/description/
3215. Count Triplets with Even XOR Set Bits II

Given three integer arrays a, b, and c, return the number of triplets (a[i], b[j], c[k]), such that the bitwise XOR
between the elements of each triplet has an even number of set bits.


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

1 <= a.length, b.length, c.length <= 105
0 <= a[i], b[i], c[i] <= 109
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
private:
    vector<long long> calc_parity(vector<int>& arr) {
        vector<long long> rst(2, 0);
        for (int val : arr) {
            if ((__builtin_popcount(val) & 1) == 0) {
                rst[0] += 1;
            } else {
                rst[1] += 1;
            }
        }
        return rst;
    }

public:
    long long tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {
        vector<long long> parity_a = calc_parity(a);
        vector<long long> parity_b = calc_parity(b);
        vector<long long> parity_c = calc_parity(c);
        return parity_a[0] * parity_b[0] * parity_c[0] + parity_a[1] * parity_b[1] * parity_c[0] +
               parity_a[1] * parity_b[0] * parity_c[1] + parity_a[0] * parity_b[1] * parity_c[1];
    }
};