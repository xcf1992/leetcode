/*
125. Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false
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
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            if (!isalpha(s[left]) and !isdigit(s[left])) {
                left += 1;
                continue;
            }
            if (!isalpha(s[right]) and !isdigit(s[right])) {
                right -= 1;
                continue;
            }

            if (toupper(s[left]) != toupper(s[right])) {
                return false;
            }
            left += 1;
            right -= 1;
        }
        return true;
    }
};
