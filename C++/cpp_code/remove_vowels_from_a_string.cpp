/*
1119. Remove Vowels from a String
Given a string S, remove the vowels 'a', 'e', 'i', 'o', and 'u' from it, and return the new string.

Example 1:

Input: "leetcodeisacommunityforcoders"
Output: "ltcdscmmntyfrcdrs"
Example 2:

Input: "aeiou"
Output: ""


Note:

S consists of lowercase English letters only.
1 <= S.length <= 1000
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
    string removeVowels(string S) {
        string result = "";
        for (char c: S) {
            if (c != 'a' and c
            !=
            'e'
            and c
            !=
            'i'
            and c
            !=
            'o'
            and c
            !=
            'u'
            )
            {
                result.push_back(c);
            }
        }
        return result;
    }
};