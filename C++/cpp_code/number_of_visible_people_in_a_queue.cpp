/*
https://leetcode.com/problems/number-of-visible-people-in-a-queue/description/
1944. Number of Visible People in a Queue

There are n people standing in a queue, and they numbered from 0 to n - 1 in left to right order. You are given an array
heights of distinct integers where heights[i] represents the height of the ith person.

A person can see another person to their right in the queue if everybody in between is shorter than both of them. More
formally, the ith person can see the jth person if i < j and min(heights[i], heights[j]) > max(heights[i+1],
heights[i+2], ..., heights[j-1]).

Return an array answer of length n where answer[i] is the number of people the ith person can see to their right in the
queue.



Example 1:



Input: heights = [10,6,8,5,11,9]
Output: [3,1,2,1,1,0]
Explanation:
Person 0 can see person 1, 2, and 4.
Person 1 can see person 2.
Person 2 can see person 3 and 4.
Person 3 can see person 4.
Person 4 can see person 5.
Person 5 can see no one since nobody is to the right of them.
Example 2:

Input: heights = [5,1,2,3,10]
Output: [4,1,1,1,0]


Constraints:

n == heights.length
1 <= n <= 105
1 <= heights[i] <= 105
All the values of heights are unique.
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
#include <set>
#include <numeric>
using namespace std;

/*
We maintain a decreasing mono stack,
(I stored the index of elements)

As we iterate each element a in input array A,
assume the last element in the stack has index i.
If the last element A[i] <= a,
A[i] can see a,
so we increment res[i]++

Because a is tall and block the line of sight.
A[i] can't see any element after a,
we have done the work for A[i],
so we stack.pop() it from the stack.

We keep doing this while A[i] < a, where i = stack.top().
By doing this, if stack is not empty,
A[i] will be the left next greater element of a.
A[i] can still see a,
so we increment res[i]++.

We do the above for each element a in A,
and we finally return result res
 */

class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> res(n);
        vector<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && heights[stk.back()] <= heights[i]) {
                res[stk.back()] += 1;
                stk.pop_back();
            }

            if (!stk.empty()) {
                res[stk.back()] += 1;
            }

            stk.push_back(i);
        }
        return res;
    }
};
