/*
360. Sort Transformed Array

Given a sorted array of integers nums and integer values a, b and c.
Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.
Expected time complexity: O(n)

Example:
nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,
Result: [3, 9, 15, 33]
nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5
Result: [-23, -5, 1, 7]
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
the problem seems to have many cases a>0, a=0,a<0, (when a=0, b>0, b<0).
However, they can be combined into just 2 cases: a>0 or a<0

1.a>0, two ends in original array are bigger than center if you learned middle school math before.

2.a<0, center is bigger than two ends.

so use two pointers i, j and do a merge-sort like process.
depending on sign of a, you may want to start from the beginning or end of the transformed array.
For a==0 case, it does not matter what b's sign is.

The function is monotonically increasing or decreasing.
you can start with either beginning or end.
*/
class Solution {
private:
    int quad(int x, int a, int b, int c) {
        return a * x * x + b * x + c;
    }

public:
    vector<int> sortTransformedArray(vector<int> &nums, int a, int b, int c) {
        int n = nums.size();
        vector<int> sorted(n, 0);
        int left = 0;
        int right = n - 1;
        int index = a >= 0 ? n - 1 : 0;
        while (left <= right) {
            if (a >= 0) {
                sorted[index--] = quad(nums[left], a, b, c) >= quad(nums[right], a, b, c)
                                      ? quad(nums[left++], a, b, c)
                                      : quad(nums[right--], a, b, c);
            } else {
                sorted[index++] = quad(nums[left], a, b, c) >= quad(nums[right], a, b, c)
                                      ? quad(nums[right--], a, b, c)
                                      : quad(nums[left++], a, b, c);
            }
        }
        return sorted;
    }
};

class Solution1 {
public:
    vector<int> sortTransformedArray(vector<int> &nums, int a, int b, int c) {
        vector<int> result;
        if (a == 0) {
            for (int i: nums) {
                result.push_back(b * i + c);
            }
            if (b >= 0) {
                return result;
            } else {
                reverse(result.begin(), result.end());
                return result;
            }
        }

        int n = nums.size();
        double mid = 0 - (double) b / (2 * a);
        int left = 0;
        int right = n - 1;
        while (left + 1 < n and((double) nums[left + 1]) < mid
        )
        {
            left += 1;
        }
        while (right > 0 and((double) nums[right - 1]) >= mid
        )
        {
            right -= 1;
        }

        while (left >= 0 or right<n
        )
        {
            if (left < 0) {
                result.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                right += 1;
                continue;
            }
            if (right == n) {
                result.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                left -= 1;
                continue;
            }
            if (abs((double) nums[right] - mid) >= abs((double) nums[left] - mid)) {
                result.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                left -= 1;
            } else {
                result.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                right += 1;
            }
        }

        if (a < 0) {
            reverse(result.begin(), result.end());
        }
        return result;
    }
};