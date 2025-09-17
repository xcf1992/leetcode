/*
1243. Array Transformation
https://leetcode.com/problems/array-transformation/

Given an initial array arr, every day you produce a new array using the array of the previous day.
On the i-th day, you do the following operations on the array of day i-1 to produce the array of day i:

If an element is smaller than both its left neighbor and its right neighbor, then this element is incremented.
If an element is bigger than both its left neighbor and its right neighbor, then this element is decremented.
The first and last elements never change.
After some days, the array does not change. Return that final array.

Example 1:
Input: arr = [6,2,3,4]
Output: [6,3,3,4]
Explanation:
On the first day, the array is changed from [6,2,3,4] to [6,3,3,4].
No more operations can be done to this array.

Example 2:
Input: arr = [1,6,3,4,3,5]
Output: [1,4,4,4,4,5]
Explanation:
On the first day, the array is changed from [1,6,3,4,3,5] to [1,5,4,3,4,5].
On the second day, the array is changed from [1,5,4,3,4,5] to [1,4,4,4,4,5].
No more operations can be done to this array.

Constraints:
1 <= arr.length <= 100
1 <= arr[i] <= 100
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
    vector<int> transformArray(vector<int>& arr) {
        int n = arr.size();
        if (n <= 2) {
            return arr;
        }

        bool valueChanged = false;
        do {
            valueChanged = false;
            vector<int> temp = arr;
            for (int i = 1; i < n - 1; ++i) {
                if (arr[i] > arr[i - 1] and arr[i] > arr[i + 1]) {
                    temp[i] -=1;
                    valueChanged = true;
                }
                if (arr[i] < arr[i - 1] and arr[i] < arr[i + 1]) {
                    temp[i] +=1;
                    valueChanged = true;
                }
            }
            arr = temp;
        } while (valueChanged);
        return arr;
    }
};
