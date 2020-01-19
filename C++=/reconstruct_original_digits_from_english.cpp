/*
423. Reconstruct Original Digits from English
https://leetcode.com/problems/reconstruct-original-digits-from-english/

Given a non-empty string containing an out-of-order English representation of digits 0-9,
output the digits in ascending order.

Note:
Input contains only lowercase English letters.
Input is guaranteed to be valid and can be transformed to its original digits.
That means invalid inputs such as "abc" or "zerone" are not permitted.
Input length is less than 50,000.

Example 1:
Input: "owoztneoer"

Output: "012"
Example 2:
Input: "fviefuro"

Output: "45"
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
using namespace std;

class Solution {
public:
    string originalDigits(string s) {
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a'] += 1;
        }

        vector<string> words = {"zero", "two", "four", "six", "eight", "one", "three", "five", "seven", "nine"};
        vector<int> nums = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        vector<int> distinct = {'z', 'w', 'u', 'x', 'g', 'o', 'r', 'f', 'v', 'i'};
        string result;
        for (int i = 0; i < 10; i++) {
            string word = words[i];
            int count = counts[distinct[i] - 'a'];

            for (char c : word) {
                counts[c - 'a'] -= count;
            }
            result += string(count, nums[i] + '0');
        }
        sort(result.begin(), result.end());
        return result;
    }
};
