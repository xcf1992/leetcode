/*
42. Trapping Rain Water

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

class Solution {
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
