/*
 1021. Remove Outermost Parentheses
 A valid parentheses string is either empty (""), "(" + A + ")", or A + B,
 where A and B are valid parentheses strings,
 and + represents string concatenation.
 For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.

 A valid parentheses string S is primitive if it is nonempty,
 and there does not exist a way to split it into S = A+B,
 with A and B nonempty valid parentheses strings.

 Given a valid parentheses string S,
 consider its primitive decomposition: S = P_1 + P_2 + ... + P_k,
 where P_i are primitive valid parentheses strings.

 Return S after removing the outermost parentheses of every primitive string in the primitive decomposition of S.

 Example 1:

 Input: "(()())(())"
 Output: "()()()"
 Explanation:
 The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
 After removing outer parentheses of each part, this is "()()" + "()" = "()()()".
 Example 2:

 Input: "(()())(())(()(()))"
 Output: "()()()()(())"
 Explanation:
 The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
 After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".
 Example 3:

 Input: "()()"
 Output: ""
 Explanation:
 The input string is "()()", with primitive decomposition "()" + "()".
 After removing outer parentheses of each part, this is "" + "" = "".


 Note:

 S.length <= 10000
 S[i] is "(" or ")"
 S is a valid parentheses string
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
#include <climits>
#include <map>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string S) {
        string result = "";
        int left = 0;
        string temp = "";
        for (int cur = 0; cur < S.size(); cur++) {
            if (S[cur] == '(') {
                left += 1;
                temp.push_back('(');
            } else {
                left -= 1;
                temp.push_back(')');
                if (left == 0) {
                    result += temp.substr(1, temp.size() - 2);
                    temp = "";
                }
            }
        }
        return result;
    }
};