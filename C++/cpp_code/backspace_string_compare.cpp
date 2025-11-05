/*
 844. Backspace String Compare
 Given two strings S and T, return if they are equal when both are typed into empty text editors.
 # means a backspace character.

 Example 1:

 Input: S = "ab#c", T = "ad#c"
 Output: true
 Explanation: Both S and T become "ac".
 Example 2:

 Input: S = "ab##", T = "c#d#"
 Output: true
 Explanation: Both S and T become "".
 Example 3:

 Input: S = "a##c", T = "#a#c"
 Output: true
 Explanation: Both S and T become "c".
 Example 4:

 Input: S = "a#c", T = "b"
 Output: false
 Explanation: S becomes "c" while T becomes "b".
 Note:

 1 <= S.length <= 200
 1 <= T.length <= 200
 S and T only contain lowercase letters and '#' characters.
 Follow up:

 Can you solve it in O(N) time and O(1) space?
*/

#include <iostream>
#include <sstream>
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
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1;
        int j = T.size() - 1;
        int countS = 0;
        int countT = 0;
        while (i >= 0 or j
        >=
        0
        )
        {
            while (i >= 0 and(S[i] == '#' or countS > 0)
            )
            {
                countS += S[i] == '#' ? 1 : -1;
                i -= 1;
            }

            while (j >= 0 and(T[j] == '#' or countT > 0)
            )
            {
                countT += T[j] == '#' ? 1 : -1;
                j -= 1;
            }

            if (i < 0 or j<0
            )
            {
                return i == j;
            }

            if (S[i--] != T[j--]) {
                return false;
            }
        }
        return i == j;
    }
};

class Solution1 {
    // space O(N) solution
public:
    bool backspaceCompare(string S, string T) {
        string s = "";
        for (char c: S) {
            if (c == '#') {
                if (!s.empty()) {
                    s.pop_back();
                }
            } else {
                s.push_back(c);
            }
        }

        string t = "";
        for (char c: T) {
            if (c == '#') {
                if (!t.empty()) {
                    t.pop_back();
                }
            } else {
                t.push_back(c);
            }
        }
        return s == t;
    }
};