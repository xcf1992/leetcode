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

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        stk.push(-1);
        int result = 0;
        int n = heights.size();
        for (int i = 0; i < n; ++i) {
            while (stk.top() != -1 and heights[i] <= heights[stk.top()]) {
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
