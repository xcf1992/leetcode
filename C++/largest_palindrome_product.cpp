//
//  largest_palindrome_product.cpp
//  C++
//
//  Created by Chenfu Xie on 2/24/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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

/*
 Find the largest palindrome made from the product of two n-digit numbers.
 
 Since the result could be very large, you should return the largest palindrome mod 1337.
 
 Example:
 
 Input: 2
 
 Output: 987
 
 Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
 
 Note:
 
 The range of n is [1,8].
 */

class Solution {
private:
    long buildPalindrome(int value) {
        string s = to_string(value);
        reverse(s.begin(), s.end());
        return stol(to_string(value) + s);
    }
public:
    int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }
        
        int maxVal = pow(10, n) - 1;
        for (int v = maxVal; v > maxVal / 10; v--) {
            long palindrome = buildPalindrome(v);
            for (long factor = maxVal; factor * factor >= palindrome; factor--) {
                if (palindrome % factor == 0 && palindrome / factor <= maxVal) {
                    return palindrome % 1337;
                }
            }
        }
        
        return 0;
    }
};
