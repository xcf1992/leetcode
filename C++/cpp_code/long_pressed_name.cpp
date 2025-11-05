/*
 925. Long Pressed Name
 Your friend is typing his name into a keyboard.
 Sometimes, when typing a character c,
 the key might get long pressed,
 and the character will be typed 1 or more times.

 You examine the typed characters of the keyboard.
 Return True if it is possible that it was your friends name,
 with some characters (possibly none) being long pressed.

 Example 1:

 Input: name = "alex", typed = "aaleex"
 Output: true
 Explanation: 'a' and 'e' in 'alex' were long pressed.
 Example 2:

 Input: name = "saeed", typed = "ssaaedd"
 Output: false
 Explanation: 'e' must have been pressed twice, but it wasn't in the typed output.
 Example 3:

 Input: name = "leelee", typed = "lleeelee"
 Output: true
 Example 4:

 Input: name = "laiden", typed = "laiden"
 Output: true
 Explanation: It's not necessary to long press any character.


 Note:

 name.length <= 1000
 typed.length <= 1000
 The characters of name and typed are lowercase letters.
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
    bool isLongPressedName(string name, string typed) {
        int m = name.size();
        int n = typed.size();
        if (m > n) {
            return false;
        }

        int i = 0;
        int j = 0;
        while (i < m and j<n
        )
        {
            if (name[i] == typed[j]) {
                i += 1;
                j += 1;
            } else if (i != 0 and name[i - 1]
            ==
            typed[j]
            )
            {
                j += 1;
            }
            else
            {
                break;
            }
        }
        while (i == m and j<n
        )
        {
            if (name[i - 1] == typed[j]) {
                j += 1;
            }
        }
        return i == m
        and j
        ==
        n;
    }
};