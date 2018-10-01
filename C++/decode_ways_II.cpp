/*
 A message containing letters from A-Z is being encoded to numbers using the following mapping way:
 
 'A' -> 1
 'B' -> 2
 ...
 'Z' -> 26
 Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9.
 
 Given the encoded message containing digits and the character '*', return the total number of ways to decode it.
 
 Also, since the answer may be very large, you should return the output mod 109 + 7.
 
 Example 1:
 Input: "*"
 Output: 9
 Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
 Example 2:
 Input: "1*"
 Output: 9 + 9 = 18
 Note:
 The length of the input string will fit in range [1, 105].
 The input string will only contain the character '*' and digits '0' - '9'.
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
#include <numeric>
using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int MOD = 1e9 + 7;
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 1;
        dp[n - 1] = s[n - 1] == '0' ? 0 : 1;
        
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] == '0') {
                continue;
            }
            if (s[i] != '*') {
                int num = stoi(s.substr(i, 2));
                dp[i] = num <= 26 ? dp[i + 1] + dp[i + 2] : dp[i + 1];
            }
            else {
                dp[i] = ((9 * dp[i + 1]) % MOD + dp[i + 2]) % MOD;
                if (s[i] <= '6') {
                    dp[i] += + dp[i + 2];
                }
            }
            dp[i] %= MOD;
        }
        
        return dp[0];
    }
};
