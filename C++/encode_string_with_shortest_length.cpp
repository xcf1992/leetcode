/*
 471. Encode String with Shortest Length
 Given a non-empty string, encode the string such that its encoded length is the shortest.

 The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

 Note:
 k will be a positive integer and encoded string will not be empty or have extra space.
 You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
 If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
 Example 1:

 Input: "aaa"
 Output: "aaa"
 Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
 Example 2:

 Input: "aaaaa"
 Output: "5[a]"
 Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
 Example 3:

 Input: "aaaaaaaaaa"
 Output: "10[a]"
 Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
 Example 4:

 Input: "aabcaabcd"
 Output: "2[aabc]d"
 Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
 Example 5:

 Input: "abbbabbbcabbbabbbc"
 Output: "2[2[abbb]c]"
 Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
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
#include <set>
using namespace std;

/*
O(n ^ 3)
Even though many of us use the following smart condition in code to check for substring repetition,
I didn't see a rigorous proof. So here is one.

Why condition (s+s).find(s,1) < s.size() is equivalent to substring repetition?

Proof: Let N = s.size() and L := (s+s).find(s,1), actually we can prove that the following 2 statements are equivalent:

0 < L < N;
N%L == 0 and s[i] == s[i%L] is true for any i in [0, N). (which means s.substr(0,L) is the repetitive substring)
Consider function char f(int i) { return s[i%N]; }, obviously it has a period N.

"1 => 2": From condition 1, we have for any i in [0,N)

s[i] == (s+s)[i+L] == s[(i+L)%N],
which means L is also a positive period of function f. Note that N == L*(N/L)+N%L, so we have
f(i) == f(i+N) == f(i+L*(N/L)+N%L) == f(i+N%L),
which means N%L is also a period of f. Note that N%L < L but L := (s+s).find(s,1) is the minimum positive period of function f, so we must have N%L == 0. Note that i == L*(i/L)+i%L, so we have
s[i] == f(i) == f(L*(i/L)+i%L) == f(i%L) == s[i%L],
so condition 2 is obtained.
"2=>1": If condition 2 holds, for any i in [0,N), note that N%L == 0, we have

(s+s)[i+L] == s[(i+L)%N] == s[((i+L)%N)%L] == s[(i+L)%L] == s[i],
which means (s+s).substr(L,N) == s, so condition 1 is obtained.
*/
class Solution1 {
private:
    string compress(string& s, int start, int end, vector<vector<string>>& dp) {
        string temp = s.substr(start, end - start + 1);
        int pos = (temp + temp).find(temp, 1);
        if (pos >= temp.size()) {
            return temp;
        }
        return to_string(temp.size() / pos) + "[" + dp[start][start + pos - 1] + "]";
    }
public:
    string encode(string s) {
        int n = s.size();
        vector<vector<string>> dp(n, vector<string>(n, ""));
        for (int length = 1; length <= n; length++) {
            for (int i = 0; i + length <= n; i++) {
                int j = i + length - 1;
                dp[i][j] = s.substr(i, length);

                for (int k = i; k < j; k++) {
                    string left = dp[i][k];
                    string right = dp[k + 1][j];
                    if (left.size() + right.size() < dp[i][j].size()) {
                        dp[i][j] = left + right;
                    }
                }

                string replace = compress(s, i, j, dp);
                if (replace.size() < dp[i][j].size()) {
                    dp[i][j] = replace;
                }
            }
        }
        return dp[0][n - 1];
    }
};

class Solution { // dfs with memo O(n ^ 3)
private:
    unordered_map<string, string> memo;

    int numRepetition(string& s, string sub) {
        int count = 0;
        int pos = 0;
        while (pos < s.size()) {
            if (s.substr(pos, sub.size()) != sub) {
                break;
            }
            count += 1;
            pos += sub.size();
        }
        return count;
    }
public:
    string encode(string s) {
        int n = s.size();
        if (n < 5) {
            return s;
        }
        if (memo.find(s) != memo.end()) {
            return memo[s];
        }

        memo[s] = s;
        for (int i = 0; i < n; ++i) {
            string sub = s.substr(0, i + 1);
            int count = numRepetition(s, sub);
            string temp = "";
            for (int k = 1; k <= count; ++k) {
                if (k == 1) {
                    temp = sub + encode(s.substr(i + 1));
                }
                else {
                    temp = to_string(k) + "[" + encode(sub) + "]" + encode(s.substr(k * sub.size()));
                }
                if (temp.size() < memo[s].size()) {
                    memo[s] = temp;
                }
            }
        }
        return memo[s];
    }
};
