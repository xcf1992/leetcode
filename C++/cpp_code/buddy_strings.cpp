/*
https://leetcode.com/problems/buddy-strings/description/
859. Buddy Strings
Given two strings A and B of lowercase letters,
return true if and only if we can swap two letters in A so that the result equals B.

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false


Note:

0 <= A.length <= 20000
0 <= B.length <= 20000
A and B consist only of lowercase letters.
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
using namespace std;

class Solution {
public:
    bool buddyStrings(string A, string B) {
        int n = A.size();
        if (n <= 1 or n != B.size()) {
            return false;
        }
        if (A == B and set<char>(A.begin(), A.end()).size() < n) {
            // there are duplicate letters
            return true;
        }

        vector<int> diff;
        for (int i = 0; i < n; i++) {
            if (A[i] != B[i]) {
                diff.push_back(i);
            }
        }
        return diff.size() == 2 and A[diff[0]] == B[diff[1]] and A[diff[1]] == B[diff[0]];
    }
};