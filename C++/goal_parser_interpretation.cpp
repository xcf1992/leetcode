/*
1678. Goal Parser Interpretation
https://leetcode.com/problems/goal-parser-interpretation/

You own a Goal Parser that can interpret a string command.
The command consists of an alphabet of "G", "()" and/or "(al)" in some order.
The Goal Parser will interpret "G" as the string "G", "()" as the string "o",
and "(al)" as the string "al".
The interpreted strings are then concatenated in the original order.

Given the string command,
return the Goal Parser's interpretation of command.

Example 1:
Input: command = "G()(al)"
Output: "Goal"
Explanation: The Goal Parser interprets the command as follows:
G -> G
() -> o
(al) -> al
The final concatenated result is "Goal".

Example 2:
Input: command = "G()()()()(al)"
Output: "Gooooal"

Example 3:
Input: command = "(al)G(al)()()G"
Output: "alGalooG"

Constraints:
1 <= command.length <= 100
command consists of "G", "()", and/or "(al)" in some order.
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
    string interpret(string s) {
        string ans;
        for (int i = 0; i < s.size(); ) {
            if (s[i] == 'G') ans += 'G', ++i;
            else if (s[i + 1] == ')') ans += 'o', i += 2;
            else ans += "al", i += 4;
        }
        return ans;
    }
};