/*
 869. Reordered Power of 2
 Starting with a positive integer N, we reorder the digits in any order (including the original order) such that the leading digit is not zero.
 
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
    bool compare(int num1, int num2) {
        vector<int> digit(10, 0);
        while (num1 != 0) {
            digit[num1 % 10] += 1;
            num1 /= 10;
        }
        
        while (num2 != 0) {
            int d = num2 % 10;
            digit[d] -= 1;
            if (digit[d] < 0) {
                return false;
            }
            num2 /= 10;
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
        int cur = 1;
        while (to_string(cur).size() <= to_string(N).size()) {
            if (to_string(cur).size() != to_string(N).size()) {
                cur <<= 1;
                continue;
            }
            if (cur == N or compare(N, cur)) {
                return true;
            }
            cur <<= 1;
        }
        return false;
    }
};
