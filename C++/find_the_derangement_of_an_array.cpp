/*
 In combinatorial mathematics, a derangement is a permutation of the elements of a set, such that no element appears in its original position.
 
 There's originally an array consisting of n integers from 1 to n in ascending order, you need to find the number of derangement it can generate.
 
 Also, since the answer may be very large, you should return the output mod 10^9 + 7.
 
 Example 1:
 Input: 3
 Output: 2
 Explanation: The original array is [1,2,3]. The two derangements are [2,3,1] and [3,1,2].
 Note:
 n is in the range of [1, 10^6].
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
    int findDerangement(int n) {
        if (n == 1) {
            return 0;
        }
        if (n == 2) {
            return 1;
        }
        unsigned long long minus2 = 0;
        unsigned long long minus1 = 1;
        unsigned long long result = 1;
        for (int i = 3; i <= n; i++) {
            result = (i - 1) * (minus1 + minus2) % 1000000007;
            minus2 = minus1;
            minus1 = result;
        }
        return result;
    }
};
