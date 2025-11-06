/*
1541. Minimum Insertions to Balance a Parentheses String
https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/

Given a parentheses string s containing only the characters '(' and ')'.
A parentheses string is balanced if:

Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.

You can insert the characters '(' and ')' at any position of the string to balance it if needed.
Return the minimum number of insertions needed to make s balanced.

Example 1:
Input: s = "(()))"
Output: 1
Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to to add one more
')' at the end of the string to be "(())))" which is balanced.

Example 2:
Input: s = "())"
Output: 0
Explanation: The string is already balanced.

Example 3:
Input: s = "))())("
Output: 3
Explanation: Add '(' to match the first '))', Add '))' to match the last '('.

Example 4:
Input: s = "(((((("
Output: 12
Explanation: Add 12 ')' to balance the string.

Example 5:
Input: s = ")))))))"
Output: 5
Explanation: Add 4 '(' at the beginning of the string and one ')' at the end. The string becomes "(((())))))))".

Constraints:
1 <= s.length <= 10^5
s consists of '(' and ')' only.
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
/*
Intuition
Similar to 921. Minimum Add to Make Parentheses Valid.
Just need to pay attention:
left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.


Explanation
res represents the number of left/right parentheses already added.
right represents the number of right parentheses needed.

1) case )
If we meet a right parentheses , right--.
If right < 0, we need to add a left parentheses before it.
Then we update right += 2 and res++
This part is easy and normal.

2) case (
If we meet a left parentheses,
we check if we have odd number ')' before.
If we right, we have odd ')' before,
but we want right parentheses in paires.
So add one ')' here, then update right--; res++;.
Note that this part is not necessary if two consecutive right parenthesis not required.

Because we have ), we update right += 2.


Dry run
All by @himanshusingh11:

Example 1: Consider ((()(,n= 5 ,i=0,1...4
i=0, we have ( it means we need two right parenthesis (they are in pair) so.. right+=2 => res =0, right =2
i=1, again we have ( it means we need two right parenthesis (they are in pair) so.. right+=2 => res =0, right =4
i=2, again we have ( it means we need two right parenthesis (they are in pair) so.. right+=2 => res =0, right =6
i=3, we have ) we subtract one from right. so.. right-- => res =0, right =5
i=4, we have ( but here right is odd so we need to make it even with right-- and increment res++ => res =1, right =4.
Also, as we have got a left parenthesis then we need two right parenthesis (they are in pair) so.. right+=2 => res =1,
right =6

finally ans is res + right => 1 +6 == 7

Example 2: ((()
Similarly, we can see when we have right<0 then we increment res by one & add 2 to right as they should be in pairs..


Complexity
Time O(N)
Space O(1)
*/
class Solution {
public:
    int minInsertions(string s) {
        int res = 0;
        int right = 0;
        for (char& c : s) {
            if (c == '(') {
                if (right % 2 > 0) {
                    right--;
                    res++;
                }
                right += 2;
            } else {
                right--;
                if (right < 0) {
                    right += 2;
                    res++;
                }
            }
        }
        return right + res;
    }
};
