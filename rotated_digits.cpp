//
//  rotated_digits.cpp
//  C++
//
//  Created by Chenfu Xie on 2/26/18.
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
 X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X. A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number.
 
 Now given a positive number N, how many numbers X from 1 to N are good?
 
 Example:
 Input: 10
 Output: 4
 Explanation:
 There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
 Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
 */

class Solution {
public:
    int rotatedDigits(int N) {
        vector<int> goodSame({1,2,2,2,2,2,2,2,3,3});
        vector<int> goodDiff({0,0,1,1,1,2,3,3,3,4});
        vector<int> digitType({0,0,1,2,2,1,1,2,0,1});
        
        if (N < 10) {
            return goodDiff[N];
        }
        string num = to_string(N);
        int result = 0;
        int length = num.size();
        int digit = num[0] - '0';
        result += (goodSame[digit - 1] + goodDiff[digit - 1]) * pow(7, length - 1) - goodSame[digit - 1] * pow(3, length - 1);
        bool allSame = true;
        
        if (digitType[digit] == 2) {
            return result;
        }
        
        if (digitType[digit] == 1) {
            allSame = false;
        }
        for (int i = length - 2; i >= 0; i--) {
            digit = num[length - i - 1] - '0';
            result += (goodSame[digit - 1] + goodDiff[digit - 1]) * pow(7, i);
            
            if (allSame) {
                result -= (goodSame[digit - 1]) * pow(3, i);
            }
            
            if (digitType[digit] == 2) {
                return result;
            }
            
            if (digitType[digit] == 1) {
                if (i == 0) {
                    result += 1;
                }
                allSame = false;
            }
            else if (i == 0) {
                if (!allSame) {
                    result += 1;
                }
            }
        }
        return result;
    }
};
