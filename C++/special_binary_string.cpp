/*
 761. Special Binary String
 Special binary strings are binary strings with the following two properties:

 The number of 0's is equal to the number of 1's.
 Every prefix of the binary string has at least as many 1's as 0's.
 Given a special string S, a move consists of choosing two consecutive, non-empty,
 special substrings of S, and swapping them.
 (Two strings are consecutive if the last character of the first string
  is exactly one index before the first character of the second string.)

 At the end of any number of moves, what is the lexicographically largest resulting string possible?

 Example 1:
 Input: S = "11011000"
 Output: "11100100"
 Explanation:
 The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
 This is the lexicographically largest string possible after some number of swaps.
 Note:

 S has length at most 50.
 S is guaranteed to be a special binary string as defined above.
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
    string makeLargestSpecial(string S) {
        vector<string> specials;
        int count = 0;
        for (char c : S) {
            if (count == 0) {
                specials.push_back("");
            }
            count += c == '1' ? 1 : -1;
            specials.back().push_back(c);
        }

        for (string& special : specials) {
            special = "1" + makeLargestSpecial(special.substr(1, special.size() - 2)) + "0";
        }

        sort(specials.begin(), specials.end(), [](string& a, string& b) {
            return a > b;
        });
        string result = "";
        for (string special : specials) {
            result += special;
        }
        return result;
    }
};
