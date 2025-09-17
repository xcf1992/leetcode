/*
394. Decode String
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string],
where the encoded_string inside the square brackets is being repeated exactly k times.
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid;
No extra white spaces, square brackets are well-formed, etc.

Furthermore,
you may assume that the original data does not contain any digits
and that digits are only for those repeat numbers, k.
For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
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
private:
    string decode(string& s, int& i) {
        string result = "";
        while (i < s.size() and s[i] != ']') {
            if (isalpha(s[i])) {
                result.push_back(s[i]);
            }
            else {
                int numStart = i;
                while (isdigit(s[i])) {
                    i++;
                }
                int repeat = stoi(s.substr(numStart, i - numStart));
                string word = decode(s, ++i);
                while (repeat > 0) {
                    result.append(word);
                    repeat--;
                }
            }
            i++;
        }
        return result;
    }
public:
    string decodeString(string s) {
        int i = 0;
        return decode(s, i);
    }
};
