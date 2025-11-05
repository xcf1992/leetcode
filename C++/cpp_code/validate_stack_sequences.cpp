/*
946. Validate Stack Sequences
https://leetcode.com/problems/validate-stack-sequences/

Given two sequences pushed and popped with distinct values,
return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.

Example 1:
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

Example 2:
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.

Note:
0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed is a permutation of popped.
pushed and popped have distinct values.
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
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
        stack<int> stk;
        int pu = 0;
        int po = 0;
        while (pu < pushed.size() and po<popped.size()
        )
        {
            if (!stk.empty() and po<popped.size() and stk.top() == popped[po]
            )
            {
                stk.pop();
                po += 1;
            }
            else
            {
                stk.push(pushed[pu]);
                pu += 1;
            }
        }

        while (po < popped.size() and
        !stk.empty()
        and
        stk.top() == popped[po]
        )
        {
            po += 1;
            stk.pop();
        }
        return stk.empty()
        and pu
        ==
        pushed.size()
        and po
        ==
        popped.size();
    }
};