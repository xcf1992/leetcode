/*
5126. Element Appearing More Than 25% In Sorted Array
https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/

Given an integer array sorted in non-decreasing order,
there is exactly one integer in the array that occurs more than 25% of the time.
Return that integer.

Example 1:
Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6

Constraints:
1 <= arr.length <= 10^4
0 <= arr[i] <= 10^5
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

class Solution {
    bool check(vector<int>& arr, int num, int n) {
        auto first = lower_bound(arr.begin(), arr.end(), num);
        auto last = upper_bound(arr.begin(), arr.end(), num);
        int count = last - first;
        return (double)count / n > 0.25;
    }

public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) {
            return arr[0];
        }

        for (int i = 1; i <= 3; ++i) {
            int num = arr[n * i / 4];
            if (check(arr, num, n)) {
                return num;
            }
        }
        return -1;
    }
};
