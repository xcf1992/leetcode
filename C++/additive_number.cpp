/*
 Additive number is a string whose digits can form additive sequence.
 
 A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
 
 For example:
 "112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
 
 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 "199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
 1 + 99 = 100, 99 + 100 = 199
 Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
 
 Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.
 
 Follow up:
 How would you handle overflow for very large input integers?
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
using namespace std;

class Solution {
private:
    bool isValid(string num1, string num2, string num3) {
        if (num1.size() > 1 && num1[0] == '0') {
            return false;
        }
        if (num2.size() > 1 && num2[0] == '0') {
            return false;
        }
        
        string sum = add(num1, num2);
        if (sum == num3) {
            return true;
        }
        
        if (num3.size() <= sum.size() || sum != num3.substr(0, sum.size())) {
            return false;
        }
        return isValid(num2, sum, num3.substr(sum.size()));
    }
    
    string add(string num1, string num2) {
        return to_string(stol(num1) + stol(num2));
    }
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= (n - i) / 2; j++) {
                if (isValid(num.substr(0, i), num.substr(i, j), num.substr(i + j))) {
                    return true;
                }
            }
        }
        return false;
    }
};
