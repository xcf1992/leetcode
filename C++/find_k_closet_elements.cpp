/*
658. Find K Closest Elements
Given a sorted array, two integers k and x,
find the k closest elements to x in the array.
The result should also be sorted in ascending order.
If there is a tie, the smaller elements are always preferred.

Example 1:
Input: [1,2,3,4,5], k=4, x=3
Output: [1,2,3,4]
Example 2:
Input: [1,2,3,4,5], k=4, x=-1
Output: [1,2,3,4]
Note:
The value k is positive and will always be smaller than the length of the sorted array.
Length of the given array is positive and will not exceed 104
Absolute value of elements in the array and x will not exceed 104
UPDATE (2017/9/19):
The arr parameter had been changed to an array of integers (instead of a list of integers). Please reload the code definition to get the latest changes.
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
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == x) {
                left = mid;
                break;
            }
            else if (arr[mid] > x) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        int start = left - 1;
        int end = left;
        int temp = k;
        while (k > 0){
            if (start < 0 or (end < arr.size() and abs(arr[start] - x) > abs(arr[end] - x))) {
                end++;
            }
            else {
                start--;
            }
            k -= 1;
        }

        vector<int> result;
        for (int i = start + 1; result.size() < temp; i++) {
            result.push_back(arr[i]);
        }
        return result;
    }
};
