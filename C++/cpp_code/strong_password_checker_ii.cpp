/*
https://leetcode.com/problems/strong-password-checker-ii/description/
2299. Strong Password Checker II

A password is said to be strong if it satisfies all the following criteria:

It has at least 8 characters.
It contains at least one lowercase letter.
It contains at least one uppercase letter.
It contains at least one digit.
It contains at least one special character. The special characters are the characters in the following string:
"!@#$%^&*()-+". It does not contain 2 of the same character in adjacent positions (i.e., "aab" violates this condition,
but "aba" does not). Given a string password, return true if it is a strong password. Otherwise, return false.



Example 1:

Input: password = "IloveLe3tcode!"
Output: true
Explanation: The password meets all the requirements. Therefore, we return true.
Example 2:

Input: password = "Me+You--IsMyDream"
Output: false
Explanation: The password does not contain a digit and also contains 2 of the same character in adjacent positions.
Therefore, we return false. Example 3:

Input: password = "1aB!"
Output: false
Explanation: The password does not meet the length requirement. Therefore, we return false.


Constraints:

1 <= password.length <= 100
password consists of letters, digits, and special characters: "!@#$%^&*()-+".
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    bool strongPasswordCheckerII(string password) {
        int n = password.size();
        if (n < 8) {
            return false;
        }

        bool lower_case_flag = false;
        bool upper_case_flag = false;
        bool digit_flag = false;
        bool special_char_flag = false;
        string special_char = "!@#$%^&*()-+";
        unordered_set<char> special_char_set(special_char.begin(), special_char.end());
        for (int i = 0; i < n; i++) {
            if (i != 0 && password[i] == password[i - 1]) {
                return false;
            }

            char c = password[i];
            if (isdigit(c)) {
                digit_flag = true;
            } else if (c >= 'a' && c <= 'z') {
                lower_case_flag = true;
            } else if (c >= 'A' && c <= 'Z') {
                upper_case_flag = true;
            } else if (special_char_set.find(c) != special_char_set.end()) {
                special_char_flag = true;
            }
        }
        return lower_case_flag && upper_case_flag && digit_flag && special_char_flag;
    }
};