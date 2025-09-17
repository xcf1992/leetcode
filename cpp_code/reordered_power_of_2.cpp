/*
869. Reordered Power of 2
Starting with a positive integer N,
we reorder the digits in any order (including the original order) such that the leading digit is not zero.

Return true if and only if we can do this in a way such that the resulting number is a power of 2.

Example 1:
Input: 1
Output: true

Example 2:
Input: 10
Output: false

Example 3:
Input: 16
Output: true

Example 4:
Input: 24
Output: false

Example 5:
Input: 46
Output: true

Note:
1 <= N <= 10^9
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
using namespace std;

class Solution {
private:
    vector<int> getCount(int num) {
        vector<int> digit(10, 0);
        while (num != 0) {
            digit[num % 10] += 1;
            num /= 10;
        }
        return digit;
    }

    bool compare(vector<int> digit, int num) {
        while (num != 0) {
            int d = num % 10;
            digit[d] -= 1;
            if (digit[d] < 0) {
                return false;
            }
            num /= 10;
        }

        for (int d : digit) {
            if (d != 0) {
                return false;
            }
        }
        return true;
    }
public:
    bool reorderedPowerOf2(int N) {
        string num = to_string(N);
        vector<int> count = getCount(N);
        for (int cur = 1; to_string(cur).size() <= num.size(); cur <<= 1) {
            if (to_string(cur).size() == num.size() and (N == cur or compare(count, cur))) {
                return true;
            }
        }
        return false;
    }
};
