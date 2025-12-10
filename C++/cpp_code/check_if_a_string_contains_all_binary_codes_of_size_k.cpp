/*
1461. Check If a String Contains All Binary Codes of Size K
https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/

Given a binary string s and an integer k.
Return True if all binary codes of length k is a substring of s.
Otherwise, return False.

Example 1:
Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indicies
0, 1, 3 and 2 respectively.

Example 2:
Input: s = "00110", k = 2
Output: true

Example 3:
Input: s = "0110", k = 1
Output: true
Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring.

Example 4:
Input: s = "0110", k = 2
Output: false
Explanation: The binary code "00" is of length 2 and doesn't exist in the array.

Example 5:
Input: s = "0000000001011100", k = 4
Output: false

Constraints:
1 <= s.length <= 5 * 10^5
s consists of 0's and 1's only.
1 <= k <= 20
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
#include <map>
#include <climits>

using namespace std;

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        long long x = pow((long long)2, (long long)k);  // calculating no. of possible binary strings of size k
        if (s.size() < x) {
            return false;
        }

        unordered_set<long long> ss;
        for (int i = 0; i + k - 1 < s.size(); i++) {
            ss.insert(stol(s.substr(i, k)));  // generating all possible substrings of size k using given string
        }
        return ss.size() == x;  // checking the final condition
    }
};
// TLE
class Solution {
private:
    string toBinary(int num, int len) {
        int left = 0;
        string result = "";
        while (num != 0) {
            result.push_back('0' + num % 2);
            num /= 2;
        }
        result += string(len - result.size(), '0');
        reverse(result.begin(), result.end());
        return result;
    }

public:
    bool hasAllCodes(string s, int k) {
        for (int i = 0; i < pow(2, k); ++i) {
            if (s.find(toBinary(i, k)) == string::npos) {
                return false;
            }
        }
        return true;
    }
};
