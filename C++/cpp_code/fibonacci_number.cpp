/*
 The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is
 the sum of the two preceding ones, starting from 0 and 1. That is,

 F(0) = 0,   F(1) = 1
 F(N) = F(N - 1) + F(N - 2), for N > 1.
 Given N, calculate F(N).



 Example 1:

 Input: 2
 Output: 1
 Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
 Example 2:

 Input: 3
 Output: 2
 Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
 Example 3:

 Input: 4
 Output: 3
 Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.


 Note:

 0 ≤ N ≤ 30.
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
private:
    int count(int N, vector<int>& mem) {
        if (mem[N] != -1) {
            return mem[N];
        }

        mem[N] = count(N - 1, mem) + count(N - 2, mem);
        return mem[N];
    }

public:
    int fib(int N) {
        vector<int> mem(100, -1);
        mem[0] = 0;
        mem[1] = 1;
        return count(N, mem);
    }
};