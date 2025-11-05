/*
1643. Kth Smallest Instructions
https://leetcode.com/problems/kth-smallest-instructions/

Bob is standing at cell (0, 0),
and he wants to reach destination: (row, column).
He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.

The instructions are represented as a string, where each character is either:
'H', meaning move horizontally (go right), or
'V', meaning move vertically (go down).
Multiple instructions will lead Bob to destination.
For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.

However, Bob is very picky.
Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.

Given an integer array destination and an integer k,
return the kth lexicographically smallest instructions that will take Bob to destination.

Example 1:
Input: destination = [2,3], k = 1
Output: "HHHVV"
Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].

Example 2:
Input: destination = [2,3], k = 2
Output: "HHVHV"

Example 3:
Input: destination = [2,3], k = 3
Output: "HHVVH"

Constraints:
destination.length == 2
1 <= row, column <= 15
1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b​​​​​.
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include "extra_data_types.hpp"
using namespace std;
/*
Given destination: (row, column), we will have column H and row V in the result.

Let's denote h = column, v = row meaning the number of H and V left to pick, respectively. The result is of length h + v.

We pick the character one by one for the result.

For the first character, if we pick H, the rest of characters can form c = nCr(h - 1 + v, v) combinations.

If k <= c, it means that the result is one of these c combinations. So we should pick H here. We append H to the result and --h.

Otherwise, we should pick V instead, and do --v and k -= c (skip these c combinations).

We keep doing this until we made choice for all the h + v characters.
*/
class Solution {
private:
    int comb(int n, int r) {
        long ans = 1;
        for (int i = 1, j = n - r + 1; i <= r; ++i, ++j) {
            ans = ans * j / i;
        }
        return ans;
    }

public:
    string kthSmallestPath(vector<int> &A, int k) {
        int h = A[1];
        int v = A[0];
        int N = h + v;
        string s;
        for (int i = 0; i < N; ++i) {
            if (h) {
                // we have H available to pick
                int c = comb(h - 1 + v, v);
                // if we pick H at the current position, there will be `c` combinations for the rest of characters
                if (k <= c) {
                    // k is covered within `c`, so we should pick H.
                    s += 'H';
                    --h;
                } else {
                    // otherwise we should pick V
                    k -= c;
                    s += 'V';
                    --v;
                }
            } else {
                // no H left, have to pick V.
                s += 'V';
                --v;
            }
        }
        return s;
    }
};