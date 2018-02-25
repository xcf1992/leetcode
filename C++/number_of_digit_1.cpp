//
//  number_of_digit_1.cpp
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
 Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
 
 For example:
 Given n = 13,
 Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
 */

class Solution {
public:
    int countDigitOne(int n) {
        int result = 0;
        int factor = 1;
        int lowerNum = 0;
        int curNum = 0;
        int higherNum = 0;
        
        while (n / factor != 0) {
            lowerNum = n - (n / factor) * factor;
            curNum = (n / factor) % 10;
            higherNum = n / (factor * 10);
            
            if (curNum == 0) {
                result += higherNum * factor;
            }
            else if (curNum == 1) {
                result += higherNum * factor + lowerNum + 1;
            }
            else {
                result += (higherNum + 1) * factor;
            }
            
            factor *= 10;
        }
        return result;
    }
};
