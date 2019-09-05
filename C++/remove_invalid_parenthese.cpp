/*
301. Remove Invalid Parentheses
Remove the minimum number of invalid parentheses in order to make the input string valid.
Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]
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
using namespace std;
/*
Key Points:

Generate unique answer once and only once, do not rely on Set.
Do not need preprocess.
Runtime 3 ms.
Explanation:
We all know how to check a string of parentheses is valid using a stack.
Or even simpler use a counter.
The counter will increase when it is ‘(‘ and decrease when it is ‘)’.
Whenever the counter is negative, we have more ‘)’ than ‘(‘ in the prefix.

To make the prefix valid, we need to remove a ‘)’.
The problem is: which one? The answer is any one in the prefix.
However, if we remove any one, we will generate duplicate results,
for example: s = ()), we can remove s[1] or s[2] but the result is the same ().
Thus, we restrict ourself to remove the first ) in a series of concecutive )s.

After the removal, the prefix is then valid.
We then call the function recursively to solve the rest of the string.
However, we need to keep another information: the last removal position.
If we do not have this position, we will generate duplicate by removing two ‘)’ in two steps only with a different order.
For this, we keep tracking the last removal position and only remove ‘)’ after that.

Now one may ask. What about ‘(‘? What if s = ‘(()(()’ in which we need remove ‘(‘?
The answer is: do the same from right to left.
However a cleverer idea is: reverse the string and reuse the code!
*/
class Solution { // 25.08%
private:
    bool isValid(string s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count += 1;
            }
            if (c == ')') {
                count -= 1;
            }
            if (count < 0) {
                return false;
            }
        }
        return count == 0;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<string> bfs;
        unordered_set<string> visit;
        bfs.push(s);
        visit.insert(s);

        vector<string> result;
        int length = 0;
        while (!bfs.empty()) {
            string curS = bfs.front();
            bfs.pop();
            if (curS.size() < length) {
                continue; // we should skip if we have to remove more parenthese than minimum
            }
            if (isValid(curS)) {
                length = curS.size();
                result.push_back(curS);
                continue;
            }

            for (int i = 0; i < curS.size(); i++) {
                if (curS[i] != '(' && curS[i] != ')') {
                    continue;
                }

                string newS = curS.substr(0, i) + curS.substr(i + 1);
                if (visit.find(newS) == visit.end()) {
                    visit.insert(newS);
                    bfs.push(newS);
                }
            }
        }
        return result;
    }
};
