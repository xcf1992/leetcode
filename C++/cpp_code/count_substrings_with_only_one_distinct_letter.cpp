/*
1180. Count Substrings with Only One Distinct Letter

Given a string S, return the number of substrings that have only one distinct letter.

Example 1:
Input: S = "aaaba"
Output: 8
Explanation: The substrings with one distinct letter are "aaa", "aa", "a", "b".
"aaa" occurs 1 time.
"aa" occurs 2 times.
"a" occurs 4 times.
"b" occurs 1 time.
So the answer is 1 + 2 + 4 + 1 = 8.

Example 2:
Input: S = "aaaaaaaaaa"
Output: 55

Constraints:
1 <= S.length <= 1000
S[i] consists of only lowercase English letters.
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
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int countLetters(string S) {
        int result = 0;
        int left = 0;
        int right = 0;
        int n = S.size();
        while (left < n and right < n) {
            while (right < n and S[right] == S[left]) {
                right += 1;
            }
            int len = right - left;
            result += len * (len + 1) / 2;
            left = right;
        }
        return result;
    }
};
