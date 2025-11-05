/*
1213. Intersection of Three Sorted Arrays
https://leetcode.com/problems/intersection-of-three-sorted-arrays/

Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order,
return a sorted array of only the integers that appeared in all three arrays.

Example 1:
Input: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
Output: [1,5]
Explanation: Only 1 and 5 appeared in the three arrays.

Constraints:
1 <= arr1.length, arr2.length, arr3.length <= 1000
1 <= arr1[i], arr2[i], arr3[i] <= 2000
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
    vector<int> arraysIntersection(vector<int> &arr1, vector<int> &arr2, vector<int> &arr3) {
        unordered_map<int, int> count;
        for (int num: arr1) {
            count[num] += 1;
        }
        for (int num: arr2) {
            count[num] += 1;
        }

        vector<int> result;
        for (int num: arr3) {
            count[num] += 1;
            if (count[num] == 3) {
                result.push_back(num);
            }
        }
        return result;
    }
};