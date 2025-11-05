/*
1616. Split Two Strings to Make Palindrome
https://leetcode.com/problems/split-two-strings-to-make-palindrome/

You are given two strings a and b of the same length.
Choose an index and split both strings at the same index,
splitting a into two strings: aprefix and asuffix where a = aprefix + asuffix,
and splitting b into two strings: bprefix and bsuffix where b = bprefix + bsuffix.
Check if aprefix + bsuffix or bprefix + asuffix forms a palindrome.

When you split a string s into sprefix and ssuffix,
either ssuffix or sprefix is allowed to be empty.
For example, if s = "abc", then "" + "abc", "a" + "bc", "ab" + "c" , and "abc" + "" are valid splits.

Return true if it is possible to form a palindrome string, otherwise return false.
Notice that x + y denotes the concatenation of strings x and y.

Example 1:
Input: a = "x", b = "y"
Output: true
Explaination: If either a or b are palindromes the answer is true since you can split in the following way:
aprefix = "", asuffix = "x"
bprefix = "", bsuffix = "y"
Then, aprefix + bsuffix = "" + "y" = "y", which is a palindrome.

Example 2:
Input: a = "abdef", b = "fecab"
Output: true

Example 3:
Input: a = "ulacfd", b = "jizalu"
Output: true
Explaination: Split them at index 3:
aprefix = "ula", asuffix = "cfd"
bprefix = "jiz", bsuffix = "alu"
Then, aprefix + bsuffix = "ula" + "alu" = "ulaalu", which is a palindrome.

Example 4:
Input: a = "xbdef", b = "xecab"
Output: false

Constraints:
1 <= a.length, b.length <= 105
a.length == b.length
a and b consist of lowercase English letters
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include "extra_data_types.hpp"
using namespace std;
/*
Greedily take the a_suffix and b_prefix as long as they are palindrome,
that is, a_suffix = reversed(b_prefix).

The the middle part of a is s1,
The the middle part of b is s2.

If either s1 or s2 is palindrome, then return true.

Then we do the same thing for b_suffix and a_prefix

one of the 2 strings must be palindrome so that we can select that string itself
either starting chars of str1 and ending chars of str2 must be same and also the in between part of the string must also be a palindrome(as written by the original commentor)
(same as pt 2) starting chars of str2 and ending chars of str1 must be same and then the same check as in pt 2.
Try writing a few examples with answer true and look at the 3 points above. You will get the intiution.

*/
class Solution {
private:
    bool isPa(string &s, int i, int j) {
        for (; i < j; ++i, --j) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }

    bool check(string &a, string &b) {
        for (int i = 0, j = a.size() - 1; i < j; ++i, --j) {
            if (a[i] != b[j]) {
                // think about abedfg and abaaba
                return isPa(a, i, j) || isPa(b, i, j);
            }
        }
        return true;
    }

public:
    bool checkPalindromeFormation(string a, string b) {
        return check(a, b) || check(b, a);
    }
};