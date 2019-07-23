/*
84. Largest Rectangle in Histogram
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:
Input: [2,1,5,6,2,3]
Output: 10
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
using namespace std;

/*
In this approach, we maintain a stack.
Initially, we push a -1 onto the stack to mark the end.
We start with the leftmost bar and keep pushing the current bar's index onto the stack
until we get two successive numbers in descending order,
i.e. until we get a[i] < a[i-1].

Now, we start popping the numbers from the stack until we hit a number stack[j] on the stack
such that a[stack[j]] <= a[i].
Every time we pop,
we find out the area of rectangle formed using the current element as the height of the rectangle
and the difference between the the current element's index pointed to in the original array
and the element stack[top−1]−1 as the width
i.e. if we pop an element stack[top] and i is the current index to which we are pointing in the original array,
the current area of the rectangle will be considered as:

(i − stack[top−1] − 1) * a[stack[top]].

Further, if we reach the end of the array,
we pop all the elements of the stack and at every pop,
this time we use the following equation to find the area:
(stack[top] − stack[top−1]) * a[stack[top]],
where stack[top]stack[top] refers to the element just popped.
Thus, we can get the area of the of the largest rectangle by comparing the new area found everytime.

The following example will clarify the process further:
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        stk.push(-1);
        int result = 0;
        int n = heights.size();
        for (int i = 0; i < n; ++i) {
            while (stk.top() != -1 and heights[i] < heights[stk.top()]) {
                int cur = stk.top();
                stk.pop();
                result = max(result, heights[cur] * (i - stk.top() - 1));
            }
            stk.push(i);
        }
        while (stk.top() != -1) {
            int cur = stk.top();
            stk.pop();
            result = max(result, heights[cur] * (n - stk.top() - 1));
        }
        return result;
    }
};

// wrong answer [4,2,0,3,2,4,3,4]
class Solution1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (n <= 0) {
            return 0;
        }

        vector<int> left(n, 0);
        int index = 0;
        left[0] = heights[0];
        for (int i = 1; i < n; ++i) {
            if (heights[i] > heights[i - 1]) {
                index = i;
            }
            left[i] = heights[i] * (i - index + 1);
        }

        vector<int> right(n, 0);
        right[n - 1] = heights[n - 1];
        index = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            if (heights[i] > heights[i + 1]) {
                index = i;
            }
            right[i] = heights[i] * (index - i + 1);
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = max(result, right[i] + left[i] - heights[i]);
        }
        return result;
    }
};
