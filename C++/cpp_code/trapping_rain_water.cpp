/*
42. Trapping Rain Water
https://leetcode.com/problems/trapping-rain-water/

Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it is able to trap after raining.

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.
Thanks Marcos for contributing this image!

Example:
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
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
As in Approach 2,
instead of computing the left and right parts seperately,
we may think of some way to do it in one iteration.
From the figure in dynamic programming approach,
notice that as long as right_max[i]>left_max[i] (from element 0 to 6),
the water trapped depends upon the left_max,
and similar is the case when left_max[i]>right_max[i] (from element 8 to 11).
So, we can say that if there is a larger bar at one end (say right),
we are assured that the water trapped would be dependant on height of bar in current direction (from left to right).
As soon as we find the bar at other end (right) is smaller, we start iterating in opposite direction (from right to
left). We must maintain left_max and right_max during the iteration, but now we can do it in one iteration using 2
pointers, switching between the two.
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int result = 0;
        int left = 0;
        int right = n - 1;
        int leftMax = 0;
        int rightMax = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    result += leftMax - height[left];
                }
                left += 1;
            } else {
                if (height[right] > rightMax) {
                    rightMax = height[right];
                } else {
                    result += rightMax - height[right];
                }
                right -= 1;
            }
        }
        return result;
    }
};

class Solution1 {
    // O(n) tiem and space
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 2) {
            return 0;
        }

        vector<int> leftMax(n, 0);
        leftMax[0] = height.front();
        vector<int> rightMax(n, 0);
        rightMax[n - 1] = height.back();
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
            rightMax[n - i - 1] = max(rightMax[n - i], height[n - i - 1]);
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            int wall = min(leftMax[i], rightMax[i]);
            if (wall > height[i]) {
                result += wall - height[i];
            }
        }
        return result;
    }
};