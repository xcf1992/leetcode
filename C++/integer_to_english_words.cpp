//
//  integer_to_english_words.cpp
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
 Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.
 
 For example,
 123 -> "One Hundred Twenty Three"
 12345 -> "Twelve Thousand Three Hundred Forty Five"
 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 */

class Solution {
private:
    vector<string> below20 = vector<string>({"One", "Two", "Three", "Four","Five","Six","Seven","Eight","Nine","Ten", "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"});
    vector<string> below100 = vector<string>({"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"});
    
    string int2string(int num) {
        if (num >= 1000000000) {
            return int2string(num / 1000000000) + " Billion" + int2string(num % 1000000000);
        }
        else if (num >= 1000000) {
            return int2string(num / 1000000) + " Million" + int2string(num % 1000000);
        }
        else if (num >= 1000) {
            return int2string(num / 1000) + " Thousand" + int2string(num % 1000);
        }
        else if (num >= 100) {
            return int2string(num / 100) + " Hundred" + int2string(num % 100);
        }
        else if (num >= 20) {
            return " " + below100[num / 10 - 2] + int2string(num % 10);
        }
        else if (num >= 1){
            return " " + below20[num - 1];
        }
        return "";
    }
public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }
        return int2string(num).substr(1);
    }
};
