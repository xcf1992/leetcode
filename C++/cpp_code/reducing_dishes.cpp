/*
1402. Reducing Dishes
https://leetcode.com/problems/reducing-dishes/

A chef has collected data on the satisfaction level of his n dishes.
Chef can cook any dish in 1 unit of time.

Like-time coefficient of a dish is defined as the time taken to cook
that dish including previous dishes multiplied by its satisfaction level
i.e.  time[i]*satisfaction[i]

Return the maximum sum of Like-time coefficient that the chef can obtain after dishes preparation.
Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.

Example 1:
Input: satisfaction = [-1,-8,0,5,-9]
Output: 14
Explanation: After Removing the second and last dish, the maximum total Like-time coefficient will be equal to (-1*1 +
0*2 + 5*3 = 14). Each dish is prepared in one unit of time.

Example 2:
Input: satisfaction = [4,3,2]
Output: 20
Explanation: Dishes can be prepared in any order, (2*1 + 3*2 + 4*3 = 20)

Example 3:
Input: satisfaction = [-1,-4,-5]
Output: 0
Explanation: People don't like the dishes. No dish is prepared.

Example 4:
Input: satisfaction = [-2,5,-1,0,3,-3]
Output: 35

Constraints:
n == satisfaction.length
1 <= n <= 500
-10^3 <= satisfaction[i] <= 10^3
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
#include <map>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition
If we cook some dishes,
they must be the most satisfied among all choices.

Another important observation is that,
we will cook the dish with small satisfication,
and leave the most satisfied dish in the end.

Explanation
We choose dishes from most satisfied.
Everytime we add a new dish to the menu list,
all dishes on the menu list will be cooked one time unit later,
so the result += total satisfaction on the list.
We'll keep doing this as long as A[i] + total > 0.


Complexity
Time O(NlogN)
Space O(1)
*/
class Solution {
public:
    int maxSatisfaction(vector<int>& A) {
        sort(A.begin(), A.end());
        int res = 0, total = 0, n = A.size();
        for (int i = n - 1; i >= 0 && A[i] > -total; --i) {
            total += A[i];
            res += total;
        }
        return res;
    }
};