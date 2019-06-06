/*
 926. Flip String to Monotone Increasing
 A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0), followed by some number of '1's (also possibly 0.)
 
 We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.
 
 Return the minimum number of flips to make S monotone increasing.
 
 
 
 Example 1:
 
 Input: "00110"
 Output: 1
 Explanation: We flip the last digit to get 00111.
 Example 2:
 
 Input: "010110"
 Output: 2
 Explanation: We flip to get 011111, or alternatively 000111.
 Example 3:
 
 Input: "00011000"
 Output: 2
 Explanation: We flip to get 00000000.
 
 
 Note:
 
 1 <= S.length <= 20000
 S only consists of '0' and '1' characters.
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
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        if (n == 0) {
            return 0;
        }
        vector<int> leftOne(n + 2, 0);
        vector<int> rightZero(n + 2, 0);
        for (int i = 1; i < n + 1; i++) {
            leftOne[i] = leftOne[i - 1] + (S[i - 1] - '0');
            
            int j = n + 1 - i;
            rightZero[j] = rightZero[j + 1] + ('1' - S[j - 1]);
        }
        
        int result = n;
        for (int i = 1; i < n + 2; i++) {
            result = min(result, leftOne[i - 1] + rightZero[i]);
        }
        return result;
    }
};

class Solution { // dp
public:
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        if (n == 0) {
            return 0;
        }
        
        int endOne = 0;
        int endZero = 0;
        for (char c : S) {
            if (c == '0') {
                endOne = 1 + min(endOne, endZero);
            }
            else {
                endOne = min(endZero, endOne);
                endZero = 1 + endZero;
            }
        }
        return min(endZero, endOne);
    }
};
