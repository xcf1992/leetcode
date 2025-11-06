/*
1189. Maximum Number of Balloons
https://leetcode.com/problems/maximum-number-of-balloons/

Given a string text,
you want to use the characters of text to form as many instances of the word "balloon" as possible.
You can use each character in text at most once.
Return the maximum number of instances that can be formed.

Example 1:
Input: text = "nlaebolko"
Output: 1

Example 2:
Input: text = "loonbalxballpoon"
Output: 2

Example 3:
Input: text = "leetcode"
Output: 0

Constraints:
1 <= text.length <= 10^4
text consists of lower case English letters only.
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
#include <numeric>
using namespace std;

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        string target = "balloon";
        vector<int> required(26, 0);
        for (char c : target) {
            required[c - 'a'] += 1;
        }

        vector<int> count(26, 0);
        for (char c : text) {
            count[c - 'a'] += 1;
        }

        int result = INT_MAX;
        for (int i = 0; i < 26; ++i)
            if (required[i] != 0) {
                if (count[i] < required[i]) {
                    result = 0;
                    break;
                }
                result = min(result, count[i] / required[i]);
            }
        return result;
    }
};