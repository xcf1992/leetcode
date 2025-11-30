/*
856. Score of Parentheses
https://leetcode.com/problems/score-of-parentheses/

Given a balanced parentheses string S,
compute the score of the string based on the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.

Example 1:
Input: "()"
Output: 1

Example 2:
Input: "(())"
Output: 2

Example 3:
Input: "()()"
Output: 2

Example 4:
Input: "(()(()))"
Output: 6

Note:
S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
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
/*
Intuition

The final sum will be a sum of powers of 2,
as every core (a substring (), with score 1) will have it's score multiplied by 2 for each exterior set of parentheses
that contains that core.

Algorithm

Keep track of the balance of the string,
as defined in Approach #1.
For every ) that immediately follows a (, the answer is 1 << balance,
as balance is the number of exterior set of parentheses that contains this core.
*/
class Solution {
public:
    int scoreOfParentheses(string S) {
        int sum = 0;
        int depth = 0;
        for (int i = 0; i < S.size(); i++) {
            depth += S[i] == '(' ? 1 : -1;
            if (S[i] == ')' and S[i - 1] == '(') {
                sum += (1 << depth);
            }
        }
        return sum;
    }
};

/*
cur record the score at the current layer level.

If we meet '(',
we push the current score to stack,
enter the next inner layer level,
and reset cur = 0.

If we meet ')',
the cur score will be doubled and will be at least 1.
We exit the current layer level,
and set cur = stack.pop() + cur

Complexity: O(N) time and O(N) space
*/
class Solution {
public:
    int scoreOfParentheses(string S) {
        stack<int> stk;
        int cur = 0;
        for (char c : S) {
            if (c == '(') {
                stk.push(cur);
                cur = 0;
            } else {
                cur += stk.top() + max(cur, 1);
                stk.pop();
            }
        }
        return cur;
    }
};