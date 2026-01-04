/*
1781. Sum of Beauty of All Substrings
https://leetcode.com/problems/sum-of-beauty-of-all-substrings/

The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.

For example, the beauty of "abaacc" is 3 - 1 = 2.
Given a string s, return the sum of beauty of all of its substrings.

Example 1:
Input: s = "aabcb"
Output: 5
Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.
Example 2:
Input: s = "aabcbaa"
Output: 17

Constraints:
1 <= s.length <= 500
s consists of only lowercase English letters.
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int beautySum(string s) {
        int ans = 0;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int cnt[26] = {};
            int max_f = INT_MIN;
            int min_f = INT_MAX;
            for (int j = i; j < n; j++) {
                int ind = s[j] - 'a';
                cnt[ind]++;
                max_f = max(max_f, cnt[ind]);
                min_f = cnt[ind];
                for (int k = 0; k < 26; k++) {
                    if (cnt[k] >= 1)
                        min_f = min(min_f, cnt[k]);
                }
                ans += (max_f - min_f);
            }
        }
        return ans;
    }
};