/*
625. Minimum Factorization

Given a positive integer a,
find the smallest positive integer b whose multiplication of each digit equals to a.
If there is no answer or the answer is not fit in 32-bit signed integer, then return 0.

Example 1
Input:
48
Output:
68

Example 2
Input:
15
Output:
35
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
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    int getDivisor(int num) {
        for (int i = 9; i >= 2; i--) {
            if (num % i == 0) {
                return i;
            }
        }
        return num;
    }

public:
    int smallestFactorization(int a) {
        if (a <= 1) {
            return a;
        }

        vector<int> digit(10, 0);
        while (a > 1) {
            int d = getDivisor(a); // get all possible factors from 9 to 2
            if (d > 9) {
                return 0;
            }
            digit[d] += 1;
            a /= d;
        }

        long long result = 0;
        for (int i = 0; i < 10; i++) {
            while (digit[i] != 0) {
                result = result * 10 + i;
                digit[i] -= 1;
            }
            if (result > INT_MAX) {
                return 0;
            }
        }
        return result;
    }
};